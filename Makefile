
#Makefile 

SHELL = /bin/bash
#Compiler
COMPILER = g++ -g -std=c++11 -Wall
#Macros not necessary


all:Neuron#,Layers

Neuron: Neuron.o,main.o
	$(COMPILER) -o Neuron.o main.o Neuron
	
Layers: Layer.o,main.o
	$(COMPILER) -o Layers.o main.o Layers

main.o: main.cpp Neuron.h #Layers.h
	$(COMPILER) -c main.cpp

Neuron.o: Neuron.cpp Neuron.h
	$(COMPILER) -c Neuron.cpp
	
Layers.o: Layers.cpp Layers.h
	$(COMPILER) -c Layers.cpp

clean : 
	rm %.o Neuron #Layers
	


