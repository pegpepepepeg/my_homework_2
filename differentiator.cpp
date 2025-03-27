//Change this text to REAL or COMPLEX to select modes
#define REAL


#include <iostream>
#include <unordered_map>
#include <complex>
#include <stack>
#include "expression.hpp"
#define GENERATE_ERROR
#ifdef REAL
#undef GENERATE_ERROR
bool is_complex = false;
#define evt double
#endif
#ifdef COMPLEX
#undef GENERATE_ERROR
bool is_complex = true;
#define evt std::complex<double>
#endif

std::complex<double> parseComplex(std::string str) {
	size_t pos = str.find('+');
	if (str.back() == 'i' && pos != std::string::npos)
		return std::complex<double>(std::stod(str.substr(0, pos)), std::stod(str.substr(pos + 1, str.size() - 1)));
	if (str.back() == 'i' && pos == std::string::npos)
		return std::complex<double>(0, std::stod(str));
	return std::complex<double>(std::stod(str), 0);
}


Expression<evt> parse(std::string str) {
	std::stack<Expression<evt>> exprstack;
	std::string lexem;
	std::stringstream ss(str);
	while (true) {
		if (ss >> lexem) {
			if (std::isdigit(lexem.front()) || lexem.front() == '.')
			{
#ifdef COMPLEX
				evt var = parseComplex(lexem);
#endif 
#ifdef REAL
				evt var = std::stod(lexem);
#endif
				exprstack.push(Expression<evt>(lexem));
				continue;
			}
			if (lexem == "+") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				Expression<evt> x = exprstack.top(); exprstack.pop();
				exprstack.push(x + y);
				continue;
			}
			if (lexem == "-") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				Expression<evt> x = exprstack.top(); exprstack.pop();
				exprstack.push(x - y);
				continue;
			}
			if (lexem == "*") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				Expression<evt> x = exprstack.top(); exprstack.pop();
				exprstack.push(x * y);
				continue;
			}
			if (lexem == "/") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				Expression<evt> x = exprstack.top(); exprstack.pop();
				exprstack.push(x * y);
				continue;
			}
			if (lexem == "^") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				Expression<evt> x = exprstack.top(); exprstack.pop();
				exprstack.push(x ^ y);
				continue;
			}
			if (lexem == "sin") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				exprstack.push(y.sin());
				continue;
			}
			if (lexem == "cos") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				exprstack.push(y.cos());
				continue;
			}
			if (lexem == "exp") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				exprstack.push(y.exp());
				continue;
			}
			if (lexem == "ln") {
				Expression<evt> y = exprstack.top(); exprstack.pop();
				exprstack.push(y.ln());
				continue;
			}
			exprstack.push(Expression<evt>(lexem));
		}
		else if (ss.eof())
			break;
	}
	return exprstack.top();
}

int main(int argc, char** argv) {
#ifdef GENERATE_ERROR
	std::cout << "This executable was compiled incorrectly!\n";
	return -1;
#endif
	std::string str = "abcdef";
	if (argc - 1 == 0)
		throw std::runtime_error("Too little arguments: 0");
	if (argc - 1 == 1)
		throw std::runtime_error("Too little arguments: 1");
	std::string mode = argv[1];
	Expression<evt> expr = parse(argv[2]);
	if (mode == "--diff") {
		if (argc - 1 == 2)
			throw std::runtime_error("Too little arguments for DIFF: 2");
		if (argc - 1 == 3)
			throw std::runtime_error("Too little arguments for DIFF: 3");
		if (argv[3] == "--by")
			throw std::runtime_error("Missing --by");
		std::cout << expr.differentiate(argv[4]).to_string();
	}
	if (mode == "--eval") {
		std::unordered_map<std::string, evt> mp;
		for (int i = 3; i < argc; i++) {
			std::string var = std::string(argv[i]);
			if (var.size() == 0)
				throw std::runtime_error("Incorrect variable definition");
			auto pos = var.find('=');
			if (pos == std::string::npos || var.back() == '=')
				throw std::runtime_error("Incorrect variable definition");
#ifdef COMPLEX
				mp[var.substr(0, pos)] = parseComplex(var.substr(pos + 1));
#endif
#ifdef REAL
				mp[var.substr(0, pos)] = std::stod(var.substr(pos + 1));
#endif
		}
		std::cout << expr.evaluate(mp) << '\n';
	}
}
