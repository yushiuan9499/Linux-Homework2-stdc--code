CXX=gcc
FLAGS=-Wall -Wextra

BUILD_DIR=build

.PHONY: all clean
all: linux_version my_version

linux_version: $(BUILD_DIR)/linux_version_o0 $(BUILD_DIR)/linux_version_o2

my_version: $(BUILD_DIR)/my_version_o0 $(BUILD_DIR)/my_version_o2

$(BUILD_DIR)/linux_version_o0: count_masked_bytes.c
	$(CXX) $(FLAGS) -O0 -D LINUX $< -o $@

$(BUILD_DIR)/linux_version_o2: count_masked_bytes.c
	$(CXX) $(FLAGS) -O2 -D LINUX $< -o $@

$(BUILD_DIR)/my_version_o0: count_masked_bytes.c
	$(CXX) $(FLAGS) -O0 -D MY $< -o $@

$(BUILD_DIR)/my_version_o2: count_masked_bytes.c
	$(CXX) $(FLAGS) -O2 -D MY $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*
