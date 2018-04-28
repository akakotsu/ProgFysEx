#include "Layer.h"

layer::layer(vector<vector<fp>>LayerWeights, vector<fp> LayerBias, bool FirstLayerParam)
{
	if (LayerWeights.size() != LayerBias.size())
	{
		throw invalid_argument("Both constructor inputs must be the same size");
	}
	if (FirstLayerParam == true && LayerWeights[0].size() != 1)
	{
		throw invalid_argument("First layer can only have 1 input per neuron");
	}
	for (int i = 0; i < LayerBias.size(); i++)
	{
		Neurons.push_back(neuron(LayerWeights[i], LayerBias[i]));
	}
	FirstLayer = FirstLayerParam;
	NumberOfNeurons = LayerBias.size();
	NumberOfInputs = LayerWeights[0].size(); //Because it is a priori known that every neuron takes an equal amount of inputs
}

layer::layer(int InitNumberOfNeurons, int InitNumberOfInputs, bool FirstLayerParam)
{
	//in every layer each neuron has the same amount of inputs and thus the same amount of weights
	if (InitNumberOfNeurons <= 0 || InitNumberOfInputs <= 0)
	{
		throw invalid_argument("Both constructor inputs must be a positive integer");
	}
	if (FirstLayerParam == true && InitNumberOfInputs != 1)
	{
		throw invalid_argument("First layer can only have 1 input per neuron");
	}
	Neurons.assign(InitNumberOfNeurons, neuron(InitNumberOfInputs));
	FirstLayer = FirstLayerParam;
	NumberOfNeurons = InitNumberOfNeurons;
	NumberOfInputs = InitNumberOfInputs;
}

layer::~layer()
{

}

layer::layer(const layer &Layer1)
{
	/*Neurons = Layer1.Neurons;
	FirstLayer = Layer1.FirstLayer;
	NumberOfNeurons = Layer1.NumberOfNeurons;
	NumberOfInputs = Layer1.NumberOfInputs;*/
}

layer& layer::operator = (const layer& Layer1)
{
	/*if (&Layer1 != this)
	{
		Neurons = Layer1.Neurons;
		FirstLayer = Layer1.FirstLayer;
		NumberOfNeurons = Layer1.NumberOfNeurons;
		NumberOfInputs = Layer1.NumberOfInputs;
	}*/
	return *this;
}

void layer::setWeights(vector<vector<fp>> LayerWeights)
{
	if (LayerWeights.size() != NumberOfNeurons || LayerWeights[0].size() != NumberOfInputs)
	{
		throw invalid_argument("SetWeights():input has the wrong dimensions");
	}
	for (int i = 0; i < LayerWeights.size(); i++)
	{
		Neurons[i].setWeights(LayerWeights[i]);
	}
}

void layer::setBias(vector<fp> LayerBias)
{
	if (LayerBias.size() != NumberOfNeurons)
	{
		throw invalid_argument("setBias(): input has the wrong dimension");
	}
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
	return NumberOfNeurons;
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

vector<fp> layer::resultFunc(vector<fp> LayerInput)
{
	vector<fp> LayerOutput(NumberOfNeurons);
	if (FirstLayer == true)
	{
		if (LayerInput.size() != NumberOfNeurons)
		{
			throw invalid_argument("resultFunc(): input has the wrong dimension");
		}

		//Because every Neuron in the first layer has only one weight/input
		for (int i = 0; i < NumberOfNeurons; i++)
		{
			LayerOutput[i] = Neurons[i].resultFunc( { LayerInput[i] } );
		}
	}
	else
	{
		if (LayerInput.size() != NumberOfInputs)
		{
			throw invalid_argument("resultFunc(): input has the wrong dimension");
		}

		//Because every Neuron in the has the same input: all the outputs of the previous layer 
		for (int i = 0; i < NumberOfNeurons; i++)
		{
			LayerOutput[i] = Neurons[i].resultFunc(LayerInput);
		}
	}
	return LayerOutput;
}

vector<float> layer::dsigmoid(vector<fp> Input)
{
	//same reasoning as in resultFunc
	vector<float> DSigmoidOutput(NumberOfNeurons);
	float z;
	if (FirstLayer == true)
	{
		if (Input.size() != NumberOfNeurons)
		{
			throw invalid_argument("dsigmoid(): input has the wrong dimension");
		}
		for (int i = 0; i < NumberOfNeurons; i++)
		{
			z = Neurons[i].activateFunc({ Input[i] });
			DSigmoidOutput[i] = Neurons[i].dsigmoid(z);
		}
	}
	else
	{
		if (Input.size() != NumberOfInputs)
		{
			throw invalid_argument("dsigmoid(): input has the wrong dimension");
		}
		for (int i = 0; i < NumberOfNeurons; i++)
		{
			z = Neurons[i].activateFunc(Input);
			DSigmoidOutput[i] = Neurons[i].dsigmoid(z);
		}
	}
	return DSigmoidOutput;
}