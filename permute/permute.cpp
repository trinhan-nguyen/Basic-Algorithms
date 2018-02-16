#include <iostream>

using namespace std;

#define maxn 18

void set_up(int len, int *a) {
	for (int i = 0; i < len; ++i) a[i] = i + 1;
}

void print_permute(int len, int *a) {
	for (int i = 0; i < len; ++i) cout << a[i] << " ";
	cout << "\n";
}

void swap(int *a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void flip(int *a, int i, int j) {
	while (i < j) {
		swap(a, i, j);
		++i;
		--j;
	}
}

void permute(int len, int *a) {
	print_permute(len, a);
	//  i is the index for the elem that stands before the last
	//	  decreasing sequence.
	int i = len - 2, k = len - 1;
	while (i >= 0 && a[i] > a[i + 1]) --i;
	if (i == -1)  return;
	while (a[k] < a[i]) --k;
	swap(a, i, k);
	flip(a, i + 1, len - 1);
	permute(len, a);
}

// 	Generate every permutations
int main() {
	int n = 0;
	int a[maxn] = {0};
	cout << "This program generates all permutaions from 1 to n.\n";
	cout << "Please enter the value:\n";
	cout << "n = ";
	cin >> n;
	if (n <= 0) {
		cout << "The value should be greater than zero.\n";
		return 0;
	}
	set_up(n, a);
	permute(n, a);
	return 0;
}