#include <iostream>
#include <algorithm>

using namespace std;

#define maxn 50

void print_string(int len, bool *a) {
	for (int i = 0; i < len; ++i) {
		if (a[i]) cout << 1;
		else cout << 0;
	}
	cout << "\n";
}

void generate(int cur, int len, bool *a) {
	if (cur == len) {
		print_string(len, a);		
		return;
	}
	a[cur] = false;
	generate(cur + 1, len, a);
	a[cur] = true;
	generate(cur + 1, len, a);
}

//	Generate all binary strings with length n
int main() {
	int n = 0;
	bool a[maxn] = {0};
	cout << "This program will generate all binary strings with length n.\n";
	cout << "Please enter the length:\n";
	cout << "n = ";
	cin >> n;
	if (n <= 0) {
		cout << "Length should be greater than zero\n";
		return 0;
	}
	generate(0, n, a);
}