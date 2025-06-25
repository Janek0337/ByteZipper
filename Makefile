CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
DEBUGFLAGS = -g -O0
OBJ_DIR := build
SRC_DIR := src

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
TARGET = $(OBJ_DIR)/kompresor

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(TARGET)

debug: CFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

TEST_DIR := test
TEST_BUILD_DIR := $(OBJ_DIR)/test
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_BIN := $(patsubst $(TEST_DIR)/%.c, $(TEST_BUILD_DIR)/%, $(TEST_SRC))
TEST_OBJ := $(filter-out $(OBJ_DIR)/main.o, $(OBJ))

$(TEST_BUILD_DIR)/%: $(TEST_DIR)/%.c $(TEST_OBJ)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

test: all $(TEST_BIN)
	@printf "\033[33mRunning tests...\033[0m\n"
	@for test in $(TEST_BIN); do \
    echo "\033[35m>> $$test\033[0m\n"; \
    	if ! $$test; then \
   	     printf "\033[31m%s\033[0m\n" "Test $$test FAILED!"; \
  	      exit 1; \
 	   fi; \
	done
	
	@printf "\033[32mAll tests passed\033[0m\n"