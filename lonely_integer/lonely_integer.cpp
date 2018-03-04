#include <iostream>

using namespace std;

int main() {
	int n = 0, result = 0; 
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int tmp = 0;
		cin >> tmp;
		result = result ^ tmp;
	}
	cout << result;
	return 0;
}