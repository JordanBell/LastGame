#pragma once
#include <exception>
#include <string>
using namespace std;

class ModuleMisuseException : public exception
{
	string m_errorMessage;

public:
	ModuleMisuseException(string errorMessage) 
		: m_errorMessage(errorMessage) {}

	virtual const char* what() const throw()
	{
		return ("Module Misuse Exception: " + m_errorMessage).c_str();
	}
};

