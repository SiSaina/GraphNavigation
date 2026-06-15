/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : Validation.h

Description:
	Provides utility functions for validating user input and file paths
***************************************************************************/

#pragma once
#include <iostream>
#include <string>
using namespace std;

/*
============================================================
PathFinder Class
============================================================
Purpose:
	- Provide reusable input validation functions for console-based user interaction

Used for:
	- validate int, string, within a specified range
	- checking if a file path exists and accessible
Note:
	- All function are static
	- can be called without creating a validation object
============================================================
*/
class Validation
{
public:
	/*
	============================================================
	Purpose:
		- prompts the user for an interger and validate int
	Parameters:
		- prompt: message display to the user
		- min: minimun accepted value
		- max: maximun accepted value
	Returns: VALID interger entered by user, ERROR otherwise
	============================================================
	*/
	static int ValidateIntInput(string prompt, int min, int max);

	/*
	============================================================
	Purpose:
		- prompts the user for an string and validate string
	Parameters:
		- prompt: message display to the user
		- min: minimun allowed string length
		- max: maximun allowed string length
	Returns: VALID string entered by user, ERROR otherwise
	============================================================
	*/
	static string ValidateStringInput(string prompt, int min, int max);

	/*
	============================================================
	Purpose:
		- Check if file path is valid
	Parameters:
		- path: file path to validate
	Returns: TRUE if valid, FALSE otherwise
	Rule:
		- path cannot be empty
		- path must contain a file extension
		- file extension must be ".txt" (case-insensitive)
	============================================================
	*/
	static bool ValidateFilePath(const string& path);
};
