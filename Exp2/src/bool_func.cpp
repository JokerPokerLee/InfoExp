#include <bits/stdc++.h>
#include "source.h"
#include "bool_func.h"

using namespace std;

int BoolFunc::addPN(vector<int> idx) {
	bitset<LENGTH> newPN;
	newPN.reset();
	for (int i = 0; i < (int)idx.size(); i++) {
		if (idx[i] >= 0 && idx[i] < n) {
			newPN.set(idx[i]);
		} else {
			cout << "Illegal boolean function." << endl;
			return -1;
		}
	}
	pn.push_back(newPN);
	return 0;
}

int BoolFunc::calc(bitset<LENGTH> state) {
	int res = 0;
	for (int i = 0; i < (int)pn.size(); i++) {
		if ((pn[i] & state) == pn[i]) {
			res ^= 1;
		}
	}
	return res;
}

bitset<FORLEN> BoolFunc::calc(bitset<LENGTH> state[LENGTH]) {
	bitset<FORLEN> res;
	res.reset();
	for (int i = 0; i < (int)pn.size(); i++) {
		bitset<FORLEN> tmp[2];
		int now = 0, pre = 1;
		tmp[now].reset();
		int j = 0;
		while (j < n) {
			if (pn[i].test(j)) {
				for (int k = 0; k < n; k++) {
					if (state[j].test(k)) {
						tmp[now].set(k);
					}
				}
				j++;
				break;
			}
			j++;
		}
		// cout << j << endl;
		// cout << tmp[now] << endl;
		while (j < n) {
			if (pn[i].test(j)) {
				now ^= 1, pre ^= 1;
				tmp[now].reset();
				for (int k = 0; k < n; k++) {
					if (state[j].test(k)) {
						for (int t = 0; t < n; t++) {
							if (tmp[pre].test(t)) {
								tmp[now].flip(getIdx(k, t));
							}
						}
					}
				}
			}
			j++;
		}
		res ^= tmp[now];
	}
	return res;
}

void BoolFunc::print() {
	for (int i = 0; i < (int)pn.size(); i++) {
		cout << pn[i] << endl;
	}
}