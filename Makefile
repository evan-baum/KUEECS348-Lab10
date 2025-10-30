CC=g++
CFLAGS=-c -w -Wall
all: stringCalc

stringCalc: stringCalc.o
	$(CC) stringCalc.o -o stringCalc
	rm -rf *.o

%.o: %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm stringCalc