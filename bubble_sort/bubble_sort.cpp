#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int n, cnt, a[800];

void swap(int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void read(void) {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
}

void write(void) {
	cout << "Array is sorted in " << cnt;
	if (cnt == 1) cout << "swap." << "\n";
	else cout << " swaps." << "\n";
	cout << "First Element: " << a[0] << "\n";
	cout << "Last Element: " << a[n - 1] << "\n"; 
}

void bubbleSort(void) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; ++j) {
			if (a[j] > a[i]) {
				swap(i, j);
				++cnt;
			}
		}
	}
}

int main(void) {
	cnt = 0;
	read();
	bubbleSort();
	write();
	return 0;
}