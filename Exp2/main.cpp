#include <bits/stdc++.h>

#define LENGTH 10
#define FORLEN 10

using namespace std;

class LFSR {

private:
	int m;
	bitset<LENGTH> reg;
	bitset<LENGTH> tap;

public:
	int init(int length) {
		m = length;
		reg.reset();
		tap.reset();
	}
	int setReg(string key) {
		if (key.size() != m) {
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
	int setTap(string t_tap) {
		if (t_tap.size() != m) {
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
	bitset<LENGTH> state() {
		return reg;
	}
	int shift(int k) {
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
};

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
	int addPN(vector<int> idx) {
		bitset<LENGTH> newPN;
		newPN.reset();
		for (int i = 0; i < idx.size(); i++) {
			if (idx[i] >= 0 && idx[i] < n) {
				newPN.set(idx[i]);
			} else {
				cout << "Illegal boolean function." << endl;
				return -1;
			}
		}
		pn.push_back(newPN);
	}
	int calc(bitset<LENGTH> state) {
		int res = 0;
		for (int i = 0; i < pn.size(); i++) {
			if ((pn[i] & state) == pn[i]) {
				res ^= 1;
			}
		}
		return res;
	}
	bitset<LENGTH> calc(bitset<LENGTH> state[LENGTH]) {
		// no constant variable in the formula
		bitset<FORLEN> res;
		res.reset();
		for (int i = 0; i < pn.size(); i++) {
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
};

class GaussElim {

private:
	int n;
	vector< bitset<FORLEN> > func;

public:
	GaussElim(int n) : n(n) {}
	void addFunc(bitset<FORLEN> newFunc) {
		func.push_back(newFunc);
	}
	int funcNum() {
		return func.size();
	}
	int solve() {
		int pre = 0;
		bool res = true;
		int m = func.size();
		for (int i = 0; i < n; i++) {
			int j;
			for (j = pre; j < m; j++) {
				if (func[j].test(i)) {
					swap(func[pre], func[j]);
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
				}
			}
			pre++;
			// print();
			// cout << "------------" << endl;
		}
		while (func.size() > pre) {
			func.pop_back();
		}
		return res;
	}
	void print() {
		for (int i = 0; i < func.size(); i++) {
			cout << func[i] << endl;
		}
	}
};

int main() {

	freopen("1.out", "w", stdout);

	int n = LENGTH;
	srand(time(0));

	LFSR lfsr;
	lfsr.init(n);

	string tap = "0000001001";
	lfsr.setTap(tap);

	string key = "";
	for (int i = 0; i < n; i++) {
		key += '0' + (rand() & 1);
	}
	key = "1000000000";
	lfsr.setReg(key);

	string keyStream = "";

	// check whether the period is
	// long enough, use KMP
	vector<int> pre;

	// wait to be defined
	// used to generate key stream
	BoolFunc f(n);
	f.addPN({1, 3, 0});
	f.addPN({1, 3, 2});

	// used to degration f
	BoolFunc g(n);
	g.addPN({1});
	g.addPN({3});

	// wait to be defined
	// changed by lfsr matrix
	bitset<LENGTH> state[n];
	for (int i = 0; i < n; i++) {
		state[i].set(i);
	}

	// Gaussian Elimination
	GaussElim EqGrp(n);

	int tried = 0;
	bool over = false;
	bool period = false;
	while (!over) {

		int keyBit = f.calc(lfsr.state());
		keyStream += '0' + keyBit;

		// cout << "state: " << lfsr.state() << endl;

		// update lfsr
		lfsr.shift(1);

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

		if (keyBit) {
			bitset<FORLEN> newFunc = g.calc(state);
			EqGrp.addFunc(newFunc);
			if (EqGrp.funcNum() > n + 10) {
				if (EqGrp.solve()) {
					cout << "hahaha" << endl;
					break;
				}
			}
		}

		// cout << "---------" << endl;
		// for (int i = 0; i < n; i++) {
		// 	cout << state[i] << endl;
		// }
		// cout << "---------" << endl;

		if (tried++ > 2000000) {
			break;
		}
	}
	EqGrp.solve();
	EqGrp.print();
	cout << "------------" << endl;
	cout << EqGrp.funcNum() << endl;

	return 0;
}