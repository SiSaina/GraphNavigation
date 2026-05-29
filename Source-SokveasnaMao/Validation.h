#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <functional>
#include <algorithm>
using namespace std;
class Validation
{
public:
	static int ValidateIntInput(string prompt, int min, int max);
	static string ValidateStringInput(string prompt, int min, int max);
	static bool ValidateFilePath(const string& path);
};

