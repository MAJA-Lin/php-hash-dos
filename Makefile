all: find-values-fast

find-values-fast: find-values-fast.c
	$(CC) -O3 -o $@ $^
