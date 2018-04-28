#pragma once
#include"Neuron.h"
#include<stdexcept>

class layer {
public:
	layer(vector<vector<fp>>, vector<fp>,bool); //Constructor1, weights and biases provided
	layer(int,int,bool); //Constructor2, random initialization of weights and biases
	~layer(); //default destructor
	

	void setWeights(vector<vector<fp>>); //set-function for Weights across a layer
	void setBias(vector<fp>); //set-function for bias across a layer


	vector<vector<fp>> getWeights(); //get-function to provide access to weights
	vector<fp> getBias(); //get-function to provide access to bias
	const int getNumberOfNeurons(); //get-function to provide access  to number of neurons
	vector<neuron*> getNeurons(); //get-function to provide access to individual neurons
	vector<fp> resultFunc(vector<fp>); // calculates the output vector of the layer.
	vector<float> dsigmoid(vector<fp>); //calculates the derivative of sigmoid
	vector<fp> operator()(vector<fp> LayerInput) { return resultFunc(LayerInput); }

protected:
	vector<neuron> Neurons;
	bool FirstLayer; //Necessary to define how the input vector in resultFunc and dsigmoid is read
	int NumberOfNeurons;
	int NumberOfInputs;

	layer(const layer&); //Copy constructor, don't use. Use constructor instead
	layer& operator = (const layer&); //Assignment constructor, don't use. Use constructor instead
};