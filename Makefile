# only test demo
# CC                    := gcc
CC                    := g++
EXEC                  := main

MK_PATH               := $(abspath $(lastword $(MAKEFILE_LIST)))
ROOT_DIR              := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_DIR             := $(ROOT_DIR)/out
BUILD_ABS_DIR         := $(abspath $(BUILD_DIR))


INCLUDE_DIRS          := -I.
INCLUDE_DIRS          += -I$(ROOT_DIR)/src
INCLUDE_DIRS          += -I$(ROOT_DIR)/src/demo
INCLUDE_DIRS          += -I$(ROOT_DIR)/src/utils
INCLUDE_DIRS          += -I$(ROOT_DIR)/src/lib/uthash/include


SOURCE_FILES          := $(wildcard *.c)
SOURCE_FILES          += $(wildcard src/demo/array/*.c)
SOURCE_FILES          += $(wildcard src/demo/string/*.c)
SOURCE_FILES          += $(wildcard src/demo/stack/*.c)
SOURCE_FILES          += $(wildcard src/demo/queue/*.c)
SOURCE_FILES          += $(wildcard src/demo/hash_table/*.c)
SOURCE_FILES          += $(wildcard src/demo/binary_search/*.c)
SOURCE_FILES          += $(wildcard src/demo/dynamic_programming/*.c)
SOURCE_FILES          += $(wildcard src/demo/sort/*.c)
SOURCE_FILES          += $(wildcard src/demo/math/*.c)
SOURCE_FILES          += $(wildcard src/utils/*.c)

ifdef T
SOURCE_FILES          += $(wildcard src/test/*.c)
else
SOURCE_FILES          += $(wildcard src/demo/*.c)
endif

CFLAGS                += -m32 # gcc 32bit

CPPFLAGS              := $(INCLUDE_DIRS) -DBUILD_DIR=\"$(BUILD_ABS_DIR)\"
CPPFLAGS              += -ggdb3
CPPFLAGS              += -Wall
CPPFLAGS              += -O0

LDFLAGS               := -pthread
LDFLAGS               += -lm # to link againt the math library (libm)
LDFLAGS               += -m32


OBJ_FILES             = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
DEP_FILE              = $(OBJ_FILES:%.o=%.d)

$(EXEC) : $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC) : $(OBJ_FILES)
	@-mkdir -p $(@D)
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo "EXEC $@"
	@echo "MAKE DONE!"

-include $(DEP_FILE)

$(BUILD_DIR)/%.o : %.c Makefile
	@-mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c $< -o $@
	@echo "CC $<"

.PHONY: all
all: $(BUILD_DIR)/$(EXEC)

# Clean build and bin directories for all platforms
.PHONY: clean
clean:
	-rm -rf $(BUILD_DIR)

# Run clang-format on source code
.PHONY: format
format:
	@echo "Running clang-format"
	@clang-format -i \
	$(shell find src/demo -name "*.c") \
	$(shell find src/test -name "*.c") \
	$(shell find src/utils -name "*.c")

# Build and run
.PHONY: run
run: all
	@echo "Starting program: $(BUILD_DIR)/$(EXEC)"
	@cd $(BUILD_DIR) && ./$(EXEC)
