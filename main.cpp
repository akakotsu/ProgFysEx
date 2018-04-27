#include "Layer.h"
#include<chrono>

float randomize(float Minimum, float Maximum)
{
	random_device RandomDevice; //Initializes random engine
	mt19937 Generator(RandomDevice()); //Mersenne Twister 19937 generator, rng
	uniform_real_distribution<float> Distribution(Minimum, Maximum); //uniform probability distribution between Minimum and Maximum
	return Distribution(Generator); //Generate random weights
}

int main() {
	float x = 1;
	float y = 0;
	auto start = std::chrono::system_clock::now();
	int NS = 150;
	int WS = 728;
	vector<fp> input(WS);
	for (int i = 0; i < WS; i++)
	{
		input[i] =&x;
	}
	vector<vector<fp>> FInput(NS);
	for (int j = 0; j < NS; j++)
	{
		FInput[j] = input;
	}
	layer pi(NS,WS);
	//cout << *pi.getWeights()[0][0] << endl;
	//pi.setWeights(pi.getWeights());
	//cout << *pi.getWeights()[0][0] << endl;
	//cout << *pi.resultFunc({ { &x,&y },{&y,&x} })[0] << endl;
	vector<vector<fp>> LW = pi.getWeights();
	vector<fp> LB = pi.getBias();
	int loopsize = 100;
	float random1;
	float random2;
	for (int i=0; i < loopsize;i++)
	{
		cout << "loop: " << i << endl;
		for (int j = 0; j < NS; j++)
		{
			for (int k = 0; k < WS; k++)
			{
				random1 = randomize(-10, 10);
				LW[j][k] = &random1;
			}
			random2 = randomize(-10, 10);
			LB[j] = &random2;
		}
		pi.setWeights(LW);
		pi.setBias(LB);
		pi.resultFunc(FInput);
	}
	auto end = std::chrono::system_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
	return 0;
}
