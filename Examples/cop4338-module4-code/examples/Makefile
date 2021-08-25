all: cat filecopy unixfilecopy myprintf scan

cat: cat.c
	gcc -Wall cat.c -o cat

filecopy: filecopy.c
	gcc -Wall filecopy.c -o filecopy

unixfilecopy: unixfilecopy.c
	gcc -Wall unixfilecopy.c -o unixfilecopy

myprintf: myprintf.c
	gcc -Wall myprintf.c -o myprintf

scan: scan.c
	gcc -Wall scan.c -o scan

clean:
	$(RM) *.o *~
	$(RM) cat filecopy unixfilecopy myprintf scan
