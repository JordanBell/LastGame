#pragma once
#include "SDL.h"

struct EntityFormat
{
	EntityFormat(const Uint8 code) : m_formatCode(code) {}
	~EntityFormat(void) {}

	// Array access convenience overload
	bool operator[](int index);

private:
	// Format information
	Uint8 m_formatCode;
};