
.SUFFIXES: .cpp .hpp

######################################

# Project Name (generate executable with this name)
TARGET = mydraw.out

# Project Paths
PROJECT_ROOT:=.
SRCDIR := $(PROJECT_ROOT)/src
INCDIR := $(PROJECT_ROOT)/include

SRCS:=$(wildcard $(SRCDIR)/*.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS)))
DEPS:=$(patsubst %.cpp,%.d,$(filter %.cpp,$(SRCS)))

######################################

UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S),Darwin)
  CC := clang++ -arch x86_64
  SHELL := bash
  RM := rm
  ECHO := /bin/echo
  CAT := cat
  PRINTF := printf
  SED := sed
  OPENGLLIB := -framework OpenGL
  LDFLAGS := 
  CPPFLAGS := -I$(INCDIR)
  CFLAGS := -std=c++11 -O3 -Wall -Wno-unused-function
else
  CC := g++
  SHELL := bash
  RM := rm
  ECHO := /bin/echo
  CAT := cat
  PRINTF := printf
  SED := sed
  OPENGLLIB := -lGL
  LDFLAGS := 
  CPPFLAGS := -I$(INCDIR)
  CFLAGS := -std=c++11 -O3 -Wall -Wno-unused-function
endif

GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"

######################################

.PHONY: all doc clean distclean

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include -include $(OBJS:.o=.d)

$(OBJS): %.o : %.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf *~ $(OBJS) $(DEPS) $(SRCDIR)/*~
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(TARGET) $(DOCDIR)/html scenes/*.ppm
