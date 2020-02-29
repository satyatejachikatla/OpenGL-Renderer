CXX ?= g++

CXXFLAGS := -I../vendor \
			-I.. \
			-I.

all:
	$(CXX) $(CXXFLAGS) -c Test.cpp
	$(CXX) $(CXXFLAGS) -c TestClearColor.cpp
	$(CXX) $(CXXFLAGS) -c TestTexture2D.cpp

clean:
	rm -f *.o
