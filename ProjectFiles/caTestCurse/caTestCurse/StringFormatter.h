#pragma once
#include <string>

class StringFormatter
{
public:
	std::string text;
	static void formatString(std::string *text, int lineNumber);
};

