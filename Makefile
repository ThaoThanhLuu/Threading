
output: main.o Bitset.o
	g++ main.o Bitset.o -o output

main.o: main.cpp
	g++ -c main.cpp

Bitset.o: Bitset.cpp Bitset.h
	g++ -c Bitset.cpp

clean:
	rm *.o output