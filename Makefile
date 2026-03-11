CXX=gcc
FLAGS=-Wall -Wextra

BUILD_DIR=build

.PHONY: all cache_test_counting cache_test_f_s_ptr sanitized clean
all: cache_test_counting

cache_test_counting: $(BUILD_DIR)/cache_test_counting_o0 $(BUILD_DIR)/cache_test_counting_o1 $(BUILD_DIR)/cache_test_counting_o2

cache_test_f_s_ptr: $(BUILD_DIR)/cache_test_f_s_ptr_o0 $(BUILD_DIR)/cache_test_f_s_ptr_o1 $(BUILD_DIR)/cache_test_f_s_ptr_o2

$(BUILD_DIR)/cache_test_counting_o0: cache_test.c
	$(CXX) $(FLAGS) -O0 -D METHOD_COUNTING $< -o $@

$(BUILD_DIR)/cache_test_counting_o1: cache_test.c
	$(CXX) $(FLAGS) -O1 -D METHOD_COUNTING $< -o $@

$(BUILD_DIR)/cache_test_counting_o2: cache_test.c
	$(CXX) $(FLAGS) -O2 -D METHOD_COUNTING $< -o $@

$(BUILD_DIR)/cache_test_f_s_ptr_o0: cache_test.c
	$(CXX) $(FLAGS) -O0 -D METHOD_F_S_PTR $< -o $@
	
$(BUILD_DIR)/cache_test_f_s_ptr_o1: cache_test.c
	$(CXX) $(FLAGS) -O1 -D METHOD_F_S_PTR $< -o $@

$(BUILD_DIR)/cache_test_f_s_ptr_o2: cache_test.c
	$(CXX) $(FLAGS) -O2 -D METHOD_F_S_PTR $< -o $@

sanitized: $(BUILD_DIR)/cache_test_counting_sanitized $(BUILD_DIR)/cache_test_f_s_ptr_sanitized
$(BUILD_DIR)/cache_test_counting_sanitized: cache_test.c
	$(CXX) $(FLAGS) -g -D METHOD_COUNTING -fsanitize=address $< -o $@

$(BUILD_DIR)/cache_test_f_s_ptr_sanitized: cache_test.c
	$(CXX) $(FLAGS) -g -D METHOD_F_S_PTR -fsanitize=address $< -o $@


clean:
	rm -rf $(BUILD_DIR)/*
