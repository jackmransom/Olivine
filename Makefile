CFLAGS = --std=c99 -Wall -Wextra -Wpedantic -lm -march=native
DEBUGFLAGS = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG

TARGET = pkmnsav

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o bin/$@ $@.c

release:
	$(CC) $(CFLAGS) $(RELEASEFLAGS) -o bin/$(TARGET) $(TARGET).c

.PHONY: clean

clean:
	rm -f bin/pkmnsav
