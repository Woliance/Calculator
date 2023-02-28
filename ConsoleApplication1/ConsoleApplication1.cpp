#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <regex>
#include <sstream> // add this include for ostringstream
#include "./string_calculator.h"
#include "./calculator.h"

using std::cout, std::endl, std::cin, std::string;

// Function to trim trailing zeros from a string
string trimTrailingZeros(string str)
{
    // Use regex_replace to remove trailing zeros and the decimal point if it's followed by only zeros
    str = std::regex_replace(str, std::regex("(\\.\\d*[1-9])0+($|[^\\d])"), "$1$2");
    return str;
}

int main() {
    cout << "String Calculator" << endl;
    cout << "\"Q\",\"q\"\"Quit\", or \"quit\" or ctrl+d to exit" << endl;
    string userInput;
    string fullExpression;
    string line;
    double answer;
    cout << std::fixed << std::setprecision(6); // Set precision to 6 decimal places
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
                cout << "Invalid expression. Try again: 1234123 \n>>  ";
                continue;
            }
            fullExpression = postfix(fullExpression);
            try
            {
                answer = calculate(fullExpression); // Compute the answer
            }
            catch (const std::exception& error)
            {
                cout << error.what() << " Try again: \n>>  ";
                continue;
            }
            // Convert double answer to string without trailing zeros and trim trailing zeros
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(6) << answer;
            std::string result = ss.str();
            if (result.find('.') != std::string::npos) {
                result.erase(result.find_last_not_of('0') + 1, std::string::npos);
            }
            if (result.back() == '.') {
                result.pop_back();
            }
            std::cout << std::left << std::setw(9) << std::setfill(' ') << result << " = " << userInput << std::endl;

        }
        cout << ">>  ";
    }
    cout << endl;
    cout << endl;
    return 0;
}
