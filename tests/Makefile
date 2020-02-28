CXX ?= g++
AR  ?= ar
MAKE ?= make

CXXFLAGS := -I../vendor \
			-I.. \
			-I.

all:
	$(CXX) $(CXXFLAGS) -c Test.cpp
	$(CXX) $(CXXFLAGS) -c TestClearColor.cpp
	$(CXX) $(CXXFLAGS) -c TestTexture2D.cpp
	
	$(AR)  rvs Test.a Test.o
	$(AR)  rvs TestClearColor.a TestClearColor.o
	$(AR)  rvs TestTexture2D.a TestTexture2D.o

	cp *.o ../


clean:
	rm -f *.o
	rm -f *.a
