#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include<random>

using namespace std;


class neuron{
public:
	neuron(vector<float> tw,float bias);
	neuron(int);
	~neuron();
	void setWeights(vector<float>);
	void setBias(float);

	vector<float> getWeights();
	float getBias();
	int getNumberOfInputs();
	float sigmoid(float);				
	float dsigmoid(float);					
	float activateFunc(vector <float >);			
	float resultFunc(vector <float >);	
	void operator()(vector<float> pi) { resultFunc(pi); }
;	
protected:
	vector<float> Weights;
	float Bias;
};
