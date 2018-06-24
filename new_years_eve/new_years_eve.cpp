#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

long long a[20], n, k;

long long numberOfBits(void) {
	int cnt = 0;
	while(n > 0) {
		++cnt;
		n = n / 2;
	}
	return cnt;
}

long long solve(void) {
	if (k == 1) return n;
	return (double)pow(2, numberOfBits()) - 1;
}

int main(void) {
	cin >> n >> k;
	cout << solve();
	return 0;
}