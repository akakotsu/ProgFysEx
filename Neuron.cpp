#include "Neuron.h"

neuron::neuron(vector<fp> WeightVector, fp BiasNumber)
{
	setWeights(WeightVector);
	setBias(BiasNumber);
}

neuron::neuron(int WeightVectorSize)
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

void neuron::setWeights(vector<fp> WeightVector)
{
	Weights.resize(WeightVector.size());
	for (int i = 0; i < WeightVector.size(); i++)
	{
		Weights[i] = *WeightVector[i];
	}
}

void neuron::setBias(fp BiasNumber)
{
	Bias = *BiasNumber;
}

vector<fp> neuron::getWeights()
{
	vector<fp> TempWeights(Weights.size());
	for (int i = 0; i < Weights.size(); i++)
	{
		TempWeights[i] = &Weights[i];
	}
	return TempWeights;
}

fp neuron::getBias()
{
	return &Bias;
}

const int neuron::getNumberOfInputs()
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

float neuron::activateFunc(vector<fp> input)
{
	float Sum = 0;
	for (int i = 0; i < input.size(); i++)
	{
		Sum += Weights[i] * *input[i]; //w.x dot product
	}
	Sum += Bias;
	return Sum;
}

fp neuron::resultFunc(vector<fp> input)
{
	Output = sigmoid(activateFunc(input));
	return  &Output;
}

