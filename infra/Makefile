CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lGL    \
		-lGLU   \
		-lGLEW  \
		-lglfw 

CXXFLAGS := -I../vendor \
			-I../tests \
			-I. \
			-I.. \
			-Wl,-no-as-needed

BUILT_LIBS := ../vendor/stb_image/stb_image.a \
			  ../vendor/imgui/imgui.a


all:

	$(CXX) $(CXXFLAGS) -c *.cpp

clean:
	rm -f *.o
	rm -f *.a