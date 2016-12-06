CFLAGS=--std=c99 -Wall -Wextra -Wpedantic -g

pkmnsav:
	$(CC) -o bin/$@ $(CFLAGS) $@.c

.PHONY: clean

clean:
	rm -f bin/pkmnsav
