CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lGL    \
		-lGLU   \
		-lGLEW  \
		-lglfw 

CXXFLAGS := -I./vendor \
			-I./tests \
			-I. \
			-Wl,-no-as-needed

BUILT_LIBS := *.a

BUILT_LIBS += vendor/stb_image/stb_image.a \
			  vendor/imgui/imgui.a


all:

	$(MAKE) libs

	$(MAKE) -C tests all

	$(MAKE) app

app:
	$(CXX) $(CXXFLAGS) -c main.cpp 
	$(CXX) *.o $(LIBS) $(BUILT_LIBS) -o run

libs:

	$(CXX) $(CXXFLAGS) -c glErrors.cpp 
	$(CXX) $(CXXFLAGS) -c Renderer.cpp 
	$(CXX) $(CXXFLAGS) -c VertexBuffer.cpp 
	$(CXX) $(CXXFLAGS) -c IndexBuffer.cpp 
	$(CXX) $(CXXFLAGS) -c VertexArray.cpp 
	$(CXX) $(CXXFLAGS) -c Shader.cpp 
	$(CXX) $(CXXFLAGS) -c Texture.cpp 
	
	$(AR)  rvs built_libs.a *.o

clean:
	rm -f run
	rm -f *.o
	rm -f *.a

	$(MAKE) -C tests clean