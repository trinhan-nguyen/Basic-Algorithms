#include <iostream>
 
using namespace std;
 
int play(int n) {
    if (n == 2) return 2;
    return 1;
}
 
int main() {
    int n;
    cin >> n;
    cout << play(n) << endl;
}
