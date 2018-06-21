NVCC	  = nvcc
CXX       = g++
CPPFLAGS  = -std=c++11 -Wall -pedantic -O3 -flto
CUDAFLAGS = -arch sm_30 -Xptxas --opt-level=3
LDFLAGS   = -L/usr/local/cuda/lib64 -lcudart
objects   = main.o mtrutils.o reduce.o
tobjects  = test.o mtrutils.o reduce.o

main : $(objects)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

test : $(tobjects)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o : mtrutils.h reduce.cuh
test.o : mtrutils.h reduce.cuh
mtrutils.o : mtrutils.h
reduce.o : reduce.cu reduce.cuh mtrutils.h
	$(NVCC) $(CUDAFLAGS) -c $<

.PHONY : clean
clean :
	-rm -f main test $(objects) $(tobjects)
