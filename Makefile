CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lGL    \
		-lGLU   \
		-lGLEW  \
		-lglfw 

CXXFLAGS := -I./vendor \
            -I./infra \
			-I./tests \
			-I. \
			-Wl,-no-as-needed

BUILT_LIBS := vendor/stb_image/stb_image.a \
			  vendor/imgui/imgui.a


OBJS := *.o tests/*.o infra/*.o

all:

	$(MAKE) -C infra all
	$(MAKE) -C tests all
	$(MAKE) app

app:
	$(CXX) $(CXXFLAGS) -c main.cpp 
	$(CXX) $(OBJS) $(LIBS) $(BUILT_LIBS) -o run

clean:
	rm -f run
	rm -f *.o
	rm -f *.a

	$(MAKE) -C infra clean
	$(MAKE) -C tests clean