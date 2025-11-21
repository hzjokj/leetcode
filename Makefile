# ============================================================================
# Project Configuration
# ============================================================================
CC                    := g++
EXEC                  := main
ROOT_DIR              := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_DIR             := $(ROOT_DIR)/out

# ============================================================================
# Include Directories
# ============================================================================
INCLUDE_DIRS          := . \
                         src \
                         src/demo \
                         src/utils \
                         src/lib/uthash/include

INCLUDE_FLAGS         := $(addprefix -I$(ROOT_DIR)/,$(INCLUDE_DIRS))

# ============================================================================
# Source Files Collection
# ============================================================================
# Common source directories
SRC_DIRS              := src/demo/array \
                         src/demo/string \
                         src/demo/stack \
                         src/demo/queue \
                         src/demo/hash_table \
                         src/demo/binary_search \
                         src/demo/dynamic_programming \
                         src/demo/sort \
                         src/demo/math \
                         src/utils

# Collect all .c files from specified directories
SOURCE_FILES          := $(wildcard *.c) \
                         $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Conditional: Add test or demo main entry
ifdef T
    SOURCE_FILES      += $(wildcard src/test/*.c)
else
    SOURCE_FILES      += $(wildcard src/demo/*.c)
endif

# ============================================================================
# Compiler and Linker Flags
# ============================================================================
COMMON_FLAGS          := -m32 -ggdb3 -Wall -O0
CPPFLAGS              := $(INCLUDE_FLAGS) -DBUILD_DIR=\"$(abspath $(BUILD_DIR))\"
CFLAGS                := $(COMMON_FLAGS)
LDFLAGS               := $(COMMON_FLAGS) -pthread -lm

# ============================================================================
# Object and Dependency Files
# ============================================================================
OBJ_FILES             := $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
DEP_FILES             := $(OBJ_FILES:%.o=%.d)

# ============================================================================
# Build Rules
# ============================================================================
.PHONY: all clean format run help

# Default target
all: $(BUILD_DIR)/$(EXEC)

# Link executable
$(BUILD_DIR)/$(EXEC): $(OBJ_FILES)
	@mkdir -p $(@D)
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo "✓ Linked: $@"
	@echo "✓ Build complete!"

# Include dependency files
-include $(DEP_FILES)

# Compile source files
$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c $< -o $@
	@echo "✓ Compiled: $<"

# ============================================================================
# Utility Targets
# ============================================================================
# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Clean complete!"

# Format source code
format:
	@echo "Formatting source code..."
	@clang-format -i \
		$(shell find src/demo src/test src/utils -name "*.c" 2>/dev/null)
	@echo "✓ Format complete!"

# Build and run
run: all
	@echo "Running: $(BUILD_DIR)/$(EXEC)"
	@echo "----------------------------------------"
	@cd $(BUILD_DIR) && ./$(EXEC)

# Display help information
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  format  - Format source code with clang-format"
	@echo "  run     - Build and run the executable"
	@echo "  help    - Display this help message"
	@echo ""
	@echo "Variables:"
	@echo "  T=1     - Build with test files instead of demo"
	@echo ""
	@echo "Examples:"
	@echo "  make              # Build project"
	@echo "  make run          # Build and run"
	@echo "  make T=1 run      # Build tests and run"
	@echo "  make clean all    # Clean rebuild"