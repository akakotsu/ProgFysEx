#include "Neuron.h"

neuron::neuron(vector<float> tw,float bias)
{
	setWeights(tw);
	setBias(bias);
}

neuron::neuron(signed int size)
{
	Weights.resize(size);
	for (int i = 0; i < size; i++)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> dis(0, 1);
		Weights[i] = dis(gen);
	}
}


neuron::~neuron()
{
}

void neuron::setWeights(vector<float> w)
{
	Weights = w;
}

void neuron::setBias(float b)
{
	Bias = b;
}

vector<float> neuron::getWeights()
{
	return Weights;
}

float neuron::getBias()
{
	return Bias;
}

const signed int neuron::getNumberOfInputs()
{
	return Weights.size();
}

float neuron::sigmoid(float z)
{
	return (1 / (1 + exp(-z)));
}

float neuron::dsigmoid(float z)
{
	return sigmoid(z)*(1 - sigmoid(z));
}

float neuron::activateFunc(vector<float> input)
{
	float temp = 0;
	for (int i = 0; i < input.size(); i++) 
	{
		temp += Weights[i] * input[i];
	}
	temp += Bias;
	return temp;
}

float neuron::resultFunc(vector<float> input) 
{
	return sigmoid(activateFunc(input));
}