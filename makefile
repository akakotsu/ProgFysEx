#Jago Coric
#s0140128
#makefile
#Due date: 30/03/2018

SHELL = /bin/bash
#Compiler
COMPILER = g++ -g -std=c++11 -Wall
#Macros
#CFLAGS = $(shell root-config --cflags)
#LIBS = $(shell root-config --libs)

#CPPFLAGS = $(shell pkg-config --cflags opencv)
#LDLIBS = $(shell pkg-config --libs opencv)


all: neuron 

#make ocr
neuron: main.o Neuron.o Neuron.h
	$(COMPILER) $^ -o $@ 

neuron.o: Neuron.cpp Neuron.h 
	$(COMPILER) -c $< 

main.o: main.cpp Neuron.h Neuron.cpp
	$(COMPILER) -c $<






#clean up
clean:
	rm neuron *\.o

#git add files
gitadd:
	git add neuron.cpp neuron.h
