#include <iostream>
#include <algorithm>

using namespace std;

int n;
long long fibo[50];

void init(void) {
	fibo[0] = 0;
	fibo[1] = 1;
	for (int i = 2; i < 36; ++i) 
		fibo[i] = fibo[i - 1] + fibo[i - 2];
} 

int main(void) {
	cin >> n;
	init();
	cout << fibo[n];
	return 0;
}