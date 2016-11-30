#include <bits/stdc++.h>
#include "LFSR.h"

using namespace std;

int LFSR::init(int length) {
	m = length;
	reg.reset();	
	tap.reset();
	return 0;
}

int LFSR::setReg(string key) {
	if ((int)key.size() != m) {
		cout << "Unmatched key length." << endl;
		return -1;
	}
	for (int i = 0; i < m; i++) {
		if (key[i] == '0') {
			reg.reset(i);
		} else
		if (key[i] == '1') {
			reg.set(i);
		} else {
			cout << "Wrong key value." << endl;
			return -2;
		}
	}
	return 0;
}

int LFSR::setTap(string t_tap) {
	if ((int)t_tap.size() != m) {
		cout << "Unmatched key length." << endl;
		return -1;
	}
	if (t_tap[m - 1] == '0') {
		cout << "Degenerated tabs." << endl;
		return -2;
	}
	for (int i = 0; i < m; i++) {
		if (t_tap[i] == '0') {
			tap.reset(i);
		} else
		if (t_tap[i] == '1') {
			tap.set(i);
		} else {
			cout << "Wrong key value." << endl;
			return -3;
		}
	}
	return 0;
}

bitset<LENGTH> LFSR::state() {
	return reg;
}

int LFSR::shift(int k) {
	while (k--) {
		bitset<LENGTH> tmp = reg & tap;
		reg <<= 1;
		if (tmp.count() & 1) {
			reg.set(0);
		} else {
			reg.reset(0);
		}
	}
	return 0;
}