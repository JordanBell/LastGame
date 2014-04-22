#pragma once
#include <String>
// An X and Y pairing
struct XY { 
	float x, y; 
	XY(float _x, float _y) : x(_x), y(_y) {}
};

// A bunch of directions
template <class E>
struct Directions {
	E top, bottom, left, right;

	Directions(E t, E b, E l, E r) 
		     : top(t), bottom(b), left(l), right(r) {} 
};

// Bool directions specialisation, with equality overloads
template <>
struct Directions<bool> {
	bool top, bottom, left, right;

	Directions(bool t, bool b, bool l, bool r) 
		   : top(t), bottom(b), left(l), right(r) {} 

	// Overload equality and inequality operators
	bool operator==(bool b) {
		return ((top	== b) &&
				(bottom == b) &&
				(left	== b) &&
				(right	== b));
	}
	
	bool operator!=(bool b) {
		return ((top	!= b) &&
				(bottom != b) &&
				(left	!= b) &&
				(right	!= b));
	}
};