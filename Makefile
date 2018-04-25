
#Makefile 

SHELL = /bin/bash
#Compiler
COMPILER = g++ -g -std=c++11 -Wall
#Macros


all:Neuron


Neuron: Neuron.cpp main.cpp
	$(COMPILER) Neuron.cpp main.cpp -o Neuron

clean : 
	rm Neuron
	


