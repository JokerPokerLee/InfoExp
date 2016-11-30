#include <bits/stdc++.h>
#include "source.h"
#include "lfsr.h"
#include "bool_func.h"
#include "gauss_elim.h"

using namespace std;

int main() {

	srand(time(0));

	freopen("../input/in", "r", stdin);
	int n, num;
	cin >> n >> num;

	LFSR lfsr;
	lfsr.init(n);

	vector<int> coef;
	for (int i = 0; i < num; i++) {
		int x;
		cin >> x;
		if (x <= n && x > 0) {
			coef.push_back(x - 1);
		} else {
			cout << "Illegal coefficient: " << x << endl;
			return 0;
		}
	}
	sort(coef.begin(), coef.end());
	reverse(coef.begin(), coef.end());

	string tap = "";
	for (int i = 0; i < n; i++) {
		if (coef.size() && i == coef.back()) {
			coef.pop_back();
			tap += '1';
		} else {
			tap += '0';
		}
	}
	lfsr.setTap(tap);

	string key = "";
	for (int i = 0; i < n; i++) {
		key += '0' + (rand() & 1);
	}
	lfsr.setReg(key);

	cout << "The generated key is:\t\t" << key << endl;

	string keyStream = "";

	bool tw = false;

	// wait to be defined
	// used to generate key stream
	BoolFunc f(n);
	cin >> num;
	while (num--) {
		int k;
		cin >> k;
		vector<int> idx;
		while (k--) {
			int x;
			cin >> x;
			idx.push_back(x);
		}
		f.addPN(idx);
	}

	// used to degration f
	BoolFunc g(n);
	cin >> num;
	while (num--) {
		int k;
		cin >> k;
		vector<int> idx;
		while (k--) {
			int x;
			cin >> x;
			idx.push_back(x);
		}
		g.addPN(idx);
		if (idx.size() > 1) {
			tw = true;
		}
	}

	// wait to be defined
	// changed by lfsr matrix
	bitset<LENGTH> state[LENGTH];
	for (int i = 0; i < n; i++) {
		state[i].set(i);
	}

	// Gaussian Elimination
	GaussElim EqGrp(n);

	if (tw) {
		EqGrp.setTw();
	}

	int sta = clock();

	// freopen("1.out", "w", stdout);

	// int tried = 0;
	bool over = false;
	int funcNum = tw ? (n * (n + 1) / 2) : n;
	while (!over) {

		int keyBit = f.calc(lfsr.state());
		keyStream += '0' + keyBit;

		// if (keyBit) {
		// 	cout << "state: " << lfsr.state() << endl;
		// }

		// update lfsr
		lfsr.shift(1);

		if (keyBit) {
			bitset<FORLEN> newFunc = g.calc(state);
			// cout << newFunc << endl;
			EqGrp.addFunc(newFunc);
			if (EqGrp.funcNum() >= funcNum) {
				if (EqGrp.solve()) {
					break;
				}
			}
		}

		// update state matrix
		bitset<LENGTH> newBit;
		newBit.reset();
		for (int i = n - 1; i >= 0; i--) {
			if (tap[i] == '1') {
				newBit ^= state[i];
			}
			if (i) {
				state[i] = state[i - 1];
			}
		}
		state[0] = newBit;

		// if (keyBit) {
		// 	cout << "---------" << endl;
		// 	for (int i = 0; i < n; i++) {
		// 		cout << state[i] << endl;
		// 	}
		// 	cout << "---------" << endl;
		// }

		// if (tried++ > 2) {
		// 	break;
		// }
	}
	EqGrp.printKey();

	cout << "The length of cipher stream: " << keyStream.size() << endl;

	cout << "Time consumed: " << setprecision(3) << 1.0 * (clock() - sta) / CLOCKS_PER_SEC << "s" << endl;

	return 0;
}