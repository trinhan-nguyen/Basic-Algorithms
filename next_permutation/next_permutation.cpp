#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define maxn 1000001

void swap(char *a, char *b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void solve(string str) {
	int len = str.length();
	int pos = len - 1;
	// find the first element that is not in the last decreasing sequence
	while (str[pos] <= str[pos - 1] && pos > 0) --pos;
	if (pos == 0) {
		cout << "no answer\n";
		return; 
	}
	// find the smallest element that is greater than str[pos - 1] in the
	//   last decreasing sequence
	int i = len - 1;
	while (str[i] <= str[pos - 1]) {
		--i;
	}
	// swap 
	swap(&str[pos - 1], &str[i]);

	//  flip from pos to the end
	for (int i = pos; i < (len + pos) / 2; ++i) {
		swap(&str[i], &str[len + pos - i - 1]);
	}
	cout << str << "\n";
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		string str;
		cin >> str;
		solve(str);
	}
}