all:	mymalloc mymath 

mymalloc:	mymalloc.c
	gcc -Wall $< -o $@

mymath:	mymath.c
	gcc -Wall $< -o $@

clean:
	rm -f mymalloc mymath *.o core *~
