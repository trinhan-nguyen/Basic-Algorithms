#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b= tmp;
}

void quicksort(vector<int> &a, int l, int r) {
	if (l >= r) return;
	int pivot  = a[rand() % (r - l + 1) + l];
	int i = l, j = r;
	while (i <= j) {
		while (a[i] < pivot) ++i;
		while (a[j] > pivot) --j;
		if (i <= j) {
			if (i < j) swap(a[i], a[j]);
			++i; --j;
		}
	}
	quicksort(a, l, j);
	quicksort(a, i, r);
}

int main() {
	int n = 0;
	vector<int> a;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int tmp = 0;
		cin >> tmp;
		a.push_back(tmp);
	}
	quicksort(a, 0, n - 1);
	for (int i = 0; i < n; ++i) 
		cout << a[i] << " ";
	return 0;
}