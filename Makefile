
#Makefile 

SHELL = /bin/bash
#Compiler
COMPILER = g++ -g -std=c++11 -Wall
#Macros not necessary


all:Neuron#,Layers

Neuron: Neuron.o main.o
	$(COMPILER) Neuron.o main.o -o Neuron
	
Layers: Layer.o main.o
	$(COMPILER)  Layers.o main.o -o Layers

main.o: main.cpp Neuron.h #Layers.h
	$(COMPILER) main.cpp -c

Neuron.o: Neuron.cpp Neuron.h
	$(COMPILER) Neuron.cpp -c
	
Layers.o: Layers.cpp Layers.h
	$(COMPILER) -c Layers.cpp

clean : 
	rm *.o Neuron #Layers
	


