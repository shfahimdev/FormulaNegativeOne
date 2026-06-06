# Makefile
CC     = gcc
CFLAGS = -Wall -Wextra -g
LIBS   = -lm -lpthread

TARGET = formulanegativeone
SRC    = $(wildcard *.c)
OBJ    = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
