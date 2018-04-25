#include "Neuron.h"

neuron::neuron(vector<float*> WeightVector, float* BiasNumber)
{
	setWeights(WeightVector);
	setBias(BiasNumber);
}

neuron::neuron(signed int WeightVectorSize)
{
	Weights.resize(WeightVectorSize);
	for (int i = 0; i < WeightVectorSize; i++)
	{
		random_device RandomDevice; //Initializes random engine
		mt19937 Generator(RandomDevice()); //Mersenne Twister 19937 generator, rng
		uniform_real_distribution<> Distribution(-1, 1); //uniform probability distribution
		Weights[i] = Distribution(Generator); //Generate random weights
	}
}


neuron::~neuron()
{
}

void neuron::setWeights(vector<float*> WeightVector)
{
	Weights.resize(WeightVector.size());
	for (int i = 0; i < WeightVector.size(); i++)
	{
		Weights[i] = *WeightVector[i];
	}
}

void neuron::setBias(float* BiasNumber)
{
	Bias = *BiasNumber;
}

vector<float>* neuron::getWeights()
{
	return &Weights;
}

float* neuron::getBias()
{
	return &Bias;
}

const signed int neuron::getNumberOfInputs()
{
	return Weights.size();
}

float neuron::sigmoid(float z)
{
	return 1 / (1 + exp(-z));
}

float neuron::dsigmoid(float z)
{
	return sigmoid(z)*(1 - sigmoid(z));
}

float neuron::activateFunc(vector<float*> input)
{
	float Sum = 0;
	for (int i = 0; i < input.size(); i++)
	{
		Sum += Weights[i] * *input[i]; //w.x dot product
	}
	Sum += Bias;
	return Sum;
}

float* neuron::resultFunc(vector<float*> input)
{
	Output = sigmoid(activateFunc(input));
	return  &Output;
}

