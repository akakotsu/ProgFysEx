#include "Neuron.h"


int main() {
	float x = 1;
	float y = 0;;
	neuron pi(2);
	cout << *pi.getWeights()[0] << endl;
	pi.setWeights(pi.getWeights());
	cout << *pi.getWeights()[0] << endl;
	cout << *pi.resultFunc({ &x,&y })<<endl;
	return 0;
}
