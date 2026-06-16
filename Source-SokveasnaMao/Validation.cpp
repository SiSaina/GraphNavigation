/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : Validation.cpp

Description:
    Implementation of utility functions for validating user input and file paths
***************************************************************************/

#include "Validation.h"

/*==================Validate Integer Input========================*/
int Validation::ValidateIntInput(string prompt, int minimumValue, int maximunValue)
{
    int value = 0;

    // keep prompt until a valid int within range is entered
    while (true) {
        cout << prompt;

        // check for non-numeric input
        if (!(cin >> value))
        {
            cout << "Invalid number. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // check value fall within allowed range
        if (value < minimumValue || value > maximunValue)
        {
            cout << "Input must be between " << minimumValue << " and " << maximunValue << endl;
            continue;
        }

        // remove any remaining characters from the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

/*==================Validate String Input========================*/
string Validation::ValidateStringInput(string prompt, int minimumLength, int maximumLength)
{
    string value;

    // keep prompt until a valid int within range is entered
    while (true) {
        cout << prompt;
        getline(cin, value);

        // reject empty input
        if (value.empty())
        {
            cout << "Input cannot be empty. Try again.\n";
            continue;
        }

        // check length fall within range
        if (value.length() < minimumLength || value.length() > maximumLength) {
            cout << "Input length must be between " << minimumLength << " and " << maximumLength << " characters";
            continue;
        }

        //// convert input to lowercase
        //transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return tolower(c); });
        return value;
    }
}

/*==================Validate File Path========================*/
bool Validation::ValidateFilePath(const string& filePath)
{
    // reject empty file path
    if (filePath.empty())
    {
        cout << "File path cannot be empty. Try again." << endl;
        return false;
    }

    // locate the file extension separator
    size_t invalidChars = filePath.find_last_of('.');

    // make sure file extension exists
    if (invalidChars == string::npos) {
        cout << "File path must contain a file extension. Try again." << endl;
        return false;
    }

    // extract the file extension
    string fileExtension = filePath.substr(invalidChars);

    // convert extension to lowercase for case-insensitive comparison
    for (char& c : fileExtension) {
        c = static_cast<char>(tolower(c));
    }

    // accept only .txt files
    return fileExtension == ".txt";
}
