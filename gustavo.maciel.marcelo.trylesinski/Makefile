CC     = g++
CFLAGS = -std=c++11 -Wall -pedantic -O3 -flto
objects = main.o mtrutils.o

main: $(objects)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

mtrutils.o: mtrutils.cpp mtrutils.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f main $(objects)
