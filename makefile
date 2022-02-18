# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := PassLock
DEBUG_EXEC := PassLockDebug

BUILD_DIR := ./build
SRC_DIRS := ./src
LIB_DIRS := ./lib

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_LIBS := $(shell find $(LIB_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
INC_FLAGS += $(addprefix -I,$(INC_LIBS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -std=c++17 -MMD -MP -g
DBGCFLAGS = $(INC_FLAGS) -g -O0 -DDEBUG

# debug settings
DBGEXE = $(BUILD_DIR)/$(DEBUG_EXEC)



# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


clean:
	rm -r $(BUILD_DIR)

run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

debug: $(TARGET_EXEC)
	valgrind $(TARGET_EXEC)

valgrind: $(TARGET_EXEC)
	valgrind $(TARGET_EXEC)

valgrind_leakcheck: $(TARGET_EXEC)
	valgrind --leak-check=full $(TARGET_EXEC)

valgrind_extreme: $(TARGET_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(TARGET_EXEC)
# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
