CXX ?= g++

CXXFLAGS := -I../vendor \
			-I../infra \
			-I.. \
			-I.

all:
	$(CXX) $(CXXFLAGS) -c *.cpp

clean:
	rm -f *.o
