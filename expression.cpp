#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <cmath>
#include <complex>
#include "expression.hpp"

template <typename T>
Expression<T>::Expression(T value) : held_type(ExpressionType::CONSTANT), held_value(value) {};
template <typename T>
Expression<T>::Expression(std::string variable) : l(nullptr), r(nullptr), held_type(ExpressionType::VARIABLE), held_variable(variable) {};
template <typename T>
Expression<T>::Expression(ExpressionType type, Expression<T> left) : l(std::make_shared<Expression<T>>(left)), r(nullptr), held_type(type) {};
template <typename T>
Expression<T>::Expression(ExpressionType type, Expression<T> left, Expression<T> right) : l(std::make_shared<Expression<T>>(left)), r(std::make_shared<Expression<T>>(right)), held_type(type) {};
template <typename T>
Expression<T>& Expression<T>::operator=(const Expression& other) {
    if (this != &other) {
        held_value = other.held_value;
        held_variable = other.held_variable;
        held_type = other.held_type;
        l = other.l ? std::make_shared<Expression>(*other.l) : nullptr;
        r = other.r ? std::make_shared<Expression>(*other.r) : nullptr;
    }
    return *this;
}
template <typename T>
T Expression<T>::evaluate(std::unordered_map<std::string, T>& vars) {
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
template <typename T>
T Expression<T>::evaluate() {
    std::unordered_map<std::string, T> vars;
    return evaluate(vars);
}
template <typename T>
std::string Expression<T>::to_string() {
    switch (held_type) {
    case ExpressionType::CONSTANT: return custom_to_string(held_value);
    case ExpressionType::VARIABLE: return held_variable;
    case ExpressionType::UNARY_NEGATION: return "-" + l->to_string();
    case ExpressionType::UNARY_SIN: return "sin(" + l->to_string() + ")";
    case ExpressionType::UNARY_COS: return "cos(" + l->to_string() + ")";
    case ExpressionType::UNARY_EXP: return "exp(" + l->to_string() + ")";
    case ExpressionType::UNARY_LOG: return "log(" + l->to_string() + ")";
    case ExpressionType::BINARY_ADDITION: return "(" + l->to_string() + " + " + r->to_string() + ")";
    case ExpressionType::BINARY_SUBTRACTION: return "(" + l->to_string() + " - " + r->to_string() + ")";
    case ExpressionType::BINARY_MULTIPLICATION: return "(" + l->to_string() + " * " + r->to_string() + ")";
    case ExpressionType::BINARY_DIVISION: return "(" + l->to_string() + " / " + r->to_string() + ")";
    case ExpressionType::BINARY_EXPONENTIATION: return "(" + l->to_string() + " ^ " + r->to_string() + ")";
    default: throw std::runtime_error(":<");
    }
}
template <typename T>
Expression<T> Expression<T>::operator+(const Expression& other) const {
    return Expression<T>(ExpressionType::BINARY_ADDITION, *this, other);
}
template <typename T>
Expression<T> Expression<T>::operator-(const Expression& other) const {
    return Expression<T>(ExpressionType::BINARY_SUBTRACTION, *this, other);
}
template <typename T>
Expression<T> Expression<T>::operator-() const {
    return Expression<T>(ExpressionType::UNARY_NEGATION, *this);
}
template <typename T>
Expression<T> Expression<T>::operator*(const Expression& other) const {
    return Expression<T>(ExpressionType::BINARY_MULTIPLICATION, *this, other);
}
template <typename T>
Expression<T> Expression<T>::operator/(const Expression& other) const {
    return Expression<T>(ExpressionType::BINARY_DIVISION, *this, other);
}
template <typename T>
Expression<T> Expression<T>::operator^(const Expression& other) const {
    return Expression<T>(ExpressionType::BINARY_EXPONENTIATION, *this, other);
}
template <typename T>
Expression<T> Expression<T>::sin() const {
    return Expression<T>(ExpressionType::UNARY_SIN, *this);
}
template <typename T>
Expression<T> Expression<T>::cos() const {
    return Expression<T>(ExpressionType::UNARY_COS, *this);
}
template <typename T>
Expression<T> Expression<T>::exp() const {
    return Expression<T>(ExpressionType::UNARY_EXP, *this);
}
template <typename T>
Expression<T> Expression<T>::ln() const {
    return Expression<T>(ExpressionType::UNARY_LOG, *this);
}
template <typename T>
void Expression<T>::substitute(const std::string& variable, T value) {
    if (held_type == ExpressionType::VARIABLE)
        held_type = ExpressionType::CONSTANT, held_value = value;
    if (l != nullptr)
        l->substitute(variable, value);
    if (r != nullptr)
        r->substitute(variable, value);
}
template <typename T>
Expression<T> Expression<T>::differentiate(const std::string& variable) {
    switch (held_type) {
        case ExpressionType::CONSTANT: return (T)0;
        case ExpressionType::VARIABLE: return (variable == held_variable) ? (T)1 : (T)0;
        case ExpressionType::UNARY_NEGATION: return l->differentiate(variable);
        case ExpressionType::UNARY_SIN: return l->cos() * (l->differentiate(variable));
        case ExpressionType::UNARY_COS: return -l->sin() * (l->differentiate(variable));
        case ExpressionType::UNARY_EXP: return l->exp() * (l->differentiate(variable));
        case ExpressionType::UNARY_LOG: return Expression((T)1)/(*l) * (l->differentiate(variable));
        case ExpressionType::BINARY_ADDITION: return (l->differentiate(variable)) + (r->differentiate(variable));
        case ExpressionType::BINARY_SUBTRACTION: return (l->differentiate(variable)) - (r->differentiate(variable));
        case ExpressionType::BINARY_MULTIPLICATION: return (l->differentiate(variable)) * (*r) + (*l) * (r->differentiate(variable));
        case ExpressionType::BINARY_DIVISION: return (((l->differentiate(variable) * (*l)) - ((*l) * r->differentiate(variable))) / ((*r) * (*r)));
        case ExpressionType::BINARY_EXPONENTIATION: return ((*r) * ((*l) ^ ((*r) - ((T)1))) * (l->differentiate(variable))) - ((((*l) ^ (*r)) * (r->differentiate(variable))) * l->ln());
        default: throw std::runtime_error(":<");
    }
}

template <typename T> std::string Expression<T>::custom_to_string(char x) { return std::to_string((long long)x); }
template <typename T> std::string Expression<T>::custom_to_string(short x) { return std::to_string((long long)x); }
template <typename T> std::string Expression<T>::custom_to_string(int x) { return std::to_string((long long)x); }
template <typename T> std::string Expression<T>::custom_to_string(long long x) { return std::to_string((long long)x); }
template <typename T> std::string Expression<T>::custom_to_string(float x) { return std::to_string(x); }
template <typename T> std::string Expression<T>::custom_to_string(double x) { return std::to_string(x); }
template <typename T> std::string Expression<T>::custom_to_string(long double x) { return std::to_string(x); }
template <typename T> std::string Expression<T>::custom_to_string(std::complex<char> x) { return std::to_string((long long)x.real()) + "+" + std::to_string((long long)x.imag()); }
template <typename T> std::string Expression<T>::custom_to_string(std::complex<short> x) { return std::to_string((long long)x.real()) + "+" + std::to_string((long long)x.imag()); }
template <typename T> std::string Expression<T>::custom_to_string(std::complex<int> x) { return std::to_string((long long)x.real()) + "+" + std::to_string((long long)x.imag()); }
template <typename T> std::string Expression<T>::custom_to_string(std::complex<long long> x) { return std::to_string((long long)x.real()) + "+" + std::to_string((long long)x.imag()); }
template <typename T> std::string Expression<T>::custom_to_string(std::complex<float> x) { return std::to_string(x.real()) + "+" + std::to_string(x.imag()); }
template <typename T> std::string Expression<T>::custom_to_string(std::complex<double> x) { return std::to_string(x.real()) + "+" + std::to_string(x.imag()); }
template <typename T> std::string Expression<T>::custom_to_string(std::complex<long double> x) { return std::to_string(x.real()) + "+" + std::to_string(x.imag()); }

template class Expression<char>;
template class Expression<short>;
template class Expression<int>;
template class Expression<long long>;
template class Expression<float>;
template class Expression<double>;
template class Expression<long double>;
template class Expression <std::complex<char>>;
template class Expression <std::complex<short>>;
template class Expression <std::complex<int>>;
template class Expression <std::complex<long long>>;
template class Expression <std::complex<float>>;
template class Expression <std::complex<double>>;
template class Expression <std::complex<long double>>;
