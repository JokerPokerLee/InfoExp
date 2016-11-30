#include <bits/stdc++.h>
#include "source.h"
#include "gauss_elim.h"

using namespace std;

void GaussElim::addFunc(bitset<FORLEN> newFunc) {
	func.push_back(newFunc);
	v.push_back(1);
}
int GaussElim::funcNum() {
	return func.size();
}
int GaussElim::solve() {
	int pre = 0;
	bool res = true;
	int m = func.size();
	for (int i = 0; i < n; i++) {
		int j;
		for (j = pre; j < m; j++) {
			if (func[j].test(i)) {
				swap(func[pre], func[j]);
				swap(v[pre], v[j]);
				break;
			}
		}
		if (j == m) {
			res = false;
			continue;
		}
		for (int j = 0; j < m; j++) {
			if (j != pre && func[j].test(i)) {
				func[j] ^= func[pre];
				v[j] ^= v[pre];
			}
		}
		pre++;
	}
	while ((int)func.size() > pre) {
		func.pop_back();
		v.pop_back();
	}
	return res;
}
void GaussElim::print() {
	for (int i = 0; i < (int)func.size(); i++) {
		cout << func[i] << "---" << v[i] << endl;
	}
}
void GaussElim::printKey() {
	cout << "The result of elimination:\t";
	if (tw) {
		swap(ori, n);
	}
	for (int i = 0; i < n; i++) {
		cout << v[i];
	}
	cout << endl;
	if (tw) {
		swap(ori, n);
	}
}