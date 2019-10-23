CC=gcc
CFLAGS=-Wall -Wextra

main: main.o tokenizer.o interpreter.o
	$(CC) $(CFLAGS) main.o tokenizer.o interpreter.o -o main

debug: main.o tokenizer.o interpreter.o
	$(CC) $(CFLAGS) -g main.o tokenizer.o interpreter.o -o main.debug

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

tokenizer.o: tokenizer.c
	$(CC) $(CFLAGS) -c tokenizer.c

interpreter.o: interpreter.c
	$(CC) $(CFLAGS) -c interpreter.c

.PHONY: clean

clean:
	@rm -rf *.o

cleanall:
	@rm -rf *.o main
