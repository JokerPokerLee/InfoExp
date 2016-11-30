#ifndef _BOOLFUNC_H_
#define _BOOLFUNC_H_

#include "source.h"

using namespace std;

class BoolFunc {

private:

	int n;
	vector< bitset<LENGTH> > pn;

	int getIdx(int x, int y) {
		if (x == y) {
			return x;
		}
		if (x > y) {
			swap(x, y);
		}
		return n + ((((n - 1) + (n - x)) * x) / 2 + (y - x - 1));
	}

public:

	BoolFunc(int n) : n(n) {}
	int addPN(vector<int> idx);
	int calc(bitset<LENGTH> state);
	bitset<FORLEN> calc(bitset<LENGTH> state[LENGTH]);
	void print();
};

#endif