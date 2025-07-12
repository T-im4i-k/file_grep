CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -pedantic

LD = g++
LDFLAGS = 

SRC_DIR = src
BUILD_DIR = build

CPP_FILES = $(shell find $(SRC_DIR) -name '*.cpp')

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_FILES))

DEP_FILES = $(OBJ_FILES:.o=.d)


all: $(BUILD_DIR)/main.out

run: $(BUILD_DIR)/main.out
	./$<

run_val: $(BUILD_DIR)/main.out
	valgrind ./$<

$(BUILD_DIR)/main.out: $(OBJ_FILES) | $(BUILD_DIR)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

-include $(DEP_FILES)

clean:
	rm -rf $(BUILD_DIR)/*