CFLAGS = --std=c99 -Wall -Wextra -Wpedantic -lm -march=native
DEBUGFLAGS = -O0 -g -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG

TARGET = pkmnsav
BINDIR = bin

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(BINDIR)/$@ $(TARGET).c

release:
	$(CC) $(CFLAGS) $(RELEASEFLAGS) -o $(BINDIR)/$(TARGET) $(TARGET).c

.PHONY: clean

clean:
	rm -f $(BINDIR)/$(TARGET)
