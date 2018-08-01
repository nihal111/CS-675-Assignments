
UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S),Darwin)
  CC := clang++ -arch x86_64
  OPENGLLIB := -framework OpenGL
  LDFLAGS := 
  CPPFLAGS := -I./
  CFLAGS := -std=c++11
else
  CC := g++
  OPENGLLIB := -lGL
  LDFLAGS := 
  CPPFLAGS := -I./
  CFLAGS := -std=c++11
endif



GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)

BIN=mydraw.out
SRCS=main.cpp gl_framework.cpp shader_util.cpp canvas.cpp primitive.cpp fill.cpp color.cpp brush.cpp
INCLUDES=gl_framework.hpp shader_util.hpp canvas.hpp primitive.hpp fill.hpp color.hpp brush.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
