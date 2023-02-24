#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "./string_calculator.h"
#include "./calculator.h"

using std::cout, std::endl, std::string, std::stack, std::istringstream;

int precedence(char c) {
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
    }
    if (!parenStack.empty())
        return false;
    for (size_t i = 0; i < s.length(); i++)
    {
        if (!isOperator(s.at(i)) && s.at(i) != ')' && s.at(i) != '(' && !isdigit(s.at(i)) && s.at(i) != '.')
            return false;
    }
    return true;
}

string postfix(string s) { // Implement error checking for only (
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
            if (theStack.empty())
                throw std::invalid_argument("Invalid expression: Unbalanced parentheses");
            while (theStack.top() != '(')
            {
                answer.push_back(theStack.top());
                answer.push_back(' ');
                theStack.pop();
                if (theStack.empty())
                    throw std::invalid_argument("Invalid expression: Unbalanced parentheses");
            }
            theStack.pop();
            i++;
        }
        else if (!isOperator(c) || (c == '-' && i != 0 && s.at(i - 1) == '(') || (i == 0 && c == '-') || (c == '-' && i != 0 && isOperator(s.at(i - 1))))
        {
            answer.push_back(s.at(i));
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
        if (theStack.top() == '(')
            throw std::invalid_argument("Invalid expression: Unbalanced parentheses");
        answer.push_back(theStack.top());
        answer.push_back(' ');
        theStack.pop();
    }
    return answer;
}

string standardize(string s) {
    // Replace multiple spaces with a single space
    size_t i = 0;
    while (i < s.length()) {
        if (s[i] == ' ') {
            size_t j = i + 1;
            while (j < s.length() && s[j] == ' ') {
                j++;
            }
            s.erase(i, j - i - 1);
        }
        i++;
    }
    return s;
}

string calculate(string s) {
    string result = "";
    string lhs;
    string rhs;
    string parse;
    istringstream iss(s);
    stack<string> theStack;
    while (iss >> parse) {
        if (parse.length() != 1 || !isOperator(parse[0])) { // is operand
            theStack.push(parse);
        }
        else if (isOperator(parse[0]) && parse.length() == 1) { // is one of the 5 operators
            switch (parse[0]) {
            case '+':
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                rhs = theStack.top();
                theStack.pop();
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                lhs = theStack.top();
                theStack.pop();
                theStack.push(add(lhs, rhs));
                break;
            case '-':
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                rhs = theStack.top();
                theStack.pop();
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                lhs = theStack.top();
                theStack.pop();
                theStack.push(subtract(lhs, rhs));
                break;
            case '*':
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                rhs = theStack.top();
                theStack.pop();
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                lhs = theStack.top();
                theStack.pop();
                theStack.push(multiply(lhs, rhs));
                break;
            case '/':
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                rhs = theStack.top();
                theStack.pop();
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                lhs = theStack.top();
                theStack.pop();
                theStack.push(division(lhs, rhs));
                break;
            case '%':
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                rhs = theStack.top();
                theStack.pop();
                if (theStack.empty()) {
                    throw std::invalid_argument("Invalid expression.");
                }
                lhs = theStack.top();
                theStack.pop();
                theStack.push(modulus(lhs, rhs));
                break;
            default:
                cout << "[ERROR] invalid operator: " << parse[0] << endl;
                break;
            }
        }
    }
    if (theStack.empty()) {
        throw std::invalid_argument("Invalid expression.");
    }
    return theStack.top();
}
