
class LFSR {
	int m;
	bitset<100> reg;
	bitset<100> tap;

	int init(int length) {
		m = length;
		reg.reset();
		tab.reset();
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
	int setTap(string tap) {
		if (tap.size() != m) {
			cout << "Unmatched key length." << endl;
			return -1;
		}
		if (tap[0] == '0' || tap[tap.size() - 1] == '0') {
			cout << "Degenerated tabs." << endl;
			return -2;
		}
		for (int i = 0; i < m; i++) {
			if (tap[i] == '0') {
				reg.reset(i);
			} else
			if (tap[i] == '1') {
				reg.set(i);
			} else {
				cout << "Wrong key value." << endl;
				return -3;
			}
		}
		return 0;
	}
	bitset<100> currentState() {
		return reg;
	}
	int shift(int k) {
		while (k--) {
			bitset<100> tmp = reg & tap;
			reg <<= 1;
			if (tmp.count & 1) {
				reg.set(0);
			} else {
				reg.reset(0);
			}
		}
		return 0;
	}
};