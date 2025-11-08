#pragma once
#include <stdexcept>
#include <string>

class CalculatorException : public std::runtime_error {
public:
    CalculatorException(const std::string& message)
        : std::runtime_error(message) {}
};

class Calc_SyntaxError : public CalculatorException {
public:
    Calc_SyntaxError(const std::string& message, const std::int32_t pos)
        : CalculatorException("Syntax error: " + message + " at position " + std::to_string(pos)) {
    }
};

class Calc_DivideByZeroError : public CalculatorException {
public:
    Calc_DivideByZeroError()
        : CalculatorException("Math error: Division by zero") {
    }
};