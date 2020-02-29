CXX ?= g++
AR  ?= ar

all:
	$(CXX) -c stb_image.cpp
	$(AR)  rvs stb_image.a stb_image.o
clean:
	rm -f *.o
	rm -f *.a
