#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "./string_calculator.h"
#include "./calculator.h"

using std::cout, std::endl, std::cin, std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"Q\",\"q\"\"Quit\", or \"quit\" or ctrl+d to exit" << endl;
    string userInput;
    string fullExpression;
    string line;
    string answer;
	cout << ">>  ";
    while (true)
    {
        getline(cin, userInput); // Get user input and store it in userInput variable
        if (userInput == "Q" || userInput == "q" || userInput == "Quit" || userInput == "quit")
            break;
        else if (userInput == "")
            continue;
        else
        {
            fullExpression = standardize(userInput);
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
            std::cout << std::left << std::setw(5) << std::setfill(' ') << answer << " = " << userInput << std::endl;
        }
    }
	cout << endl;
	cout << endl;
}

