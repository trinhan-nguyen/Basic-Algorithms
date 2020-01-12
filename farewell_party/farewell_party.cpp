#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
 
using namespace std;
 
vector<int> ans;
vector<pair<int, int>> a;
 
bool cmp(pair<int, int> i, pair<int, int> j) {
    if (i.first == j.first) return i.second < j.second;
    return i.first < j.first;
}
 
void init() {
    sort(a.begin(), a.end(), cmp);
    for (int i = 0; i < a.size(); ++i) {
        ans.emplace_back(0);
    }
}
 
void solve() {
    init();
    int count = 1;
    for (int i = 0; i < a.size(); ++count) {
        int numDiff = a[i].first - i;
        int j = i;
        while (j < a.size() - numDiff) {
            if (a[j].first != a[i].first) {
                ans.clear();
                return;
            }
            ans[a[j].second] = count;
            ++j;
        }
        i = j;
    }
}
 
int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int inp;
        cin >> inp;
        a.emplace_back(make_pair(inp, i));
    }

    solve();
 
    if (ans.empty()) {
        cout << "Impossible" << endl;
    } else {
        cout << "Possible" << endl;
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}
