# Makefile for 2-Level Page Table Mapping System

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = os.hw3.2021041017.kimgyuhyeon
SOURCE = os.hw3.2021041017.kimgyuhyeon.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild