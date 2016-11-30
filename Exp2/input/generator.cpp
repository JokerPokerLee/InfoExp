#include <bits/stdc++.h>

using namespace std;

vector<int> a, b, c;

int main() {

	srand(time(0));

	freopen("../input/in", "w", stdout);

	int n = 100, m =2;

	cout << n << " " << m << endl;
	cout << "100 63" << endl;

	cout << endl;

	int cnt = 0;
	for (int i = 40; i < 70; i++) {
		for (int j = 70; j < 100; j++) {
			if (rand() % 500 < 498) {
				continue;
			}
			a.push_back(i);
			b.push_back(j);
			cnt++;
		}
	}
	for (int i = 10; i < 20; i++) {
		for (int j = 20; j < 30; j++) {
			for (int k = 30; k < 40; k++) {
				if (rand() % 500 < 498) {
					continue;
				}
				a.push_back(i);
				b.push_back(j);
				c.push_back(k);
				cnt++;
			}
		}
	}
	cnt++;
	cout << cnt << endl;
	cout << 10;
	for (int i = 0; i < 10; i++) {
		cout << " " << i;
	}
	cout << endl;
	while (c.size()) {
		cout << 4 << " " << 0 << " " << a.back() << " " << b.back() << " " << c.back() << endl;
		a.pop_back();
		b.pop_back();
		c.pop_back();
	}
	while (b.size()) {
		cout << 3 << " " << 4 << " " << a.back() << " " << b.back() << endl;
		a.pop_back();
		b.pop_back();
	}

	cout << endl;

	cout << "3" << endl;
	cout << "1 0" << endl;
	cout << "1 4" << endl;
	cout << "2 0 4" << endl;
	return 0;
}