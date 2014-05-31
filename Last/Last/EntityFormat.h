#pragma once
#include "SDL.h"

/*
A bitwise wrapper that overloads the [] operator to return the contents of its format.
See config.h for corresponding index properties.
*/
struct EntityFormat
{
	EntityFormat(const Uint8 code) : m_formatCode(code) {}
	~EntityFormat(void) {}

	// Array-like convenience overload
	bool operator[](int index);

private:
	// Format information
	Uint8 m_formatCode;
};