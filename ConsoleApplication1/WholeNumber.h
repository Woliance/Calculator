#ifndef WHOLENUMBER_H
#define WHOLENUMBER_H

#include <string>
#include <vector>
#include <algorithm>

class WholeNumber {
public:
    WholeNumber();
    WholeNumber(const std::string& number);
    std::string to_string() const;
    WholeNumber(int num);
    std::string getNumber() const;
    void setNumber(const std::string& number);
    WholeNumber operator+(const WholeNumber& rhs) const;
    WholeNumber operator-(const WholeNumber& rhs) const;
    WholeNumber operator*(const WholeNumber& rhs) const;
    WholeNumber operator/(const WholeNumber& rhs) const;
    bool operator==(const WholeNumber& rhs) const;
    bool operator!=(const WholeNumber& rhs) const;
    bool operator<(const WholeNumber& rhs) const;
    bool operator>(const WholeNumber& rhs) const;
    bool operator<=(const WholeNumber& rhs) const;
    bool operator>=(const WholeNumber& rhs) const;

private:
    std::string number_;
    int value_;
    std::vector<int> digits;
};

#endif // WHOLENUMBER_H
