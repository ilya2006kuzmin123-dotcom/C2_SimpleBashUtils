CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TARGET = s21_cat
SRC = s21_cat.c
all: $(TARGET)
s21_cat: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
clean:
	rm -f $(TARGET)
rebuild: clean all
