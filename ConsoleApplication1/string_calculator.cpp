#include <iostream>
#include <algorithm>
#include <string>
#include "./string_calculator.h"
#include "WholeNumber.h"

using std::cout, std::endl, std::string;


unsigned int digit_to_decimal_unsigned(char digit) {
	if (isdigit(digit)) {
		return digit - '0';
	}
	else if (digit == '.') {
		return -1; // Use -1 to represent decimal point
	}
	else {
		throw std::invalid_argument("Character entered is not a digit or a decimal.");
	}
}

unsigned int digit_to_decimal(char digit)
{
	return 0;
}

char decimal_to_digit(unsigned int decimal) {
	if (decimal > 9)
	{
		throw std::invalid_argument("Decimal entered is greater than 9 or less than 0.");
	}
	return decimal + '0';
}

string trim_leading_zeros(string num) {
	bool wasNeg = false;
	string result = "";
	if (num.find("-") != string::npos) // Number represented is negative
	{
		wasNeg = true;
		num.erase(0, 1); // initially delete the negative sign
	}
	size_t i = 0;
	while (num.at(i) == '0')
	{
		i++;
		if (i == num.length()) // if the number entered consists soley of 0's
		{
			return "0";
		}
	}
	while (i != num.length())
	{
		result += num.at(i);
		i++;
	}
	if (wasNeg)
	{
		result.insert(0, "-");
	}
	return result;
}

string add(string lhs, string rhs) {
	// Check if input strings contain decimal point
	bool has_decimal_lhs = lhs.find('.') != string::npos;
	bool has_decimal_rhs = rhs.find('.') != string::npos;

	// Split input strings at decimal point
	string lhs_whole = has_decimal_lhs ? lhs.substr(0, lhs.find('.')) : lhs;
	string lhs_frac = has_decimal_lhs ? lhs.substr(lhs.find('.') + 1) : "";
	string rhs_whole = has_decimal_rhs ? rhs.substr(0, rhs.find('.')) : rhs;
	string rhs_frac = has_decimal_rhs ? rhs.substr(rhs.find('.') + 1) : "";

	// Calculate sum of whole numbers
	string whole_sum = add_whole(lhs_whole, rhs_whole);

	// Calculate sum of fractional parts
	string frac_sum = "";
	if (has_decimal_lhs || has_decimal_rhs) {
		// Add trailing zeros to the shorter fractional part
		while (lhs_frac.length() < rhs_frac.length()) {
			lhs_frac += '0';
		}
		while (rhs_frac.length() < lhs_frac.length()) {
			rhs_frac += '0';
		}
		// Calculate sum of fractional parts
		frac_sum = add_whole(lhs_frac, rhs_frac);
	}

	// Combine whole and fractional parts with decimal point
	string result = whole_sum;
	if (has_decimal_lhs || has_decimal_rhs) {
		result += '.';
		result += frac_sum;
	}

	return result;
}

std::string add_whole(std::string lhs, std::string rhs) {
	// Convert the input strings to whole numbers
	WholeNumber lhs_whole(lhs);
	WholeNumber rhs_whole(rhs);

	// Add the whole numbers
	WholeNumber result_whole = lhs_whole + rhs_whole;

	// Convert the result to a string
	std::string result = result_whole.to_string();

	return result;
}

string subtract(string lhs, string rhs) {
	// Check if input strings contain decimal point
	bool has_decimal_lhs = lhs.find('.') != string::npos;
	bool has_decimal_rhs = rhs.find('.') != string::npos;

	// Split input strings at decimal point
	string lhs_whole = has_decimal_lhs ? lhs.substr(0, lhs.find('.')) : lhs;
	string lhs_frac = has_decimal_lhs ? lhs.substr(lhs.find('.') + 1) : "";
	string rhs_whole = has_decimal_rhs ? rhs.substr(0, rhs.find('.')) : rhs;
	string rhs_frac = has_decimal_rhs ? rhs.substr(rhs.find('.') + 1) : "";

	// Calculate difference of whole numbers
	string whole_diff = subtract_whole(lhs_whole, rhs_whole);

	// Calculate difference of fractional parts
	string frac_diff = "";
	if (has_decimal_lhs || has_decimal_rhs) {
		// Add trailing zeros to the shorter fractional part
		while (lhs_frac.length() < rhs_frac.length()) {
			lhs_frac += '0';
		}
		while (rhs_frac.length() < lhs_frac.length()) {
			rhs_frac += '0';
		}
		// Calculate difference of fractional parts
		frac_diff = subtract_whole(lhs_frac, rhs_frac);
		// Remove trailing zeros from fractional part
		while (frac_diff.length() > 1 && frac_diff.back() == '0') {
			frac_diff.pop_back();
		}
	}

	// Combine whole and fractional parts with decimal point
	string result = whole_diff;
	if (!frac_diff.empty()) {
		result += "." + frac_diff;
	}
	return result;
}

string subtract_whole(string lhs, string rhs) {
	string result = "";
	int borrow = 0;

	// Pad the shorter string with zeros
	if (lhs.length() > rhs.length()) {
		rhs = string(lhs.length() - rhs.length(), '0') + rhs;
	}
	else if (rhs.length() > lhs.length()) {
		lhs = string(rhs.length() - lhs.length(), '0') + lhs;
	}

	// Calculate difference of each digit from right to left
	for (int i = lhs.length() - 1; i >= 0; i--) {
		int lhs_digit = digit_to_decimal(lhs[i]);
		int rhs_digit = digit_to_decimal(rhs[i]);

		// Handle decimal points separately
		if (lhs_digit == -1 && rhs_digit == -1) {
			result = '.' + result;
			continue;
		}
		else if (lhs_digit == -1) {
			lhs_digit = 0;
		}
		else if (rhs_digit == -1) {
			rhs_digit = 0;
		}

		int digit_diff = lhs_digit - rhs_digit - borrow;
		if (digit_diff < 0) {
			digit_diff += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}

		result = std::to_string(digit_diff) + result;
	}

	// Remove leading zeros from the result
	result.erase(0, std::min(result.find_first_not_of('0'), result.size() - 1));
	return result;
}


