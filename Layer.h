#pragma once
#include"Neuron.h"

class layer {
public:
	layer(vector<vector<fp>>, vector<fp>);
	layer(int,int);
	~layer();

	void setWeights(vector<vector<fp>>);
	void setBias(vector<fp>);

	vector<vector<fp>> getWeights();
	vector<fp> getBias();
	const int getNumberOfNeurons();
	vector<fp> resultFunc(vector<vector<fp>>);
	vector<float> dsigmoid(vector<float>);

protected:
	vector<neuron> Neurons;
};