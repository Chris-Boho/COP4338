all:	shellsort

shellsort: shellsort.o
	gcc shellsort.o -o shellsort

shellsort.o: shellsort.c
	gcc -c shellsort.c -o shellsort.o

clean:
	rm -f shellsort shellsort.o core *~
