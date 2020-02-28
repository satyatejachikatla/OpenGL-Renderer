CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lGL    \
		-lGLU   \
		-lGLEW  \
		-lglfw 

CXXFLAGS := -I./vendor \
			-I./tests

BUILT_LIBS := glErrors.a \
			  Renderer.a \
			  VertexBuffer.a \
			  IndexBuffer.a \
			  VertexArray.a \
			  Shader.a \
			  Texture.a

BUILT_LIBS += vendor/stb_image/stb_image.a \
			  vendor/imgui/imgui.a

BUILT_LIBS += tests/Test.a \
			  tests/TestClearColor.a

all:

	$(MAKE) libs

	$(MAKE) -C tests all

	$(MAKE) app

app:
	$(CXX) $(CXXFLAGS) main.cpp -o run $(LIBS) $(BUILT_LIBS)

libs:

	$(CXX) $(CXXFLAGS) -c glErrors.cpp 
	$(CXX) $(CXXFLAGS) -c Renderer.cpp 
	$(CXX) $(CXXFLAGS) -c VertexBuffer.cpp 
	$(CXX) $(CXXFLAGS) -c IndexBuffer.cpp 
	$(CXX) $(CXXFLAGS) -c VertexArray.cpp 
	$(CXX) $(CXXFLAGS) -c Shader.cpp 
	$(CXX) $(CXXFLAGS) -c Texture.cpp 
	
	$(AR)  rvs glErrors.a glErrors.o
	$(AR)  rvs Renderer.a Renderer.o
	$(AR)  rvs VertexBuffer.a VertexBuffer.o
	$(AR)  rvs IndexBuffer.a IndexBuffer.o
	$(AR)  rvs VertexArray.a VertexArray.o
	$(AR)  rvs Shader.a Shader.o
	$(AR)  rvs Texture.a Texture.o

clean:
	rm -f run
	rm -f *.o
	rm -f *.a

	$(MAKE) -C tests clean