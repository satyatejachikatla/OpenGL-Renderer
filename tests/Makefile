CXX ?= g++
AR  ?= ar
MAKE ?= make

CXXFLAGS := -I../vendor \
			-I.. \
			-I.

all:
	$(CXX) $(CXXFLAGS) -c TestClearColor.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp

	$(AR)  rvs TestClearColor.a TestClearColor.o
	$(AR)  rvs Test.a Test.o


clean:
	rm -f *.o
	rm -f *.a
