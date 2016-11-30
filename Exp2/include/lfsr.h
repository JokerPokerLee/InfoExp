#ifndef _LFSR_H_
#define _LFSR_H_

#include "source.h"

using namespace std;

class LFSR {

private:
	int m;
	bitset<LENGTH> reg;
	bitset<LENGTH> tap;

public:
	int init(int length);
	int setReg(string key);
	int setTap(string t_tap);
	bitset<LENGTH> state();
	int shift(int k);
};

#endif