#include "Neuron.h"

neuron::neuron(vector<float> WeightVector, float BiasNumber)
{
	setWeights(WeightVector);
	setBias(BiasNumber);
}

neuron::neuron(int WeightVectorSize)
{
	Weights.resize(WeightVectorSize);
	for (vector<float>::iterator i = Weights.begin(); i != Weights.end(); i++)
	{
		*i = randomize(-1, 1);
	}

	Bias = randomize(-1, 1);
}


neuron::~neuron()
{
}

neuron::neuron(const neuron &Neuron1)
{
	Weights = Neuron1.Weights;
	Bias = Neuron1.Bias;
	Output = Neuron1.Output;
}

neuron& neuron::operator = (const neuron& Neuron1)
{
	if (&Neuron1 != this)
	{
		Weights = Neuron1.Weights;
		Bias = Neuron1.Bias;
		Output = Neuron1.Output;
	}
	return *this;
}

void neuron::setWeights(vector<float> WeightVector)
{
	Weights = WeightVector;
	/*Weights.resize(WeightVector.size());
	for (int i = 0; i < WeightVector.size(); i++)
	{
		Weights[i] = *WeightVector[i];
	}*/
}

void neuron::setBias(float BiasNumber)
{
	Bias = BiasNumber;
}

float neuron::randomize(float Minimum, float Maximum)
{
	random_device RandomDevice; //Initializes random engine
	mt19937 Generator(RandomDevice()); //Mersenne Twister 19937 generator, rng
	uniform_real_distribution<float> Distribution(Minimum, Maximum); //uniform probability distribution between Minimum and Maximum
	return Distribution(Generator); //Generate random weights
}

vector<float> neuron::getWeights()
{
	/*vector<fp> TempWeights(Weights.size());
	for (int i = 0; i < Weights.size(); i++)
	{
		TempWeights[i] = &Weights[i];
	}*/
	return Weights;
}

float neuron::getBias()
{
	return Bias;
}

const int neuron::getNumberOfInputs()
{
	return Weights.size();
}

float* neuron::sigmoid(float* z)
{
	*z = 1 / (1 + exp(-*z));
	return z;
}

float* neuron::dsigmoid(float* z)
{
	float temp = *sigmoid(z);
	*z = temp*(1 - temp);
	return z;
}


float* neuron::activateFunc(vector<float*> input)
{
	Output = 0;
	/*for (int i = 0; i < input.size(); i++)
	{
		Output += Weights.at(i) * *input[i]; //w.x dot product
	}
	Output += Bias;*/
	vector<float> TInput(input.size());
	std::transform(input.begin(), input.end(), TInput.begin(), [](float* Element)->float {return *Element; });
	Output = std::inner_product(Weights.begin(), Weights.end(), TInput.begin(), Bias);

	return &Output;
}

float* neuron::resultFunc(vector<float*> input)
{
	Output = *sigmoid(activateFunc(input));
	return  &Output;
}

