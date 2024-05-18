CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = main.c matrix.c binary_inverse.c bitflipping.c

all: $(SRC)
	$(CC) $(CFLAGS) $^ -o prog

clean:
	rm -f prog