#ifndef _GAUSSELIM_H_
#define _GAUSSELIM_H_

#include "source.h"

using namespace std;

class GaussElim {

private:
	bool tw;
	int n, ori;
	vector<int> v;
	vector< bitset<FORLEN> > func;

public:
	GaussElim(int n) : n(n) {
		tw = false;
	}
	void setTw() {
		ori = n;
		n = n * (n + 1) / 2;
		tw = true;
	}
	void addFunc(bitset<FORLEN> newFunc);
	int funcNum();
	int solve();
	void print();
	void printKey();
};

#endif