#include "Layer.h"

layer::layer(vector<vector<float>>LayerWeights, vector<float> LayerBias, bool FirstLayerParam)
{
	if (LayerWeights.size() != LayerBias.size())
	{
		throw invalid_argument("Both constructor inputs must be the same size");
	}
	if (FirstLayerParam == true && LayerWeights.at(0).size() != 1)
	{
		throw invalid_argument("First layer can only have 1 input per neuron");
	}

	FirstLayer = FirstLayerParam;
	NumberOfNeurons = LayerBias.size();
	NumberOfInputs = LayerWeights.at(0).size(); //Because it is a priori known that every neuron takes an equal amount of inputs

	Neurons.reserve(NumberOfNeurons);
	for (int i = 0; i < NumberOfNeurons; ++i) //let's not use iterators here, shall we?
	{
		Neurons.push_back(neuron(LayerWeights.at(i), LayerBias.at(i) ));
	}

	

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
	//Neurons.assign(InitNumberOfNeurons, neuron(InitNumberOfInputs));
	FirstLayer = FirstLayerParam;
	NumberOfNeurons = InitNumberOfNeurons;
	NumberOfInputs = InitNumberOfInputs;

	Neurons.reserve(NumberOfNeurons);
	for (int i = 0; i < NumberOfNeurons; ++i) //let's not use iterators here, shall we?
	{
		Neurons.push_back(neuron(NumberOfInputs));
	}

	
}

layer::~layer()
{

}

layer::layer(const layer &Layer1)
{
	Neurons = Layer1.Neurons;
	FirstLayer = Layer1.FirstLayer;
	NumberOfNeurons = Layer1.NumberOfNeurons;
	NumberOfInputs = Layer1.NumberOfInputs;
}

layer& layer::operator = (const layer& Layer1)
{
	if (&Layer1 != this)
	{
		Neurons = Layer1.Neurons;
		FirstLayer = Layer1.FirstLayer;
		NumberOfNeurons = Layer1.NumberOfNeurons;
		NumberOfInputs = Layer1.NumberOfInputs;
	}
	return *this;
}

void layer::setWeights(vector<vector<float>> LayerWeights)
{
	if (LayerWeights.size() != NumberOfNeurons || LayerWeights.at(0).size() != NumberOfInputs)
	{
		throw invalid_argument("SetWeights():input has the wrong dimensions");
	}
	/*for (int i = 0; i < LayerWeights.size(); ++i)
	{
		Neurons[i].setWeights( LayerWeights.at(i) );
	}*/

	int count = 0;
	std::for_each(Neurons.begin(), Neurons.end(),
		[&](neuron &Neuron) {
		Neuron.setWeights(LayerWeights.at(++count));
	});
}

void layer::setBias(vector<float> LayerBias)
{
	if (LayerBias.size() != NumberOfNeurons)
	{
		throw invalid_argument("setBias(): input has the wrong dimension");
	}
	/*for (int i = 0; i < LayerBias.size(); ++i)
	{
		Neurons[i].setBias( LayerBias.at(i) );
	}*/

	int count = 0;
	std::for_each(Neurons.begin(), Neurons.end(),
		[&](neuron &Neuron) {
		Neuron.setBias(LayerBias.at(++count));
	});
}

vector<vector<float>> layer::getWeights()
{
	vector<vector<float>> LayerWeights(Neurons.size());
	std::transform(Neurons.begin(), Neurons.end(), LayerWeights.begin(),
		[](neuron &Neuron) {
		return Neuron.getWeights();
	});
	/*for (int i = 0; i < Neurons.size(); ++i)
	{
		LayerWeights.at(i) = Neurons.at(i).getWeights();
	}*/
	return LayerWeights;
}

vector<float> layer::getBias()
{
	vector<float> LayerBias(Neurons.size());

	std::transform(Neurons.begin(), Neurons.end(), LayerBias.begin(), 
		[](neuron &Neuron) {
		return Neuron.getBias();
	});
	/*int it = 0;
	std::generate(LayerBias.begin(), LayerBias.end(),
		[&]() {
		return Neurons.at(it++).getBias();
	});*/
	/*for (int i = 0; i < Neurons.size(); ++i)
	{
		LayerBias.at(i) = Neurons.at(i).getBias();
	}*/
	return LayerBias;
}

const int layer::getNumberOfNeurons()
{
	return NumberOfNeurons;
}

vector<neuron> layer::getNeurons()
{
	
	return Neurons;
}

vector<float*> layer::resultFunc(vector<float*> LayerInput)
{
	vector<float*> LayerOutput(NumberOfNeurons);
	if (FirstLayer == true)
	{
		if (LayerInput.size() != NumberOfNeurons)
		{
			throw invalid_argument("resultFunc(): input has the wrong dimension");
		}

		//Because every Neuron in the first layer has only one weight/input

		int count = 0;
		std::transform(Neurons.begin(), Neurons.end(),LayerOutput.begin(),
			[&](neuron &Neuron) {
			return Neuron.resultFunc({ LayerInput.at(++count) });
		});

		/*for (int i = 0; i < NumberOfNeurons; ++i)
		{
			LayerOutput.at(i) = Neurons.at(i).resultFunc( { LayerInput.at(i) } );
		}*/

	}
	else
	{
		if (LayerInput.size() != NumberOfInputs)
		{
			throw invalid_argument("resultFunc(): input has the wrong dimension");
		}

		//Because every Neuron in the has the same input: all the outputs of the previous layer 
		/*for (int i = 0; i < NumberOfNeurons; ++i)
		{
			LayerOutput.at(i) = Neurons.at(i).resultFunc(LayerInput);
		}*/

		std::transform(Neurons.begin(), Neurons.end(),LayerOutput.begin(),
			[&](neuron &Neuron) {
			return Neuron.resultFunc(LayerInput);
		});
	}
	return LayerOutput;
}

vector<float> layer::dsigmoid(vector<float*> Input)
{
	//same reasoning as in resultFunc
	vector<float> DSigmoidOutput(NumberOfNeurons);
	float* z;
	if (FirstLayer == true)
	{
		if (Input.size() != NumberOfNeurons)
		{
			throw invalid_argument("dsigmoid(): input has the wrong dimension");
		}
		/*for (int i = 0; i < NumberOfNeurons; ++i)
		{
			z = Neurons.at(i).activateFunc({ Input.at(i) });
			DSigmoidOutput.at(i) = *Neurons.at(i).dsigmoid(z);
		}*/
		int count = 0;
		std::transform(Neurons.begin(), Neurons.end(), DSigmoidOutput.begin(),
			[&](neuron &Neuron) {
			z = Neuron.activateFunc({ Input.at(++count) });
			return *Neuron.dsigmoid(z);
		});
	}
	else
	{
		if (Input.size() != NumberOfInputs)
		{
			throw invalid_argument("dsigmoid(): input has the wrong dimension");
		}
		/*for (int i = 0; i < NumberOfNeurons; ++i)
		{
			z = Neurons.at(i).activateFunc(Input);
			DSigmoidOutput.at(i) = *Neurons.at(i).dsigmoid(z);
		}*/
		//int count = 0;
		std::transform(Neurons.begin(), Neurons.end(),DSigmoidOutput.begin(),
			[&](neuron &Neuron) {
			z = Neuron.activateFunc(Input);
			return *Neuron.dsigmoid(z);
		});
	}
	return DSigmoidOutput;
}