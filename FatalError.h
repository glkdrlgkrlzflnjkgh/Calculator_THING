#pragma once
#include <stdexcept>
#include <string>

class FatalError : public std::runtime_error {
public:
    explicit FatalError(const std::string& msg)
        : std::runtime_error(msg) {}
};
