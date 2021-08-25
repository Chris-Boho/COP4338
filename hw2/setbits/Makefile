all:	setbits

setbits:	setbits.o
	gcc setbits.o -o setbits

setbits.o: setbits.c
	gcc -c setbits.c -o setbits.o

clean:
	rm -f setbits setbits.o core *~
