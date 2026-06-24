#include "RPN.hpp"

#include <cctype>
#include <cstdlib>
#include <sstream>

RPN::RPN() {
}

RPN::RPN(const RPN &other) : _values(other._values) {
}

RPN::~RPN() {
}

RPN &RPN::operator=(const RPN &other) {
	if (this != &other)
		_values = other._values;
	return *this;
}

int RPN::calculate(const std::string &expr) {
	RPN rpn;
	return rpn.eval(expr);
}

int RPN::eval(const std::string &expr) {
	std::istringstream input(expr);
	std::string token;
	while (input >> token) {
		if (token.size() != 1)
			throw std::runtime_error("Error");
		if (std::isdigit(token[0]))
			_values.push(token[0] - '0');
		else if (isOperator(token[0]))
			apply(token[0]);
		else
			throw std::runtime_error("Error");
	}
	if (_values.size() != 1)
		throw std::runtime_error("Error");
	return _values.top();
}

bool RPN::isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::apply(char op) {
	if (_values.size() < 2)
		throw std::runtime_error("Error");
	int right = _values.top();
	_values.pop();
	int left = _values.top();
	_values.pop();
	if (op == '+')
		_values.push(left + right);
	else if (op == '-')
		_values.push(left - right);
	else if (op == '*')
		_values.push(left * right);
	else {
		if (right == 0)
			throw std::runtime_error("Error");
		_values.push(left / right);
	}
}
