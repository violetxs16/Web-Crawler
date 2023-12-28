CC = gcc
SOURCE = crawler.c curl.c pagedir.c url.c hashtable.c set.c queue.c
OBJ = crawler.o pagedir.o url.o curl.o hashtable.o set.o queue.o
HEADER = crawler.h pagedir.h url.h curl.h hashtable.h set.h queue.h

check_crawler: ${OBJ} ${HEADER}
	$(CC) -o check_crawler $(OBJ) -Wall -Wextra -Wpedantic -lcurl

%.o: %.c $(HEADER)
	$(CC) $< -c

clean:
	rm -rf check_cycle
	rm -rf *.o

