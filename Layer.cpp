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

vector<neuron*> layer::getNeurons()
{
	vector<neuron*> NeuronPTR(Neurons.size());
	for (int i = 0; i < Neurons.size(); i++)
	{
		NeuronPTR[i] = &Neurons[i];
	}
	return NeuronPTR;
}

vector<fp> layer::resultFunc(vector<fp> LayerInput,bool FirstLayer)
{
	vector<fp> LayerOutput(LayerInput.size());
	if (FirstLayer == true)
	{
		for (int i = 0; i < LayerInput.size(); i++)
		{
			LayerOutput[i] = Neurons[i].resultFunc( { LayerInput[i] } );
		}
	}
	else
	{
		for (int i = 0; i < LayerInput.size(); i++)
		{
			LayerOutput[i] = Neurons[i].resultFunc(LayerInput);
		}
	}
	return LayerOutput;
}

vector<float> layer::dsigmoid(vector<fp> Input,bool FirstLayer)
{
	vector<float> DSigmoidOutput(Input.size());
	float z;
	if (FirstLayer == true)
	{

		for (int i = 0; i < Input.size(); i++)
		{
			z = Neurons[i].activateFunc({ Input[i] });
			DSigmoidOutput[i] = Neurons[i].dsigmoid(z);
		}
	}
	else
	{
		for (int i = 0; i < Input.size(); i++)
		{
			z = Neurons[i].activateFunc(Input);
			DSigmoidOutput[i] = Neurons[i].dsigmoid(z);
		}
	}
	return DSigmoidOutput;
}