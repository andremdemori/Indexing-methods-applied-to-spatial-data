# Makefile for GCC
#
# Author: Marcos Rodrigues Vieira
# Author: Fabio Jun Takada Chino
#
CC=gcc
CFLAGS=
INCLUDEPATH=../../include
LIBPATH=-L../../lib
INCLUDE=-I$(INCLUDEPATH)
LIBS=-lstdc++ -lm -larboretum
SRC= app.cpp Stars.cpp star.cpp
OBJS=$(subst .cpp,.o,$(SRC))


# Implicit Rules
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

Stars: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o Stars $(INCLUDE) $(LIBPATH) $(LIBS)
