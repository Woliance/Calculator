#include "WholeNumber.h"

#include <algorithm>

WholeNumber::WholeNumber() : number_("0"), value_(0) {}

WholeNumber::WholeNumber(const std::string& number) : number_(number), value_(0) {
    // Remove leading zeros
    number_.erase(0, number_.find_first_not_of('0'));
    // Replace empty string with "0"
    if (number_.empty()) {
        number_ = "0";
    }
}

WholeNumber::WholeNumber(int num) : value_(num) {
    number_ = std::to_string(num);
}

std::string WholeNumber::getNumber() const {
    return number_;
}

void WholeNumber::setNumber(const std::string& number) {
    number_ = number;
}

std::string WholeNumber::to_string() const {
    return number_;
}


WholeNumber WholeNumber::operator+(const WholeNumber& rhs) const {
    std::string result;
    int carry = 0;
    int i = number_.size() - 1;
    int j = rhs.number_.size() - 1;
    while (i >= 0 || j >= 0 || carry != 0) {
        int sum = carry;
        if (i >= 0) {
            sum += number_[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += rhs.number_[j] - '0';
            j--;
        }
        carry = sum / 10;
        sum %= 10;
        result += (char)(sum + '0');
    }
    std::reverse(result.begin(), result.end());
    return WholeNumber(result);
}

WholeNumber WholeNumber::operator-(const WholeNumber& rhs) const {
    std::string result;
    int borrow = 0;
    int i = number_.size() - 1;
    int j = rhs.number_.size() - 1;
    while (i >= 0 || j >= 0) {
        int diff = borrow;
        if (i >= 0) {
            diff -= number_[i] - '0';
            i--;
        }
        if (j >= 0) {
            diff += rhs.number_[j] - '0';
            j--;
        }
        if (diff < 0) {
            borrow = -1;
            diff += 10;
        }
        else {
            borrow = 0;
        }
        result += (char)(diff + '0');
    }
    std::reverse(result.begin(), result.end());
    return WholeNumber(result);
}

WholeNumber WholeNumber::operator*(const WholeNumber& rhs) const {
    // TODO: Implement multiplication
}

WholeNumber WholeNumber::operator/(const WholeNumber& rhs) const {
    // TODO: Implement division
}