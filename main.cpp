#include "Neuron.h"


int main() {
	float x = 1;
	float y = 0;
	//float* px = &x; 
	//float* py = &y;
	neuron pi(2);
	//cout << (*pi.getWeights())[0] << endl;
	cout << *pi.resultFunc({ &x,&y })<<endl;
	//system("pause");
	return 0;
}
