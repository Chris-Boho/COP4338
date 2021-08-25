all:	hw3

hw3:	main.o mylist.o
	gcc -Wall main.o mylist.o -o $@

main.o:	main.c mylist.h
	gcc -c -Wall $< -o $@

mylist.o:	mylist.c mylist.h
	gcc -c -Wall $< -o $@

clean:
	rm -f hw3 *.o core *~
