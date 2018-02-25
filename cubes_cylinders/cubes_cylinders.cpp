#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define maxn 3001

struct obj {
	int len;
	int num;
};

bool inc_cmp(struct obj i, struct obj j) {
	return i.len < j.len;
}

void print_res(int n, int m, int *s, int *k, int *r, int *c) {
	int count = 0;
	// sort in increasing order
	vector<obj> cubes; 
	vector<obj> cylinders; 
	for (int i = 0; i < n; ++i) {
		struct obj tmp = {s[i], k[i]};
		cubes.push_back(tmp);
	}
	for (int i = 0; i < m; ++i) {
		struct obj tmp = {r[i], c[i]};
		cylinders.push_back(tmp);
	}

	sort(cubes.begin(), cubes.end(), inc_cmp);
	sort(cylinders.begin(), cylinders.end(), inc_cmp);

	// solve after sort
	for (int i = 0; i < m; ++i) {
		for (int j = n - 1; j >= 0; --j) {
			if (cubes[j].len < cylinders[i].len) {
				while (cylinders[i].num > 0 && cubes[j].num > 0) {
					++count; 
					--(cylinders[i].num);
					--(cubes[j].num);
				}
			}
		}
	}	
	cout << count;
}

int main() {
	int n, m, s[maxn], k[maxn], r[maxn], c[maxn];
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> s[i];
		s[i] = s[i] * s[i] * 2;
	}
	for (int i = 0; i < n; ++i) cin >> k[i];
	for (int i = 0; i < m; ++i) {
		cin >> r[i];
		r[i] = r[i] * r[i] * 4;
	}
	for (int i = 0; i < m; ++i) cin >> c[i];
	print_res(n, m, s, k, r, c);
	return 0;
}