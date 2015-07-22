myshell: myshell.o list.o
	gcc myshell.o list.o -o myshell
myshell.o: list.h myshell.c
	gcc -c myshell.c -o myshell.o
list.o:	list.c list.h
	gcc -c list.c -o list.o
.PHONY: clean
clean:
	-rm -f *.o
