INCLUDEDIR = $(CURDIR)/include

CFLAGS = -shared -c -fpic --std=c99 -Wall -Wextra -Wpedantic -lm -march=native -I$(INCLUDEDIR)
DEBUGFLAGS = -O0 -g -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG

TARGET = libolivine
LIBDIR = $(CURDIR)/lib

all: $(TARGET)

$(TARGET):
	mkdir $(LIBDIR)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(LIBDIR)/$@.so $(TARGET).c

release:
	mkdir $(LIBDIR)
	$(CC) $(CFLAGS) $(RELEASEFLAGS) -o $(LIBDIR)/$(TARGET).so $(TARGET).c

.PHONY: clean

clean:
	rm -f $(LIBDIR)/$(TARGET)
