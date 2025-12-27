.PHONY: all clean test

CC = clang
CXX = clang++
CFLAGS = -Wall -Wextra -O2
CXXFLAGS = -Wall -Wextra -O2 -std=c++11

# Flags for creating a PIE (Position Independent Executable) that can be loaded as a library
DYEXE_FLAGS = -fPIC -Wl,-export_dynamic -Wl,-pie

# Build directory
BUILD_DIR = build

all: $(BUILD_DIR) $(BUILD_DIR)/dyexe $(BUILD_DIR)/test_loader

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/dyexe: dyexe.cpp
	$(CXX) $(CXXFLAGS) $(DYEXE_FLAGS) -o $(BUILD_DIR)/dyexe dyexe.cpp

$(BUILD_DIR)/test_loader: test_loader.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_loader test_loader.c

test: all
	@echo "=== Test 1: Executable mode ==="
	@echo ""
	./test_executable.sh $(BUILD_DIR)/dyexe
	@echo ""
	@echo "=== Test 2: Library mode ==="
	@echo ""
	$(BUILD_DIR)/test_loader $(BUILD_DIR)/dyexe

clean:
	rm -rf $(BUILD_DIR)
