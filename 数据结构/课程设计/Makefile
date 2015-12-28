#This is a Makefile

object=Main.o Huffman.o Common.o Function.o

Huffman : $(object)
	cc -o Huffman $(object) -lm
Main.o : Function.h Huffman.h Common.h
Function.o : Function.h Huffman.h Common.h
Huffman.o : Huffman.h Common.h
Common.o : Common.h

.PHONY : clean
clean:
	-rm -f *.o
