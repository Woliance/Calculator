#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"
#include "./calculator.h"

using std::cout, std::endl, std::cin, std::string;

int main() {
    string fullExpression;
    string line;
    string answer;
	while (true)
    {
        getline(cin, fullExpression);
        if (fullExpression == "Q" || fullExpression == "q" || fullExpression == "Quit" || fullExpression == "quit")
            break;
        else if (fullExpression == "")
            continue;
        else
        {
            fullExpression = standardize(fullExpression);
            if (!validate(fullExpression))
            {
                cout << "Invalid expression. Try again: \n>>  ";
                continue;
            }
            fullExpression = postfix(fullExpression);
            try 
            {
                answer = calculate(fullExpression);
            }
            catch (const std::exception& error) 
            {
                cout << error.what() << " Try again: \n>>  ";
                continue;
            }
            cout << answer << endl;
        }
    }
	cout << endl;
	cout << "farvel!" << endl;
	cout << endl;
}

