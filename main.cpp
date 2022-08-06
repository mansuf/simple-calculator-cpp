#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <map>

// Source: https://www.codeguru.com/cplusplus/switch-on-strings-in-c/
// Value-Defintions of the different String values
enum OperatorValues {
    OperatorAddition,
    OperatorSubtraction,
    OperatorMultiplication,
    OperatorDivision,
};

// Map to associate the strings with the enum values
static std::map<std::string, OperatorValues> map_operator_values;

// This function must be called in main()
void initialize_map_operators() {
    // Enter operator values
    map_operator_values["*"] = OperatorMultiplication;
    map_operator_values["/"] = OperatorDivision;
    map_operator_values["+"] = OperatorAddition;
    map_operator_values["-"] = OperatorSubtraction;
}

bool is_numbers(std::string c) {
    std::string ARRAY_NUMBERS[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

    for (int i = 0; i < sizeof(ARRAY_NUMBERS) / sizeof(std::string); i++) {
        if (c != ARRAY_NUMBERS[i]) {
            continue;
        }

        return true;
    }

    return false;
}

bool is_operators(std::string c) {
    std::string ARRAY_OPERATORS[] = {"*", "/", "+", "-"};

    for (int i = 0; i < sizeof(ARRAY_OPERATORS) / sizeof(std::string); i++) {
        if (c != ARRAY_OPERATORS[i]) {
            continue;
        }

        return true;
    }

    return false;
}

int convert_integer_from_string(std::string numbers) {
    int result;
    std::stringstream ss;

    ss << numbers;
    ss >> result;
    return result;
}

int main() {
    initialize_map_operators();

    // Create a variable to store input
    std::string input;

    // Begin retrieving input
    std::cout << "Enter a numbers pattern to calculate: ";
    std::getline(std::cin, input);

    std::string first_numbers;
    bool is_first_numbers_empty = true;

    std::string second_numbers;
    bool is_second_numbers_empty = true;

    std::string op;
    std::string c;

    // Begin parsing
    for (int i = 0; i < input.size(); i++) {
        c = input[i];
        if (is_first_numbers_empty) {
            // Ignore whitespace
            if (c == " ") {continue;}

            if (is_operators(c)) {
                // Operator detected
                // Begin to parsing next numbers
                is_first_numbers_empty = false;
                op = c;
            }
            else if (!is_numbers(c)) {
                std::cerr << "Error: Invalid number detected in first numbers = " << c << std::endl;
                return 1;
            }

            first_numbers += c;
        }
        else if (is_second_numbers_empty) {
            // Ignore whitespace
            if (c == " ") {continue;}

            if (is_operators(c)) {
                // Operator in second numbers are not allowed
                // Because this is calculator for first and second numbers
                // numbers calculation more than 1 are not supported
                std::cerr << "Error: Additional operator at the end second numbers are not allowed" << std::endl;
                return 1;
            }
            else if (!is_numbers(c)) {
                std::cerr << "Error: Invalid number detected in second numbers = " << c << std::endl;
                return 1;
            }

            second_numbers += c;
        }
    }

    if (is_first_numbers_empty) {
        std::cerr << "Error: There is no operator" << std::endl;
        return 1;
    }
    else if (is_second_numbers_empty) {
        std::cerr << "Error: There is no second numbers found" << std::endl;
        return 1;
    }

    // String from input is exhausted
    is_second_numbers_empty = true;

    // Begin conversion from string to integer
    int first_numbers_int = convert_integer_from_string(first_numbers);
    int second_numbers_int = convert_integer_from_string(second_numbers);
    double result;

    // Begin calculating
    switch (map_operator_values[op]) {
        case OperatorAddition:
            result = first_numbers_int + second_numbers_int;
            break;
        case OperatorSubtraction:
            result = first_numbers_int - second_numbers_int;
            break;
        case OperatorDivision:
            result = first_numbers_int / second_numbers_int;
            break;
        case OperatorMultiplication:
            result = first_numbers_int * second_numbers_int;
            break;
    }

    // Print the final result
    std::cout << "Result calculation \"" << input << "\" are = " << result << std::endl;
    return 0;
}