CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lssl -lcrypto
SRC = main.c matrix.c binary_inverse.c bitflipping.c prange.c mdpc.c

# Valeurs par défaut pour n, k, et t
PARAM_N = 200
PARAM_K = 100
PARAM_T = 10

all: prog

prog: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o prog -DPARAM_N=$(PARAM_N) -DPARAM_K=$(PARAM_K) -DPARAM_T=$(PARAM_T) $(LDFLAGS)

clean:
	rm -f prog
