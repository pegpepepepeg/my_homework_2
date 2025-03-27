#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <cmath>
#include <complex>

template <typename T>
class Expression {
public:
    T held_value;
    std::string held_variable;
    std::shared_ptr<Expression<T>> l, r;
    enum class ExpressionType { CONSTANT, VARIABLE, UNARY_NEGATION, UNARY_SIN, UNARY_COS, UNARY_LOG, UNARY_EXP, BINARY_ADDITION, BINARY_SUBTRACTION, BINARY_MULTIPLICATION, BINARY_DIVISION, BINARY_EXPONENTIATION };
    ExpressionType held_type;

    Expression(T value);
    Expression(std::string variable);
    Expression(ExpressionType type, Expression<T> left);
    Expression(ExpressionType type, Expression<T> left, Expression<T> right);
    Expression<T>& operator=(const Expression& other);

    T evaluate(std::unordered_map<std::string, T>& vars);

    T evaluate();

    std::string to_string();

    Expression<T> operator+(const Expression& other) const;
    Expression<T> operator-(const Expression& other) const;
    Expression<T> operator-() const;
    Expression<T> operator*(const Expression& other) const;
    Expression<T> operator/(const Expression& other) const;
    Expression<T> operator^(const Expression& other) const;
    Expression<T> sin() const;
    Expression<T> cos() const;
    Expression<T> exp() const;
    Expression<T> ln() const;
    void substitute(const std::string& variable, T value);
    Expression<T> differentiate(const std::string& variable);
private:
    static std::string custom_to_string(char x);
    static std::string custom_to_string(short x);
    static std::string custom_to_string(int x);
    static std::string custom_to_string(long long x);
    static std::string custom_to_string(float x);
    static std::string custom_to_string(double x);
    static std::string custom_to_string(long double x);
    static std::string custom_to_string(std::complex<char> x);
    static std::string custom_to_string(std::complex<short> x);
    static std::string custom_to_string(std::complex<int> x);
    static std::string custom_to_string(std::complex<long long> x);
    static std::string custom_to_string(std::complex<float> x);
    static std::string custom_to_string(std::complex<double> x);
    static std::string custom_to_string(std::complex<long double> x);
};
