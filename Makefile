CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=main
SRCS=main.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp
INCLUDES=gl_framework.hpp shader_util.hpp main.hpp hierarchy_node.hpp box.cpp cylinder.cpp ellipsoid.cpp humanoid.cpp opening_box.cpp r2d2.cpp furniture/room.cpp furniture/door.cpp furniture/drawer.cpp furniture/cupboard.cpp furniture/bed.cpp furniture/bed_base.cpp furniture/bed_headrest.cpp furniture/bed_mattress.cpp furniture/table.cpp furniture/chair.cpp furniture/window.cpp furniture/wall_light.cpp furniture/lamp.cpp quad.cpp recorder.cpp playback.cpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
