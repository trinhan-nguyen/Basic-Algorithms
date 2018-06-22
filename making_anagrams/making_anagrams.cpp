#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int lenS, lenT, cntS[26], cntT[26];
string s, t;

void result(void) {
	int ans = 0;
	for (int i = 0; i < 26; ++i) {
		ans += abs(cntS[i] - cntT[i]);
	}
	cout << ans;
}

void init(void) {
	lenS = s.length();
	lenT = t.length();
	for (int i = 0; i < lenS; ++i) {
		int curChar = s[i];
		cntS[curChar - 97]++;
	}
	for (int i = 0; i < lenT; ++i) {
		int curChar = t[i];
		cntT[curChar - 97]++;
	}
}

int main(void) {

	cin >> s >> t;
	init();
	result();
	return 0;
}