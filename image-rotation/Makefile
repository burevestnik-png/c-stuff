CFLAGS=--std=c18 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
CC=gcc
TARGET = build/

all: print_header

bmp.o: structs/bmp.c
	$(CC) -c $(CFLAGS) $< -o $(TARGET)$@

util.o: util/util.c
	$(CC) -c $(CFLAGS) $< -o $(TARGET)$@

fman.o: util/file_manager.c
	$(CC) -c $(CFLAGS) $< -o $(TARGET)$@

image.o: structs/image.c
	$(CC) -c $(CFLAGS) $< -o $(TARGET)$@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $(TARGET)$@

print_header: main.o util.o bmp.o fman.o image.o
	$(CC) -o $(TARGET)print_header $(TARGET)main.o $(TARGET)util.o $(TARGET)bmp.o $(TARGET)fman.o $(TARGET)image.o

clean:
	rm -f $(TARGET)main.o $(TARGET)util.o $(TARGET)bmp.o $(TARGET)print_header $(TARGET)fman.o $(TARGET)image.o

