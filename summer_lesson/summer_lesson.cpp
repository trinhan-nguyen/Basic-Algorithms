#include <iostream>

using namespace std;

#define maxn 10001

int main() {
    int n, m, a[maxn], res[maxn];
    for (int i = 0; i < maxn; ++i) res[i] = 0;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ++res[a[i]];
    }
    for (int i = 0; i < m; ++i) {
        cout << res[i] << " ";
    }
    return 0;
}