#include <iostream>

using namespace std;

long long a, b, x, y, z;

long long solve(void) {
	long long ans = 0;
	a = a - 2 * x - y;
	b = b - 3 * z - y;
	if (a < 0) ans -= a;
	if (b < 0) ans -= b;
	return ans;
}

int main(void) {
	cin >> a >> b;
	cin >> x >> y >> z;
	cout << solve();
	return 0;
}