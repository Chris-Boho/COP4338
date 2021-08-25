all:	args wc1

args:	args.o
	gcc args.o -o args

args.o:	args.c
	gcc -Wall -c args.c -o args.o

wc1:	wc1.o
	gcc wc1.o -o wc1

wc1.o:	wc1.c
	gcc -Wall -c wc1.c -o wc1.o

clean:
	rm -f args args.o wc1 wc1.o core *~
