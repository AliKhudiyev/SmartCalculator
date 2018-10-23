#Comments

CXX = g++
CXXFLAGS = -W
CC = gcc
CCFLAGS = -W
LFLAG = -lm
RM = rm -f

LBRS = iaos.hpp
SRCS = srmain.cpp iaos.cpp
OBJS = srmain.o iaos.o
#INCLUDES = 

EXEC = iaos

info = "The makefile created to compile and run c/c++ programs.\n\
		Easily managable/updatable with many detailed macros.\n\
		Filled with lots of options to have more control over programs.\n\
		Options : \n\
		-1. make(or make exec) : gives the final executable file\n\
		-2. \n\
		-3. make clean : removes everything named\n\
		-4. make what : shows the version of current makefile"
version = "Makefile version : 1.0"

interface : srmain.o
	$(CXX) $(CXXFLAGS) srmain.o -o smreader

srmain.o : srmain.cpp smreader.hpp exception.hpp
	$(CXX) $(CXXFLAGS) -c srmain.cpp -o srmain.o

iaos : srmain.o iaos.o
	$(CXX) $(CXXFLAGS) srmain.o iaos.o -o iaos

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $(LFLAGS) $^ -o $@

clean :
	$(RM)

info :
	@echo $(info)

what :
	@echo $(version)