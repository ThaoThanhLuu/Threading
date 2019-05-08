CC=g++
CCFLAGS=-pthread

output: main.o Bitset.o
	$(CC) $(CCFLAGS) main.o Bitset.o -o output

main.o: main.cpp
	$(CC) $(CCFLAGS) -c main.cpp

Bitset.o: Bitset.cpp Bitset.h
	$(CC) $(CCFLAGS) -c Bitset.cpp

clean:
	rm *.o output
