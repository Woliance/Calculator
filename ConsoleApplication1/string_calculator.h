#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <algorithm>

// Add support for exponential and square roots

unsigned int digit_to_decimal(char digit);

char decimal_to_digit(unsigned int decimal);

std::string trim_leading_zeros(std::string num);

std::string add(std::string lhs, std::string rhs);

std::string subtract(std::string lhs, std::string rhs);

std::string multiply(std::string lhs, std::string rhs);

std::string numTimes(std::string lhs, std::string result);

bool compare(std::string lhs, std::string rhs);

std::string division(std::string dividend, std::string divisor);

std::string modulus(std::string dividend, std::string divisor);

std::string add_whole(std::string lhs, std::string rhs);

std::string subtract_whole(std::string lhs, std::string rhs);

#endif  // STRING_CALCULATOR_H
