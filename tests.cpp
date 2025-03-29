#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <cmath>
#include "expression.hpp"

int main()
{
    Expression<double> x = Expression<double>("x");
    Expression<double> c1 = Expression<double>(1);
    Expression<double> c2 = Expression<double>(2);
    Expression<double> c3 = Expression<double>(3);
    Expression<double> result = Expression<double>(0);
    std::cout << "Testing creation and output...\n";
    result = (x + c1) * (x * x + c2) * c3 + c3 + x.ln() + (x + c1).exp() + (x + c1).sin() + (x + c1).cos() + (x ^ x) + (x / c2) + (-c1);
    std::cout << result.to_string() << '\n';
    std::cout << "Testing substitution and basic computation...\n";
    result.substitute("x", 1);
    std::cout << result.to_string() << '\n';
    std::cout << "=" << result.evaluate() << '\n';
    std::cout << "Testing computation...\n";
    result = (x.sin() ^ c2) + (x.cos() ^ c2) - c1;
    std::unordered_map<std::string, double> vars;
    for (double xv = 0; xv <= std::acos(-1); xv += 0.1) {
        vars["x"] = xv;
        if (std::abs(result.evaluate(vars)) > 1e-10) {
            std::cout << "Failed\n";
            break;
        }
    }
    std::cout << "Finished\n";
    std::cout << "Testing differentiation...\n";
    std::cout << result.differentiate("x").to_string() << '\n';
    std::cout << "Finished\n";
    return 0;
}
