#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "./string_calculator.h"
#include "./calculator.h"

using std::cout, std::endl, std::string, std::stack, std::istringstream;

int precedence (char c) {
    if (c == '/')
        return 4;
    else if (c == '*')
        return 3;
    else if (c == '+' || c == '-')
        return 2;
    else
        return 1;
}

bool isOperator(char c) {
    if (c == '/' || c == '*' || c == '+' || c == '-')
        return true;
    return false;
}

bool validate(string s) {
    if (s == "()")
        return false;
    stack<char> parenStack;
    bool hasDigit = false;
    int numDecimalPoints = 0;
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s.at(i) == '(')
            parenStack.push(s.at(i));
        else if (s.at(i) == ')')
        {
            if (parenStack.empty())
                return false;
            parenStack.pop();
        }
        else if (!isOperator(s.at(i)) && s.at(i) != ')' && s.at(i) != '(' && !isdigit(s.at(i)) && s.at(i) != '.')
        {
            numDecimalPoints = 0;
            return false;
        }
        else if (s.at(i) == '.')
        {
            if (numDecimalPoints >= 1)
            {
                numDecimalPoints = 0;
                return false;
            }
            numDecimalPoints++;
        }
        else if (isdigit(s.at(i)))
        {
            hasDigit = true;
            while (i < s.length() && (isdigit(s.at(i)) || s.at(i) == '.'))
            {
                if (s.at(i) == '.')
                {
                    if (numDecimalPoints >= 1)
                    {
                        numDecimalPoints = 0;
                        return false;
                    }
                    numDecimalPoints++;
                }
                i++;
            }
            i--;
            numDecimalPoints = 0;
        }
    }
    if (!parenStack.empty())
        return false;
    return hasDigit;
}


string postfix(string s) {
    stack<char> theStack;
    string answer;
    char c;
    size_t sentinel = s.length();
    size_t i = 0;
    while (i < sentinel)
    {
        c = s.at(i);
        if (c == '(')
        {
            theStack.push(c);
            i++;
        }
        else if (c == ')')
        {
            while (theStack.top() != '(')
            {
                answer.push_back(theStack.top());
                answer.push_back(' ');
                theStack.pop();
                if (theStack.empty()) // fix error in case of mismatched parentheses
                    return "error: mismatched parentheses";
            }
            theStack.pop();
            i++;
        }
        else if (!isOperator(c) ||
            (c == '-' && i != 0 && s.at(i - 1) == '(') ||
            (i == 0 && c == '-') ||
            (c == '-' && i != 0 && isOperator(s.at(i - 1))))
        {
            answer.push_back(c);
            i++;
            while (i < sentinel && s.at(i) != ')' && !isOperator(s.at(i)))
            {
                answer.push_back(s.at(i));
                i++;
            }
            answer.push_back(' ');
        }
        else
        {
            while (!theStack.empty() && precedence(c) <= precedence(theStack.top()))
            {
                answer.push_back(theStack.top());
                answer.push_back(' ');
                theStack.pop();
            }
            theStack.push(c);
            i++;
        }
    }
    while (!theStack.empty())
    {
        if (theStack.top() == '(') // fix error in case of mismatched parentheses
            return "error: mismatched parentheses";
        answer.push_back(theStack.top());
        answer.push_back(' ');
        theStack.pop();
    }
    return answer;
}

string standardize (string s) // makes it so each infix has only 1 space in between
{
    // first, if it has spaces, make it not have spaces
    string noSpaceResult = "";
    for (size_t i = 0; i < s.length(); i++)
    {
        if (s.at(i) != ' ')
            noSpaceResult.push_back(s.at(i));
    }
    return noSpaceResult;
}

#include <stack>
#include <sstream>

double calculate(std::string s) {
    std::stack<double> operands;
    std::istringstream iss(s);
    std::string token;
    while (iss >> token) {
        if (isOperator(token[0])) {
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            switch (token[0]) {
            case '+': operands.push(operand1 + operand2); break;
            case '-': operands.push(operand1 - operand2); break;
            case '*': operands.push(operand1 * operand2); break;
            case '/': operands.push(operand1 / operand2); break;
            }
        }
        double calculate(std::string s); {
            std::stack<double> operands;
            std::istringstream iss(s);
            std::string token;
            while (iss >> token) {
                if (isOperator(token[0])) {
                    double operand2 = operands.top();
                    operands.pop();
                    double operand1 = operands.top();
                    operands.pop();
                    switch (token[0]) {
                    case '+': operands.push(operand1 + operand2); break;
                    case '-': operands.push(operand1 - operand2); break;
                    case '*': operands.push(operand1 * operand2); break;
                    case '/': operands.push(operand1 / operand2); break;
                    }
                }
                else {
                    // Check if the token contains a decimal point
                    if (token.find('.') != std::string::npos) {
                        // Token contains a decimal point, so use stod to convert directly to double
                        operands.push(std::stod(token));
                    }
                    else {
                        // Token does not contain a decimal point, so convert to int first and then to double
                        operands.push(static_cast<double>(std::stoi(token)));
                    }
                }
            }
            if (operands.size() != 1) {
                throw std::invalid_argument("Invalid expression aaaaaaaaa");
            }
            return operands.top();
        }
    }
    if (operands.size() != 1) {
        throw std::invalid_argument("Invalid expression Multiple operands");
    }
    return operands.top();
}

