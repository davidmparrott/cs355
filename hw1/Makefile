CC=gcc
COPTS=-g -std=c99 -pedantic -Wall

ALL: scanner
clean:
	-rm -rf *.o *.dSYM scanner core *~

scanner: scanner.c
	$(CC) $(COPTS) -DTEST_SCANNER $^ -o $@

.c.o:
	$(CC) -c $(COPTS) $<

scanner.o: scanner.c scanner.h
