#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

void quicksort(vector<int> &a, int l, int r) {
	if (l >= r) return;
	int pivot  = a[rand() % (r - l + 1) + l];
	int i = l, j = r;
	while (i <= j) {
		while (a[i] < pivot) ++i;
		while (a[j] > pivot) --j;
		if (i <= j) {
			if (i < j) swap(a[i], a[j]);
			++i; --j;
		}
	}
	quicksort(a, l, j);
	quicksort(a, i, r);
}

void printToFile(const vector<int> &a) {
    ofstream out("sampleOutput.txt");
	for (int i = 0; i < a.size(); ++i) {
		out << a[i] << " ";
    }
}

int main() {
    ifstream inp("sampleInput.txt");
    int size;
    inp >> size;
	vector<int> a;
	for (int i = 0; i < size; ++i) {
		int elem = 0;
		inp >> elem;
		a.push_back(elem);
	}

	quicksort(a, 0, a.size() - 1);

    printToFile(a);
}
