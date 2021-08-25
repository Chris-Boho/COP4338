all:	f2k

f2k:	f2k.o
	gcc f2k.o -o f2k

f2k.o: f2k.c
	gcc -c f2k.c -o f2k.o

clean:
	rm -f f2k f2k.o core *~
