MAKE ?= make
CP ?= cp

#SOURCES += ./libs/imgui_impl_sdl.cpp ./libs/imgui_impl_opengl3.cpp
#SOURCES += ./imgui.cpp ./imgui_demo.cpp ./imgui_draw.cpp ./imgui_widgets.cpp
#OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

#$(info ${OBJS})
#$(info ${SOURCES})

CXXFLAGS = -I./examples -I./
CXXFLAGS += -g -Wall -Wformat

LIBS += -lGL -ldl `sdl2-config --libs`

CXXFLAGS += `sdl2-config --cflags`
CFLAGS = $(CXXFLAGS)


all:
	$(CP) ./examples/imgui_impl_glfw.cpp .
	$(CP) ./examples/imgui_impl_glfw.h .
	$(CP) ./examples/imgui_impl_opengl3.cpp  .	
	$(CP) ./examples/imgui_impl_opengl3.h  .	


	$(CXX) $(CXXFLAGS) -c -o ./imgui_impl_sdl.o ./imgui_impl_glfw.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -c -o ./imgui_impl_opengl3.o ./imgui_impl_opengl3.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -c -o ./imgui.o ./imgui.cpp  $(LIBS)
	$(CXX) $(CXXFLAGS) -c -o ./imgui_demo.o ./imgui_demo.cpp  $(LIBS)
	$(CXX) $(CXXFLAGS) -c -o ./imgui_draw.o ./imgui_draw.cpp  $(LIBS)
	$(CXX) $(CXXFLAGS) -c -o ./imgui_widgets.o ./imgui_widgets.cpp $(LIBS)

	$(AR)  rvs imgui.a *.o

clean:
	rm -f *.o
	rm -f *.a

	rm ./imgui_impl_glfw.cpp
	rm ./imgui_impl_glfw.h
	rm ./imgui_impl_opengl3.cpp	
	rm ./imgui_impl_opengl3.h	

#all:
#	$(MAKE) -C examples/example_glfw_opengl3
#clean:
#	$(MAKE) -C examples/example_glfw_opengl3 clean
