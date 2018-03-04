#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool is_closing(char bracket) {
	return bracket == '}' || bracket == ']' || bracket == ')';
}

bool is_matching(char open, char close) {
	return (open == '(' && close == ')') 
		|| (open == '[' && close == ']') 
		|| (open == '{' && close == '}'); 
}

bool is_balanced(string expression) {
	stack<char> my_stack;
	for (int i = 0; i < expression.length(); ++i) {
		if (my_stack.empty() && is_closing(expression[i])) return false;
		else if (is_closing(expression[i])) {
			char top = my_stack.top();
			my_stack.pop();
			if (!is_matching(top, expression[i])) return false;
		} else {
			my_stack.push(expression[i]);
		}
	}
	return my_stack.empty();
}

int main() {
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string expression = "";
		cin >> expression;
		bool answer = is_balanced(expression);
		if (answer) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}