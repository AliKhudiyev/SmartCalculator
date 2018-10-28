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
		-1. make(or make interface) : gives the final executable file for reader\n\
		-2. make iaos : gives the final executable file for iaos\n\
		-3. make clean : removes everything named\n\
		-4. make what : shows the version of current makefile"

version = "Makefile version : 1.0"

interface : srmain.o
	$(CXX) $(CXXFLAGS) srmain.o -o reader

iaos : iaos.o calculator.o operator.o list.o srmain.o
	$(CXX) $(CXXFLAGS) iaos.o calculator.o operator.o list.o srmain.o -o iaos

srmain.o : srmain.cpp iaos.hpp smreader.hpp calculator.hpp operator.hpp exception.hpp
	$(CXX) $(CXXFLAGS) -c srmain.cpp -o srmain.o

iaos.o : iaos.cpp iaos.hpp smreader.hpp calculator.hpp operator.hpp exception.hpp
	$(CXX) $(CXXFLAGS) -c iaos.cpp -o iaos.o

calculator.o : calculator.cpp calculator.hpp operator.hpp
	$(CXX) $(CXXFLAGS) -c calculator.cpp -o calculator.o

operator.o : operator.cpp operator.hpp exception.hpp
	$(CXX) $(CXXFLAGS) -c operator.cpp -o operator.o

list.o : list.cpp list.hpp operator.hpp exception.hpp
	$(CXX) $(CXXFLAGS) -c list.cpp -o list.o

clean :
	$(RM)

info :
	@echo $(info)

what :
	@echo $(version)