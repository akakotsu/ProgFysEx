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
	int WS = 1;
	vector<fp> FInput(NS);
	for (int j = 0; j < NS; j++)
	{
		FInput[j] = &x;
	}
	try {
		layer pi(NS, WS, true);

		//cout << pi.getNumberOfNeurons() << endl;
		//cout << *pi.getWeights()[0][0] << endl;
		//pi.setWeights(pi.getWeights());
		//cout << *pi.getWeights()[0][0] << endl;
		//cout << *pi.resultFunc({ { &x,&y },{&y,&x} })[0] << endl;
		vector<vector<fp>> LW = pi.getWeights();
		
		vector<fp> LB = pi.getBias();
		
		int loopsize = 100;
		for (int i = 0; i < loopsize; i++)
		{
			cout << "loop: " << i << endl;
			for (int j = 0; j < NS; j++)
			{
				
				for (int k = 0; k < WS; k++)
				{
					*LW[j][k] = randomize(-1, 1);
				}
				*LB[j] = randomize(-1, 1);
			}
			cout << "Result: " << *pi(FInput)[0] << endl;

		}
	}
catch (const invalid_argument& e)
{
	cout << e.what() << endl;

}
	auto end = std::chrono::system_clock::now();
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
	return 0;
}
