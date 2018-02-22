#include <iostream>
#include <vector>

using namespace std;

#define maxn 10001
#define maxv 1000000001
#define max_reduce 5

int count_step(int diff) {
	int steps = 0;
	int step5 = diff / 5;
	if (step5 > 0) {
		steps += step5;
		diff %= 5;
	} 
	int step2 = diff / 2;
	if (step2 > 0) {
		steps += step2;
		diff %= 2;
	}
	return steps + diff;
}

int sum_step(vector<int> arr, int target) {
	int steps = 0;
	for (int i = 0; i < arr.size(); ++i) {
		steps += count_step(arr[i] - target);
	}
	return steps;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int n, min = maxv, res = maxv, ans[max_reduce];
		cin >> n;
		vector<int> arr(n);
		for (int j = 0; j < n; ++j) {
			cin >> arr[j];
			if (arr[j] < min) min = arr[j];
		}
		for (int j = 0; j < max_reduce; ++j) {
			int tmp = sum_step(arr, min - j);
			if (tmp < res) res = tmp;
		}
		cout << res << "\n";
	}
	return 0;
}