string multiply(string lhs, string rhs) {
	int topSide = 0;
	int bottomSide = 0;
	int product = 0;
	int carryOver = 0;
	string result = "";
	bool negFound = false;

	if (rhs.length() < lhs.length())  // swap them so the bigger number is on top
	{
		swap(lhs, rhs);
	}
	if (lhs.find('-') != string::npos && rhs.find('-') != string::npos) // if both are negative, it's ok because result is pos
	{
		rhs.erase(0, 1);  // deletes the negative
		lhs.erase(0, 1);
	}
	else if (rhs.find('-') != string::npos && lhs.find('-') == string::npos) // right is negative left positive
	{
		rhs.erase(0, 1);
		negFound = true;  // negFound is so we can slap a negative on at the end
	}
	else if (lhs.find('-') != string::npos && rhs.find('-') == string::npos) // left is negative, right positive
	{
		lhs.erase(0, 1);
		negFound = true;
	}
	string sum = "0";
	int counter = 1;
	for (int i = lhs.length() - 1; i >= 0; i--)  // nested for loop, one for the bigger number (top number) and one for the smaller number (bottom)
	{
		carryOver = 0; // reset carryOver
		for (int j = rhs.length() - 1; j >= 0; j--)
		{
			topSide = digit_to_decimal(rhs.at(j));
			bottomSide = digit_to_decimal(lhs.at(i));

			product = topSide * bottomSide + carryOver;
			carryOver = product / 10; // update carryOver for next iteration

			result += decimal_to_digit(product % 10); // append ones digit to result
		}
		if (carryOver != 0) // append any remaining carryOver to result
		{
			result += decimal_to_digit(carryOver);
		}
		int j = result.length() - 1;  // reverses the result since it's currently backwards
		string newResult = "";
		while (j >= 0)
		{
			newResult += result.at(j);
			j--;
		}
		sum = add(sum, newResult);  // add the sum to the normal result (not the reversed one) each time
		result = "";
		for (int k = 0; k < counter; k++)  // number of zeroes to add is equal to the outer loop (add one zero after first iteration (first row))
			result += "0";
		counter++;  // increments the counter so we know the next iteration will need 2 zeroes (second row)
	}
	if (negFound)
	{
		sum.insert(0, "-");
	}
	return sum;
}

string numTimes(string lhs, string result) {
	if (lhs == result)
		return "1";
	if (result == "0" || compare(lhs,result)) // if lhs > result, ie: 5 and 2, then return 0
		return "0";
	string i = "1";
 	string product = multiply(lhs,i);
	while (!compare(product,result)) // while (product is less than the result)
	{
		i = add(i,"1");
		product = multiply(lhs,i);
	}
	if (product == result) // bandaid solution (i is 1 too much i product > result at the end)
		return i;
	return subtract(i,"1");
}

bool compare (string lhs, string rhs) { // true if lhs > rhs
	if (lhs.length() > rhs.length()) // if they're different lengths
		return true;
	if (rhs.length() > lhs.length())
		return false;
	string a = "";
	string b = "";
	for (size_t i = 0; i < lhs.length(); i++) // compares digit by digit
	{
		a = lhs.at(i);
		b = rhs.at(i);
		if (stoi(a) < stoi(b))
			return false;
		if (stoi(a) > stoi(b))
			return true;
	}
	return true;
}

string division(string dividend, string divisor) {
	if (divisor == "0")
		throw std::invalid_argument("Error: Division by 0.");
	if (dividend == "0")
		return "0";
	string quotient = ""; // result
	string factorTimes = "0";
	string dividendParse = "";
	bool negFound = false;
	if (dividend.find("-") != string::npos && divisor.find("-") != string::npos) // both are negative, result will be positive
	{
		dividend.erase(0,1);
		divisor.erase(0,1);
	}
	else if (dividend.find("-") != string::npos && divisor.find("-") == string::npos) // dividend is negative, result will be negative
	{
		dividend.erase(0,1);
		negFound = true;
	}
	else if (dividend.find("-") == string::npos && divisor.find("-") != string::npos)
	{
		divisor.erase(0,1);
		negFound = true;
	}
	size_t origLength = dividend.length();
	for (size_t i = 0; i < origLength; i++)
	{
		dividendParse.push_back(dividend.at(i)); // essentially dragging down the next number
		//cout << "dividendParse: " << dividendParse << endl;
		factorTimes = numTimes(divisor,dividendParse); // how many times divisor goes into that part of the dividend
		//cout << "numTimes: " << factorTimes << endl;
		//cout << "divisor * numTimes: " << multiply(divisor,factorTimes) << endl;
		if (factorTimes == "0") // not factorable
		{
			quotient.append("0");
			continue;
		}
		quotient.append(factorTimes);
		dividendParse = subtract(dividendParse,multiply(divisor,factorTimes));
		//cout << "dividendParse after subtract: " << dividendParse << endl << endl;
		if (dividendParse == "0")
		{
			dividendParse = ""; // resets dividendParse
		}
	}
	if (negFound)
		quotient.insert(0,"-");
	return trim_leading_zeros(quotient);
}

string modulus(string dividend, string divisor) {
	return subtract(dividend, multiply(division(dividend, divisor), divisor));
};
