#include "Calculator.h"
#include "CalculatorErrors.h"
#include <stdexcept>
#include <cctype>
#include <iostream>
#include <cmath>
#include "Config.h"

// Set debug flag based on build configuration


// Basic arithmetic operations for Calculator

// Adds two numbers
double Calculator::add(double a, double b) {
    return a + b;
}

// Subtracts b from a
double Calculator::subtract(double a, double b) {
    return a - b;
}

// Multiplies two numbers
double Calculator::multiply(double a, double b) {
    return a * b;
}

// Divides a by b, throws if b is zero
double Calculator::divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

// Parser class for evaluating mathematical expressions
class Parser {
public:
    int getPos() const;
    // Initialize parser with the expression string
    Parser(const std::string& expr)
        : expr(expr), pos(0) {}

    // Check if parsing has reached the end of the expression
    bool end() const {
        return pos >= expr.size();
    }

    // Parse and evaluate an expression (handles + and -)
    double parseExpression() {
        if (debug) {
            std::cout << "Parsing expression: " << expr << std::endl;
        }
        double result = parseTerm();
        while (match('+') || match('-')) {
            char op = expr[pos - 1];
            double rhs = parseTerm();

            result = (op == '+') ? result + rhs : result - rhs;
            if (debug) {
                std::cout << "result: of +/- " << result << std::endl;
            }
        }
        return result;
    }

private:
    std::string expr; // Expression to parse
    size_t pos;       // Current position in the expression

    // Parse a term (handles * and /)
    double parseTerm() {
        if (debug) {
            std::cout << "Parsing term at pos " << pos << ": " << expr.substr(pos) << std::endl;
        }
        double result = parsePower();
        while (match('*') || match('/')) {
            char op = expr[pos - 1];
            double rhs = parsePower();
            if (op == '*') {
                result *= rhs;
            } else {
                if (rhs == 0) {
					throw Calc_DivideByZeroError();
                }
                result /= rhs;
            }
        }
        return result;
    }

    // Parse a power (handles ^, right-associative)
    double parsePower() {
        double result = parseFactor();
        while (match('^')) {
            double exponent = parsePower(); // right-associative
            result = std::pow(result, exponent);
        }
        return result;
    }

    // Parse a factor (number or parenthesized expression)
    double parseFactor() {
        skipWhitespace();

        if (match('(')) {
            double result = parseExpression();
            if (!match(')')) {
                throw Calc_SyntaxError("Expected ')'",pos);
            }
            return result;
        }

        return parseNumber();
    }

    // Parse a number from the expression
    double parseNumber() {
        skipWhitespace();
        size_t start = pos;
        while (pos < expr.size() && (isdigit(expr[pos]) || expr[pos] == '.')) {
            pos++;
        }
        if (expr.substr(pos, 3) == "inf") {
            pos += 3;
            return std::numeric_limits<double>::infinity();
        }
        if (start == pos) {
            throw Calc_SyntaxError("Expected number",pos);
        }
        return std::stod(expr.substr(start, pos - start));
    }

    // Match and consume the expected character if present
    bool match(char expected) {
        skipWhitespace();
        if (pos < expr.size() && expr[pos] == expected) {
            pos++;
            return true;
        }
        return false;
    }

    // Skip whitespace characters in the expression
    void skipWhitespace() {
        while (pos < expr.size() && std::isspace(expr[pos])) {
            pos++;
        }
    }

};
int Parser::getPos() const {
    return static_cast<int>(pos);
}
// Evaluate a mathematical expression using the Parser
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
        // Print expression with error section in red
        std::cerr << expression.substr(0, e.position()); // before error
        if (e.position() < expression.size()) {
            std::cerr << "\033[1;31m" << expression.substr(e.position()) << "\033[0m\n"; // red from error to end
        }
        

        // Print caret under error position
        std::cerr << std::string(e.position(), ' ') << "\033[1;31m^\033[0m\n";
        std::cerr << "\033[1mThe ^ shows where we found the error — the mistake is probably there.\033[0m\n";

        // Print error message
        std::cerr << "SyntaxError: " << e.what() << "\n";
        throw;
    }
}