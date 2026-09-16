CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I. -I../common
TARGET = s21_cat
SRC = s21_cat.c main.c
HEADER = s21_cat.h
COMMON_SRC = ../common/s21_common.c
COMMON_HEADER = ../common/s21_common.h
all: $(TARGET)
s21_cat: $(SRC) $(HEADER)
$(TARGET): $(SRC) $(HEADER) $(COMMON_SRC) $(COMMON_HEADER)
	$(CC) $(CFLAGS) $(SRC) $(COMMON_SRC) -o $(TARGET)
clean:
	rm -f $(TARGET)
test: $(TARGET)
	chmod +x test_s21_cat.sh
	bash ./test_s21_cat.sh
rebuild: clean all
.PHONY: all clean rebuild test s21_cat