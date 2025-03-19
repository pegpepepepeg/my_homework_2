#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <cmath>

template <typename T>
class Expression {
public:
    T held_value;
    std::string held_variable;
    std::shared_ptr<Expression<T>> l, r;
    enum class ExpressionType { CONSTANT, VARIABLE, UNARY_NEGATION, UNARY_SIN, UNARY_COS, UNARY_LOG, UNARY_EXP, BINARY_ADDITION, BINARY_SUBTRACTION, BINARY_MULTIPLICATION, BINARY_DIVISION, BINARY_EXPONENTIATION };
    ExpressionType held_type;
    
    Expression(T value) : held_type(ExpressionType::CONSTANT), held_value(value) {};
    Expression(std::string variable) : l(nullptr), r(nullptr), held_type(ExpressionType::VARIABLE), held_variable(variable) {};
    Expression(ExpressionType type, Expression<T> left) : l(std::make_shared<Expression<T>>(left)), r(nullptr), held_type(type) {};
    Expression(ExpressionType type, Expression<T> left, Expression<T> right) : l(std::make_shared<Expression<T>>(left)), r(std::make_shared<Expression<T>>(right)), held_type(type) {};
    Expression<T>& operator=(const Expression& other) {
        if (this != &other) {
            held_value = other.held_value;
            held_variable = other.held_variable;
            held_type = other.held_type;
            l = other.l ? std::make_shared<Expression>(*other.l) : nullptr;
            r = other.r ? std::make_shared<Expression>(*other.r) : nullptr;
        }
        return *this;
    }
    
    T evaluate(std::unordered_map<std::string, T>& vars) {
        switch (held_type) {
        case ExpressionType::CONSTANT: return held_value;
        case ExpressionType::VARIABLE: if (vars.find(held_variable) == vars.end()) throw std::runtime_error(":<"); else return vars[held_variable];
        case ExpressionType::UNARY_NEGATION: return -l->evaluate(vars);
        case ExpressionType::UNARY_SIN: return std::sin(l->evaluate(vars));
        case ExpressionType::UNARY_COS: return std::cos(l->evaluate(vars));
        case ExpressionType::UNARY_EXP: return std::exp(l->evaluate(vars));
        case ExpressionType::UNARY_LOG: return std::log(l->evaluate(vars));
        case ExpressionType::BINARY_ADDITION: return l->evaluate(vars) + r->evaluate(vars);
        case ExpressionType::BINARY_SUBTRACTION: return l->evaluate(vars) - r->evaluate(vars);
        case ExpressionType::BINARY_MULTIPLICATION: return l->evaluate(vars) * r->evaluate(vars);
        case ExpressionType::BINARY_DIVISION: return l->evaluate(vars) / r->evaluate(vars);
        case ExpressionType::BINARY_EXPONENTIATION: return std::pow(l->evaluate(vars), r->evaluate(vars));
        default: throw std::runtime_error(":<");
        }
    }
    
    T evaluate() {
        std::unordered_map<std::string, T> vars;
        return evaluate(vars);
    }

    std::string to_string() {
        switch (held_type) {
        case ExpressionType::CONSTANT: return std::to_string(held_value);
        case ExpressionType::VARIABLE: return held_variable;
        case ExpressionType::UNARY_NEGATION: return "-"+l->to_string();
        case ExpressionType::UNARY_SIN: return "sin(" + l->to_string() + ")";
        case ExpressionType::UNARY_COS: return "cos("+l->to_string() + ")";
        case ExpressionType::UNARY_EXP: return "exp("+l->to_string() + ")";
        case ExpressionType::UNARY_LOG: return "log("+l->to_string() + ")";
        case ExpressionType::BINARY_ADDITION: return "(" + l->to_string() + " + " + r->to_string() + ")";
        case ExpressionType::BINARY_SUBTRACTION: return "(" + l->to_string() + " - " + r->to_string() + ")";
        case ExpressionType::BINARY_MULTIPLICATION: return "(" + l->to_string() + " * " + r->to_string() + ")";
        case ExpressionType::BINARY_DIVISION: return "(" + l->to_string() + " / " + r->to_string() + ")";
        case ExpressionType::BINARY_EXPONENTIATION: return "(" + l->to_string() + " ^ " + r->to_string() + ")";
        default: throw std::runtime_error(":<");
        }
    }

    Expression<T> operator+(const Expression& other) const {
        return Expression<T>(ExpressionType::BINARY_ADDITION, *this, other);
    }
    Expression<T> operator-(const Expression& other) const {
        return Expression<T>(ExpressionType::BINARY_SUBTRACTION, *this, other);
    }
    Expression<T> operator-() const {
        return Expression<T>(ExpressionType::UNARY_NEGATION, *this);
    }
    Expression<T> operator*(const Expression& other) const {
        return Expression<T>(ExpressionType::BINARY_MULTIPLICATION, *this, other);
    }
    Expression<T> operator/(const Expression& other) const {
        return Expression<T>(ExpressionType::BINARY_DIVISION, *this, other);
    }
    Expression<T> operator^(const Expression& other) const {
        return Expression<T>(ExpressionType::BINARY_EXPONENTIATION, *this, other);
    }
    Expression<T> sin() const {
        return Expression<T>(ExpressionType::UNARY_SIN, *this);
    }
    Expression<T> cos() const {
        return Expression<T>(ExpressionType::UNARY_COS, *this);
    }
    Expression<T> exp() const {
        return Expression<T>(ExpressionType::UNARY_EXP, *this);
    }
    Expression<T> ln() const {
        return Expression<T>(ExpressionType::UNARY_LOG, *this);
    }
    void substitute(const std::string& variable, T value) {
        if (held_type == ExpressionType::VARIABLE)
            held_type = ExpressionType::CONSTANT, held_value = value;
        if (l != nullptr)
            l->substitute(variable, value);
        if (r != nullptr)
            r->substitute(variable, value);
    }
};

int main()
{
    Expression<double> x = Expression<double>("x");
    Expression<double> c1 = Expression<double>(1);
    Expression<double> c2 = Expression<double>(2);
    Expression<double> c3 = Expression<double>(3);
    Expression<double> result = Expression<double>(0);
    std::cout << "Testing creation and output...\n";
    result = (x + c1) * (x * x + c2) * c3 + c3 + x.ln() +(x + c1).exp() + (x + c1).sin() + (x + c1).cos() + (x ^ x) + (x / c2) +(-c1);
    std::cout << result.to_string() << '\n';
    std::cout << "Testing substitution and basic computation...\n";
    result.substitute("x", 1);
    std::cout << result.to_string() << '\n';
    std::cout << "=" << result.evaluate() << '\n';
    std::cout << "Testing computation...\n";
    result = (x.sin() ^ c2) + (x.cos() ^ c2) - c1;
    std::unordered_map<std::string, double> vars;
    for(double xv = 0; xv <= std::acos(-1); xv += 0.1) {
        vars["x"] = xv;
        if (std::abs(result.evaluate(vars)) > 1e-10) {
            std::cout << "Failed\n";
            break;
        }
    }
    std::cout << "Finished\n";
}
