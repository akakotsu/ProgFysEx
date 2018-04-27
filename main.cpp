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
	vector<fp> FInput(WS);
	for (int j = 0; j < WS; j++)
	{
		FInput[j] = &x;
	}
	layer pi(NS,WS);
	//cout << *pi.getWeights()[0][0] << endl;
	//pi.setWeights(pi.getWeights());
	//cout << *pi.getWeights()[0][0] << endl;
	//cout << *pi.resultFunc({ { &x,&y },{&y,&x} })[0] << endl;
	vector<vector<fp>> LWP = pi.getWeights();
	vector<vector<float>> LW(LWP.size(), vector<float>(WS));
	vector<fp> LBP = pi.getBias();
	vector<float> LB(LBP.size());
	int loopsize = 10;
	float random1;
	float random2;
	for (int i=0; i < loopsize;i++)
	{
		cout << "loop: " << i << endl;
		for (int j = 0; j < NS; j++)
		{
			for (int k = 0; k < WS; k++)
			{
				//random1 = randomize(-1, 1);
				//cout << random1 << endl;
				LW[j][k] = randomize(-1, 1);
				LWP[j][k] = &LW[j][k];
			}
			//random2 = randomize(-1, 1);
			LB[j] = randomize(-1, 1);
			LBP[j] = &LB[j];
		}
		pi.setWeights(LWP);
		pi.setBias(LBP);
		cout << "Result: "<< *pi(FInput,false)[0] << endl;

	}
	auto end = std::chrono::system_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
	return 0;
}
