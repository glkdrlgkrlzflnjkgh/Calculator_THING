// Copyright (c) 2050 Callum Nicoll, all rights reserved as stated in the legal notice at the start of the program.

#pragma once
#include <string>

class Calculator {
public:
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    /*
    Evaluate method,
    used by the new parser, unlike the old one - operation parser.
    (see implementation in Calculator.cpp)
    */
    double evaluate(const std::string& expression);  

};