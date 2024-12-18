#pragma once
#include <exception>

class Invalid_Input : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input";
    }
};


