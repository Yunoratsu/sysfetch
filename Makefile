CC = gcc
CFLAGS = -Wall -Wextra -fno-builtin-printf
PREFIX ?= /usr/local

OBJS = src/main.o src/sysfetch.o src/utils.o

all: src/include/art.h sysfetch

# Art conversion (text file to C header array
src/include/art.h: src/assets/linux.txt
	@xxd -i src/assets/linux.txt > src/include/art.h

sysfetch: $(OBJS)
	$(CC) $(OBJS) -o sysfetch

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: sysfetch
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp sysfetch $(DESTDIR)$(PREFIX)/bin/

uninstall:
	@echo "Uninstalling sysfetch from $(PREFIX)/bin..."
	rm -f $(DESTDIR)$(PREFIX)/bin/sysfetch

# Clean build artifacts
clean:
	rm -f sysfetch src/*.o src/include/art.h
