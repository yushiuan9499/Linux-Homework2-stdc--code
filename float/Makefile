CXX=gcc
FLAGS=-Wall -Wextra

BUILD_DIR=build

.PHONY: all clean
all: $(BUILD_DIR)/bin_representation

$(BUILD_DIR)/bin_representation: bin_representation.c
	$(CXX) $(FLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)/*
