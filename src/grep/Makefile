CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TARGET = s21_grep
SRC = s21_grep.c
all: $(TARGET)
s21_grep: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
clean:
	rm -f $(TARGET)
rebuild: clean all