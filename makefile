CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lssl -lcrypto
SRC = main.c matrix.c binary_inverse.c bitflipping.c prange.c mdpc.c

# Valeurs par défaut pour n, k, et t
PARAM_N = 200
PARAM_K = 100
PARAM_T = 10
PARAM_SIZE = 4813
PARAM_WEIGHT_H = 39
PARAM_WEIGHT_E = 78
PARAM_THRESHOLD = 26

all: prog

prog: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o prog -DPARAM_N=$(PARAM_N) -DPARAM_K=$(PARAM_K) -DPARAM_T=$(PARAM_T) -DPARAM_SIZE=$(PARAM_SIZE) -DPARAM_WEIGHT_H=$(PARAM_WEIGHT_H) -DPARAM_WEIGHT_E=$(PARAM_WEIGHT_E) -DPARAM_THRESHOLD=$(PARAM_THRESHOLD) $(LDFLAGS)

clean:
	rm -f prog
