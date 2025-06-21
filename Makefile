CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUGFLAGS = -g -O0

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = kompresor

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

debug: CFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)