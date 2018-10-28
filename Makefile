CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=main
SRCS=main.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp
INCLUDES=gl_framework.hpp shader_util.hpp main.hpp hierarchy_node.hpp box.cpp cylinder.cpp ellipsoid.cpp humanoid.cpp opening_box.cpp r2d2.cpp room.cpp door.cpp drawer.cpp cupboard.cpp bed.cpp bed_base.cpp bed_headrest.cpp bed_mattress.cpp textured_cuboid.cpp table.cpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
