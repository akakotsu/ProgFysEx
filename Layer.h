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
	vector<neuron*> getNeurons();
	vector<fp> resultFunc(vector<fp>,bool);
	vector<float> dsigmoid(vector<fp>,bool);
	vector<fp> operator()(vector<fp> LayerInput, bool FirstLayer) { return resultFunc(LayerInput, FirstLayer); }

protected:
	vector<neuron> Neurons;
};