#include <iostream>

using namespace std;

#define maxn 50

int find_last(int len, bool *a) {
	for (int i = len; i > 0; --i) {
		if (a[i - 1]) return i - 1;
	}
	return -1;
}

void print_string(int len, bool *a, const int *elem) {
	cout << "{ ";
	int last_elem = find_last(len, a);
	for (int i = 0; i < len; ++i) {
		if (a[i]) {
			cout << elem[i];
			if (i != last_elem) cout << ", ";
		}	
	}
	cout << " }\n";
}

void generate(int cur, int len, bool *a, const int *elem) {
	if (cur == len) {
		print_string(len, a, elem);		
		return;
	}
	a[cur] = false;
	generate(cur + 1, len, a, elem);
	a[cur] = true;
	generate(cur + 1, len, a, elem);
}

//	Generate all subsets
int main() {
	int n = 0;
	int elem[maxn] = {0};
	bool a[maxn] = {0};
	cout << "This program will generate all subsets\n";
	cout << "Please enter the number of elements:\n";
	cout << "n = ";
	cin >> n;
	if (n <= 0) {
		cout << "The number of elements should be greater than zero\n";
	} else if (n == 1) {
		cout << "Now enter the element: ";
		cin >> elem[0];
		cout << "{ }\n{ " << elem[0] << " }\n";
	} else {
		cout << "Now enter your elements: ";
		for (int i = 0; i < n; ++i) cin >> elem[i];
		generate(0, n, a, elem);
	}
	return 0;
}