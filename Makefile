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
			-I./objects \
			-I. \
			-Wl,-no-as-needed

BUILT_LIBS := vendor/stb_image/stb_image.a \
			  vendor/imgui/imgui.a


OBJS := tests/*.o infra/*.o objects/*.o

all:

	$(MAKE) -C infra all
	$(MAKE) -C objects all
	$(MAKE) -C tests all
	$(MAKE) app

app:
	$(CXX) $(CXXFLAGS) -c main.cpp 
	$(CXX) main.o $(OBJS) $(LIBS) $(BUILT_LIBS) -o run

	$(CXX) $(CXXFLAGS) -c shader_toy.cpp
	$(CXX) shader_toy.o $(OBJS) $(LIBS) $(BUILT_LIBS) -o toy

clean:
	rm -f run
	rm -f toy
	rm -f *.o
	rm -f *.a

	$(MAKE) -C infra clean
	$(MAKE) -C objects clean
	$(MAKE) -C tests clean