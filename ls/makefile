my_ls: ls.o displayifo.o analyze_dir.o
	gcc ls.o displayifo.o analyze_dir.o -o my_ls
ls.o: main.c
	gcc -c main.c -o ls.o
displayifo.o: displayifo.c
	gcc -c displayifo.c -o displayifo.o
analyze_dir.o: analyze_dir.c
	gcc -c analyze_dir.c -o analyze_dir.o
.PHONY : clean
clean:
	-rm -f *.o
#This is a makefile
