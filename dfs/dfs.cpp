#include <iostream>
#include <math.h>

using namespace std;

#define maxn 1001

const int a[8][2] = {
	{1, 0},
	{0, 1},
	{1, 1},
	{-1, 1},
	{1, -1},
	{0, -1},
	{-1, 0},
	{-1, -1},
};

bool out_of_bound(int i, int j, int n, int m) {
	return i < 0 || j < 0 || i > n || j > m;
}

void dfs(int (*grid)[maxn][maxn], int *max_so_far, int i, int j, int n, int m) {
	if ((*grid)[i][j] == 0) return;
	(*grid)[i][j] = 0;
	++(*max_so_far);	
	for (int t = 0; t < 8; ++ t) {
		int new_i = i + a[t][0];
		int new_j = j + a[t][1];
		if (out_of_bound(new_i, new_j, n, m)) continue;
		dfs(grid, max_so_far, i + a[t][0], j + a[t][1], n ,m);
	}
}

int main() {
	int grid[maxn][maxn] = {0};
	int n = 0, m = 0, max_so_far = 0, result = 0;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < m; ++j) 
			cin >> grid[i][j];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			if (grid[i][j]) {
				dfs(&grid, &max_so_far, i, j, n, m);
				result = max(result, max_so_far);
				max_so_far = 0;
			}
		}
	cout << result;
	return 0;
}