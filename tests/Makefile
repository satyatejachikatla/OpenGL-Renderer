CXX ?= g++
PYTHON := python3

CXXFLAGS := -I../vendor \
			-I../infra \
			-I.. \
			-I.

all:
	$(CXX) $(CXXFLAGS) -c *.cpp
	$(PYTHON) genTestInclude.py

clean:
	rm -f *.o
	rm -f allTestInclude.h
	rm -f allTestReg.h
	touch allTestInclude.h
	touch allTestReg.h
