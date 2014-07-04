#
# Makefile for the lightem library
#

# set compiler and linker
CC = g++
LD = g++

# binaries and folders
BINDIR = bin
LIBDIR = lib
LIBRARYNAME=liblightem
TEST = $(BINDIR)/test
LIBNAME = $(LIBRARYNAME).so
LIB = $(LIBDIR)/$(LIBNAME)
LIBNAME_S = $(LIBRARYNAME).a
STATIC = $(LIBDIR)/$(LIBNAME_S)

# set library and include paths
INCLUDE =  -I. -I/usr/local/include
TESTLIBS = -lgtest -lgtest_main -lpthread
LIBS =

# set compiler and linker flags
CCFLAGS = -fPIC -O3 -W -Wall
LDFLAGS = -L/usr/local/lib

# source files
SRCS =  $(wildcard ./*.cpp)
HEADERS = $(wildcard ./*.h)

# test source files
TESTSRCS = $(SRCS)
TESTSRCS += $(wildcard tests/test_lightem*.cpp)

# dependencies
# object files
OBJS = $(SRCS:.cpp=.o)
TESTOBJS = $(TESTSRCS:.cpp=.o)

# linking rule
$(TEST): $(TESTOBJS) $(BINDIR)
	$(LD) $(LDFLAGS) $(TESTOBJS) -o $(TEST) $(TESTLIBS)

# dynamic lib rule
$(LIB): $(OBJS) $(LIBDIR)
	$(LD) $(LDFLAGS) -shared -soname,$(LIBNAME) -o $(LIB) $(OBJS) $(LIBS)

# static lib rule
$(STATIC): $(OBJS) $(LIBDIR)
	ar rcs $(STATIC) $(OBJS)

# compile rule
%.o:%.cpp $(HEADERS)
	$(CC) $(CCFLAGS) $(INCLUDE) -c $<  -o $@

$(BINDIR):
	@mkdir -p $(BINDIR)

$(LIBDIR):
	@mkdir -p $(LIBDIR)

# tasks
.PHONY:  clean

clean:
	@rm -rf tests/*.o
	@rm -rf *.o
	@rm -rf bin
	@rm -rf lib

test: $(TEST)
	@./bin/test

dynamiclibrary: $(LIB)

staticlibrary: $(STATIC)
