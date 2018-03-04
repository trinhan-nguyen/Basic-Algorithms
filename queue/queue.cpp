#include <iostream>
#include <queue>

using namespace std;

int main() {
	int q = 0;
	cin >> q;
	queue<int> my_queue;
	for (int i = 0; i < q; ++i) {
		int type = 0;
		cin >> type;
		if (type == 1) {
			int x = 0;
			cin >> x;
			my_queue.push(x);
		} else if (type == 2) {
			if (!my_queue.empty()) my_queue.pop();
		} else if (type == 3) {
			if (!my_queue.empty()) cout << my_queue.front() << "\n";
			else cout << "Empty\n";
		} else {
			cout << "I/O Error!";
			return 0;
		}
	}
	return 0;
}