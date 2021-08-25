all:	pointers arrays strings

pointers:	pointers.c
	gcc -Wall $< -o $@

arrays:	arrays.c
	gcc -Wall $< -o $@

strings:	strings.c
	gcc -Wall $< -o $@

clean:
	rm -f pointers arrays strings *.o core *~
