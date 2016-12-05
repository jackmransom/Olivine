CC=clang
CFLAGS=--std=c99 -Wall -Wextra -Wpedantic

pkmnsav:
	$(CC) -o bin/$@ $(CFLAGS) $@.c
