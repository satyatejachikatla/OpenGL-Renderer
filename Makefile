CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lGL    \
		-lGLU   \
		-lGLEW  \
		-lglfw 

CXXFLAGS := -I./vendor

BUILT_LIBS := glErrors.a \
			  Renderer.a \
			  VertexBuffer.a \
			  IndexBuffer.a \
			  VertexArray.a \
			  Shader.a \
			  Texture.a \
			  vendor/stb_image/stb_image.a \

# 
# -lglut

all:

	
	$(MAKE) libs
	$(CXX) $(CXXFLAGS) main.cpp -o run $(LIBS) $(BUILT_LIBS)

libs:

	$(MAKE) -C vendor all

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

	$(MAKE) -C vendor clean
