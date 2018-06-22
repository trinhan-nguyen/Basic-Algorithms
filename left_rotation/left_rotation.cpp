#include <iostream>
#include <algorithm>

using namespace std;

#define maxn 1000001
int n, d, a[maxn];

int main() {
	cin >> n >> d;
	for (int i = 0; i < n; ++ i) cin >> a[i];
	for (int i = d; i < n; ++ i)
		cout << a[i] << " ";
	for (int i = 0; i < d; ++ i) 
		cout << a[i] << " ";
	return 0;
}