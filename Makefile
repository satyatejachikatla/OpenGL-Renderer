CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lGL    \
		-lGLU   \
		-lGLEW  \
		-lglfw

BUILT_LIBS := glErrors.a \
			  Renderer.a \
			  VertexBuffer.a \
			  IndexBuffer.a \
			  VertexArray.a \
			  Shader.a

# 
# -lglut

all:
	$(MAKE) libs
	$(CXX) main.cpp -o run $(LIBS) $(BUILT_LIBS)

libs:
	$(CXX) -c glErrors.cpp
	$(CXX) -c Renderer.cpp
	$(CXX) -c VertexBuffer.cpp
	$(CXX) -c IndexBuffer.cpp
	$(CXX) -c VertexArray.cpp
	$(CXX) -c Shader.cpp
	
	$(AR)  rvs glErrors.a glErrors.o
	$(AR)  rvs Renderer.a Renderer.o
	$(AR)  rvs VertexBuffer.a VertexBuffer.o
	$(AR)  rvs IndexBuffer.a IndexBuffer.o
	$(AR)  rvs VertexArray.a VertexArray.o
	$(AR)  rvs Shader.a Shader.o

clean:
	rm -f run
	rm -f *.o
	rm -f *.a