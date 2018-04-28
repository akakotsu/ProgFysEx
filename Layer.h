#pragma once
#include"Neuron.h"
#include<stdexcept>

class layer {
public:
	layer(vector<vector<fp>>, vector<fp>,bool);
	layer(int,int,bool);
	~layer();

	void setWeights(vector<vector<fp>>);
	void setBias(vector<fp>);

	vector<vector<fp>> getWeights();
	vector<fp> getBias();
	const int getNumberOfNeurons();
	vector<neuron*> getNeurons();
	vector<fp> resultFunc(vector<fp>);
	vector<float> dsigmoid(vector<fp>);
	vector<fp> operator()(vector<fp> LayerInput) { return resultFunc(LayerInput); }

protected:
	vector<neuron> Neurons;
	bool FirstLayer;
	int NumberOfNeurons;
	int NumberOfInputs;
};