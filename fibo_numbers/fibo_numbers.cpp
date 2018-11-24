#include <iostream>

int calculate(int n) {
	int first = 0;
	int second = 1;
    int fiboNumber = 1;
	for (int i = 1; i < n; ++i) {
		fiboNumber = first + second;
        first = second;
        second = fiboNumber;
    }
    return fiboNumber;
} 

int main(void) {
    int n = 20;
    std::cout << calculate(n) << std::endl;
	return 0;
}
