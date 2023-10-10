CC = gcc
CFLAGS = -I. -lm

HDF5_FLAGS = -I/usr/include/hdf5/serial -L/usr/lib/x86_64-linux-gnu/hdf5/serial -lhdf5
COMMON_HDRS = ./utils/data_utils.h ./kernel/conv.h ./kernel/functional.h ./kernel/matrix_ops.h ./kernel/linear.h
COMMON_SRC = ./utils/data_utils.c ./kernel/conv.c ./kernel/functional.c ./kernel/matrix_ops.c ./kernel/linear.c

# Unity test framework
UNITY_FILES = ./tests/unity/unity.c
TEST_FILES = $(wildcard ./tests/*.c)
MODULE_TEST_FILES = $(wildcard ./tests/test*.c)
TEST_EXECUTABLES = $(patsubst %.c,%,$(TEST_FILES))

main.out: main.c
	$(CC) -o main.out main.c $(COMMON_SRC) $(CFLAGS) $(HDF5_FLAGS) 
	./main.out NAIVE 100 5 1

.PHONY: test
test: all_tests

.PHONY: all_tests
all_tests: 
	$(CC) -o tests/$@ $(TEST_FILES) $(UNITY_FILES) $(COMMON_SRC) $(CFLAGS) $(HDF5_FLAGS) 
	./tests/$@
t:
	./tests/all_tests

debug_test:
	$(CC) -g -o tests/$@ $(TEST_FILES) $(UNITY_FILES) $(COMMON_SRC) $(CFLAGS) $(HDF5_FLAGS) 
	gdb ./tests/$@
	
.PHONY: clean
clean:
	rm -f $(TEST_EXECUTABLES)