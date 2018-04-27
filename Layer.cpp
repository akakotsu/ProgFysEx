#include "Layer.h"

layer::layer(vector<vector<fp>>LayerWeights, vector<fp> LayerBias)
{
	for (int i = 0; i < LayerBias.size(); i++)
	{
		Neurons.push_back(neuron(LayerWeights[i], LayerBias[i]));
	}
}

layer::layer(int NumberOfNeurons, int NumberOfInputs)
{
	Neurons.assign(NumberOfNeurons, neuron(NumberOfInputs));
}

layer::~layer()
{

}

void layer::setWeights(vector<vector<fp>> LayerWeights)
{
	for (int i = 0; i < LayerWeights.size(); i++)
	{
		Neurons[i].setWeights(LayerWeights[i]);
	}
}

void layer::setBias(vector<fp> LayerBias)
{
	for (int i = 0; i < LayerBias.size(); i++)
	{
		Neurons[i].setBias(LayerBias[i]);
	}
}

vector<vector<fp>> layer::getWeights()
{
	vector<vector<fp>> LayerWeights(Neurons.size());
	for (int i = 0; i < Neurons.size(); i++)
	{
		LayerWeights[i] = Neurons[i].getWeights();
	}
	return LayerWeights;
}

vector<fp> layer::getBias()
{
	vector<fp> LayerBias(Neurons.size());
	for (int i = 0; i < Neurons.size(); i++)
	{
		LayerBias[i] = Neurons[i].getBias();
	}
	return LayerBias;
}

const int layer::getNumberOfNeurons()
{
	return Neurons.size();
}

vector<fp> layer::resultFunc(vector<vector<fp>> LayerInput)
{
	vector<fp> LayerOutput(LayerInput.size());
	for (int i = 0; i < LayerInput.size(); i++)
	{
		LayerOutput[i] = Neurons[i].resultFunc(LayerInput[i]);
	}
	return LayerOutput;
}

vector<float> layer::dsigmoid(vector<float> z)
{
	vector<float> DSigmoidOutput(z.size());
	for (int i = 0; i < z.size(); i++)
	{
		DSigmoidOutput[i] = Neurons[i].dsigmoid(z[i]);
	}
	return DSigmoidOutput;
}