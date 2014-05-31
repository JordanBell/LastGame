#pragma once
#include <exception>
#include <string>
using namespace std;

class AnimationIteratorException : public exception
{
	string m_errorMessage;

public:
	AnimationIteratorException(string errorMessage) 
		: m_errorMessage(errorMessage) {}

	virtual const char* what() const throw()
	{
		return ("Animation Iterator Exception: " + m_errorMessage).c_str();
	}
};

