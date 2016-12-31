#include <bits/stdc++.h>

#define MINI	2
#define STR		1

using namespace std;

class BigInteger {
private:
	int ty;
	int length;
	string strNum;

public:
	BigInteger() {
		ty = STR;
		length = 1;
		strNum = "0";
	}
	BigInteger(string s) {
		ty = STR;
		strNum = s;
		length = strNum.size();
	}
	int getLength() {
		return length;
	}
	BigInteger sub(int l, int r) {
		if (l >= length) {
			return BigInteger("0");
		}
		return BigInteger(strNum.substr(l, min(r, length) - l));
	}
	BigInteger shiftL(int k) {
		string res(k, '0');
		strNum = res + strNum;
		length = strNum.size();
		return *this;
	}

	int operator [] (const int& k) const {
		if (k < (int)strNum.size()) {
			return strNum[k] - '0';
		} else {
			return 0;
		}
	}
	BigInteger operator + (const BigInteger& addend) const {
		string res = "";
		int len = max(length, addend.getLength());
		int y = 0;
		for (int i = 0; i < len; i++) {
			int x = (strNum[i] & 1) + (addend[i] & 1) + y;
			y = x >> 1;
			res += '0' + (x & 1);
		}
		if (y) {
			res += '1';
		}
		return BigInteger(res);
	}
	BigInteger operator - (const BigInteger& subtrahend) const {
		string res = "";
		int y = 0;
		int len = subtrahend.getLength();
		for (int i = 0; i < len; i++) {
			int x = (strNum[i] & 1) + (subtrahend[i] & 1) + y;
			if ((x && !(strNum[i] & 1)) || (y || (subtrahend[i] & 1)))
		}
	}
};

void toBit(string& strNum) {
	BigInteger res;
	int length = strNum.size();
	reverse(strNum.begin(), strNum.end());
	while (length > 1 || strNum[0] != '0') {
		res += '0' + (strNum[0] & 1);
		int y = 0;
		for (int i = length - 1; i >= 0; i--) {
			int x = strNum[i] - '0' + y;
			strNum[i] = x / 2;
			y = (x & 1) ? 10 : 0;
		}
		if (strNum.back() == '0') {
			strNum.pop_back();
			length--;
		}
	}
	strNum = res;
	length = strNum.size();
}

BigInteger mul(BigInteger a, BigInteger b) {
	if (a.length < MINI && b.length < MINI) {
		return a * b;
	}
	int l = max(a.length, b.length);
	int ll = l / 2;
	BigInteger a0 = a.sub(0, ll), b0 = b.sub(0, ll);
	BigInteger a1 = a.sub(ll, l), b1 = b.sub(ll, l);
	BigInteger z0 = mul(a0, b0);
	BigInteger z1 = mul(a0 + a1, b0 + b1);
	BigInteger z2 = mul(a1, b1);
	return z0 + (z1 - z0 - z2).shiftL(ll) + z2.shiftL(l);
}

int main() {
	string s1, s2;
	cout << "Please input two integer:" << endl;
	cin >> s1 >> s2;
	for (int i = 0; i < s1.size(); i++) {
		if (!isdigit(s1[i])) {
			cout << "Non-digit bit found in the first number." << endl;
			return -1;
		}
	}
	for (int i = 0; i < s2.size(); i++) {
		if (!isdigit(s2[i])) {
			cout << "Non-digit bit found in the second number." << endl;
			return -1;
		}
	}
	toBit(s1);
	toBit(s2);
	BigInteger a(s1), b(s2);
	cout << "The result is: " << mul(a, b) << endl;
	return 0;
}