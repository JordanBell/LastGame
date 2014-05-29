#pragma once

#include "EntityFormat.h"
#include "Tools.h"

bool EntityFormat::operator[](int index)
{
	return (m_formatCode>>index & 1);

	/*
	This method checks if a given bit of the formatCode has been OR'd into it.

	1. Shift the bits "index" times to the right, truncating any bits right of the target.
	2. Bitwise AND, with the number 1, checks the value of the right-most bit
	3. If the bit at "index" position in the formatCode was 1, the statement is true.
	If not, the bitwise AND computes to 0, meaning false, which is returned.
	*/
}