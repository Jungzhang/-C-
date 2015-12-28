#This is a Makefile

cc=gcc
object=Main.o Huffman.o Common.o Function.o
Main=Main.c Function.o Common.o Huffman.o
Function=Function.c Common.o Huffman.o
Huffman=Huffman.c  Common.o
Common=Common.c

Huffman : $(object)
	cc -o Huffman $(object) -lm
Main.o : $(Main)
	cc -c $(Main)
Function.o : $(Function)
	cc -c $(Function)
Huffman.o : $(Huffman)
	cc -c $(Huffman)
Common.o : $(Common)
	cc -c $(Common)
.PHONY : clean
clean:
	-rm -f *.o
