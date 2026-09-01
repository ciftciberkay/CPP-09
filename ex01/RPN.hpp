#ifndef RPN_HPP
# define RPN_HPP
# include <stack>
# include <stdexcept>
# include <string>

class RPN
{
public:
	RPN();
	RPN(const RPN &other);
	~RPN();
	RPN &operator=(const RPN &other);
	static int calculate(const std::string &expr);

private:
	std::stack<int> _values;
	int eval(const std::string &expr);
	static bool isOperator(char c);
	void apply(char op);
};

#endif
