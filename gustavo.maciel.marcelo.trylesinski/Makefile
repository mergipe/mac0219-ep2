CXX      = g++
CPPFLAGS = -std=c++11 -Wall -pedantic -O3 -flto
objects  = main.o mtrutils.o

main : $(objects)
	$(CXX) $(CPPFLAGS) -o $@ $^

$(objects) : mtrutils.h

.PHONY : clean
clean :
	-rm -f main $(objects)
