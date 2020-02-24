CXX ?= g++
AR  ?= ar
MAKE ?= make

LIBS := -lGL    \
		-lGLU   \
		-lGLEW  \
		-lglfw

BUILT_LIBS := Renderer.a \
			  VertexBuffer.a \
			  IndexBuffer.a \
			  VertexArray.a

# 
# -lglut

all:
	$(MAKE) libs
	$(CXX) main.cpp -o run $(LIBS) $(BUILT_LIBS)

libs:
	$(CXX) -c Renderer.cpp
	$(CXX) -c VertexBuffer.cpp
	$(CXX) -c IndexBuffer.cpp
	$(CXX) -c VertexArray.cpp
	
	$(AR)  rvs Renderer.a Renderer.o
	$(AR)  rvs VertexBuffer.a VertexBuffer.o
	$(AR)  rvs IndexBuffer.a IndexBuffer.o
	$(AR)  rvs VertexArray.a VertexArray.o

clean:
	rm -f run
	rm -f *.o
	rm -f *.a