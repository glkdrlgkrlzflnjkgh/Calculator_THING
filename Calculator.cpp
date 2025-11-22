#include "Calculator.h"
#include "CalculatorErrors.h"
#include <stdexcept>
#include <cctype>
#include <iostream>
#include <cmath>
#include <limits>
#include "Config.h"

// Basic arithmetic operations
double Calculator::add(double a, double b) { return a + b; }
double Calculator::subtract(double a, double b) { return a - b; }
double Calculator::multiply(double a, double b) { return a * b; }
double Calculator::divide(double a, double b) {
    if (b == 0) throw std::invalid_argument("Division by zero");
    return a / b;
}

// Parser class
class Parser {
public:
    Parser(const std::string& expr) : expr(expr), pos(0) {}
    int getPos() const { return static_cast<int>(pos); }
    bool end() const { return pos >= expr.size(); }

    double parseExpression() {
        if (debug) std::cout << "Parsing expression: " << expr << std::endl;
        double result = parseTerm();
        while (match('+') || match('-')) {
            char op = expr[pos - 1];
            double rhs = parseTerm();
            result = (op == '+') ? result + rhs : result - rhs;
            if (debug) std::cout << "result: of +/- " << result << std::endl;
        }
        return result;
    }

private:
    std::string expr;
    size_t pos;

    double parseTerm() {
        if (debug) std::cout << "Parsing term at pos " << pos << ": " << expr.substr(pos) << std::endl;
        double result = parsePower();
        while (match('*') || match('/')) {
            char op = expr[pos - 1];
            double rhs = parsePower();
            if (op == '*') result *= rhs;
            else {
                if (rhs == 0) throw Calc_DivideByZeroError();
                result /= rhs;
            }
        }
        return result;
    }

    double parsePower() {
        double result = parseFactor();
        while (match('^')) {
            double exponent = parsePower(); // right-associative
            result = std::pow(result, exponent);
        }
        return result;
    }

    double parseFactor() {
        skipWhitespace();

        if (match('(')) {
            size_t checkpoint = pos;
            double result = parseExpression();

            if (!match(')')) {
                pos = checkpoint; // optional: rewind to start of subexpression
                throw Calc_SyntaxError("Expected ')'", pos);
            }

            return result;
        }

        return parseNumber();
    }

    double parseNumber() {
        skipWhitespace();
        size_t start = pos;
        while (pos < expr.size() && (isdigit(expr[pos]) || expr[pos] == '.')) pos++;
        if (expr.substr(pos, 3) == "inf") {
            pos += 3;
            return std::numeric_limits<double>::infinity();
        }
        if (start == pos) {
            std::string got = (pos < expr.size()) ? expr.substr(pos, 120) : "<EOL>";
            std::string msg = "Expected number but got '" + got + "'";
            throw Calc_SyntaxError(msg, pos);

        }
        return std::stod(expr.substr(start, pos - start));
    }

    bool match(char expected) {
        skipWhitespace();
        if (pos < expr.size() && expr[pos] == expected) {
            pos++;
            return true;
        }
        return false;
    }

    void skipWhitespace() {
        while (pos < expr.size() && std::isspace(expr[pos])) pos++;
    }
};

// Calculator evaluation
double Calculator::evaluate(const std::string& expression) {
    try {
        Parser parser(expression);
        double result = parser.parseExpression();
        if (!parser.end()) {
            throw Calc_SyntaxError("Expected EOL, but found trailing data!", parser.getPos());
        }
        return result;
    }
    catch (const Calc_SyntaxError& e) {
        std::cerr << expression.substr(0, e.position());
        if (e.position() < expression.size()) {
            std::cerr << "\033[1;31m" << expression.substr(e.position()) << "\033[0m\n";
        }
        else {
            std::cerr << "\033[1;31m\033[0m\n";
        }
        std::cerr << std::string(e.position(), ' ') << "\033[1;31m^\033[0m\n";
        std::cerr << "\033[1mThe ^ shows where we found the error, but the mistake could be before or after it.\033[0m\n";
        std::cerr << "SyntaxError: " << e.what() << "\n";
        throw;
    }
}