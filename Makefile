CC=gcc
CFLAGS=-Wall -Wextra -Werror
DEPS = hash.h strset.h stream_reader.h
OBJ = strset.o hash.o main.o stream_reader.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

strdict: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
