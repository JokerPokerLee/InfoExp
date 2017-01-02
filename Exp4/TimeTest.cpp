#include <bits/stdc++.h>

#define MINI	2
#define STR		1

using namespace std;

struct BigInteger {
	int ty;
	int length;
	string strNum;

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
	BigInteger sub(int l, int r) {
		if (l >= length) {
			return BigInteger("0");
		}
		string res = strNum.substr(l, min(r, length) - l);
		while (res.back() == '0' && res.length() > 1) {
            res.pop_back();
		}
		return BigInteger(res);
	}
	BigInteger shiftL(int k) {
        if (strNum == "0") {
            return BigInteger("0");
        }
		string res(k, '0');
		res = res + strNum;
		return res;
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
		int len = min(length, addend.length);
		int y = 0;
		for (int i = 0; i < len; i++) {
			int x = (strNum[i] & 1) + (addend[i] & 1) + y;
			y = x >> 1;
			res += '0' + (x & 1);
		}
		if (len < length) {
			res += strNum.substr(len, length);
		} else {
			res += addend.strNum.substr(len, addend.length);
		}
		while (len < res.length() && y) {
			y = res[len] & 1;
			res[len++] ^= 1;
		}
		if (y) {
			res += '1';
		}
		return BigInteger(res);
	}
	BigInteger operator - (const BigInteger& subtrahend) const {
		string res = "";
		int y = 0;
		int len = subtrahend.length;
		for (int i = 0; i < len; i++) {
            int x = y + (subtrahend[i] & 1);
            if (strNum[i] - '0' < x) {
                res += strNum[i] + 2 - x;
                y = 1;
            } else {
                res += strNum[i] - x;
                y = 0;
            }
		}
		res += strNum.substr(len, strNum.length() - len);
		while (y) {
			y = (res[len] & 1) ^ 1;
			res[len++] ^= 1;
		}
		while (res.back() == '0' && res.length() > 1) {
			res.pop_back();
		}
		return BigInteger(res);
	}
	BigInteger operator * (BigInteger& multiplier) {
		BigInteger res("0");
		if (strNum == "0" || multiplier.strNum == "0") {
            return res;
		}
		int len = multiplier.length;
		string mul = multiplier.strNum;
		for (int i = 0; i < len; i++) {
			if (mul[i] & 1) {
				string tmp = string(i, '0') + strNum;
				res = res + BigInteger(tmp);
			}
		}
		return res;
	}
	void print() {
		string res = strNum;
		reverse(res.begin(), res.end());
		cout << res << endl;
	}
};

void toBit(string& strNum){
	string res = "";
	int length = strNum.size();
	reverse(strNum.begin(), strNum.end());
	while (length > 1 || strNum[0] != '0') {
		int y = 0;
		for (int i = length - 1; i >= 0; i--) {
			int x = strNum[i] - '0' + y * 10;
			strNum[i] = '0' + x / 2;
			y = x & 1;
		}
		res += '0' + y;
		if (strNum.back() == '0' && strNum.length() > 1) {
			strNum.pop_back();
			length--;
		}
	}
	strNum = res;
}

string toDec(string strNum) {
	string res = "0";
	string t = "1";
	int len = strNum.length();
	for (int i = 0; i < len; i++) {
		if (strNum[i] & 1) {
			int l = t.length();
			if (res.length() < l) {
                res += string(l - res.length(), '0');
			}
			int y = 0;
			for (int j = 0; j < l; j++) {
				int x = (res[j] - '0') + (t[j] - '0') + y;
				y = x / 10;
				res[j] = '0' + x % 10;
			}
			while (y) {
				if (len < res.length()) {
					y = (res[len] - '0') + y;
					res[len] = '0' + y % 10;
					y /= 10;
				} else {
					res += '0' + y;
					y = 0;
				}
				len++;
			}
		}
		int y = 0;
		for (int j = 0; j < t.length(); j++) {
            int x = (t[j] - '0') * 2 + y;
            t[j] = '0' + x % 10;
            y = x / 10;
		}
		if (y) {
            t.push_back('1');
		}
	}
	reverse(res.begin(), res.end());
	return res;
}

BigInteger mul(BigInteger a, BigInteger b) {
	if (a.length <= MINI && b.length <= MINI) {
		return a * b;
	}
	int l = max(a.length, b.length);
	l += (l & 1);
	int ll = l / 2;
	BigInteger a0 = a.sub(0, ll), b0 = b.sub(0, ll);
	BigInteger a1 = a.sub(ll, l), b1 = b.sub(ll, l);
	BigInteger z0 = mul(a0, b0);
	BigInteger z1 = mul(a0 + a1, b0 + b1);
	BigInteger z2 = mul(a1, b1);
	return z0 + (z1 - z0 - z2).shiftL(ll) + z2.shiftL(l);
}

int main() {
	srand(time(0));
	int len = 1;
	for (int i = 0; i < 7; i++) {
		string a, b;
		a += '1' + rand() % 9;
		b += '1' + rand() % 9;
		len *= 10;
		for (int j = 1; j < len; j++) {
			a += '0' + rand() % 10;
			b += '0' + rand() % 10;
		}
		toBit(a);
		toBit(b);
		BigInteger s(a), t(b);
		int sta = clock();
		mul(s, t);
		std::cout << std::setprecision(3) << 1.0 * (clock() - sta) / CLOCKS_PER_SEC << std::endl;
	}
	return 0;
}
