all:	wcdash

wcdash: wcdash.o
	gcc wcdash.o -o wcdash

wcdash.o: wcdash.c
	gcc -c wcdash.c -o wcdash.o

clean:
	rm -f wcdash wcdash.o core *~
