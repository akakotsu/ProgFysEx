#include "Layer.h"


int main() {
	float x = 1;
	float y = 0;;
	//layer pi(2,2);
	layer pi({ {&x,&y},{&y,&x} }, { &x,&x });
	cout << *pi.getWeights()[0][0] << endl;
	pi.setWeights(pi.getWeights());
	cout << *pi.getWeights()[0][0] << endl;
	cout << *pi.resultFunc({ { &x,&y },{&y,&x} })[0] << endl;
	return 0;
}
