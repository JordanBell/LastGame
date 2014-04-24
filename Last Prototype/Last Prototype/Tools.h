#pragma once
#include <String>
#include "Config.h"

// Direction enumeration
enum E_Direction{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// An X and Y pairing
struct XY { 
	float x, y; 
	XY(float _x, float _y) : x(_x), y(_y) {}

	// Finding the manhatten distances between the two (or other pythagorean theorum contexts)
	float manhatten() { return sqrt(x*x + y*y); }

	// Alter the values based on a direction
	void addDirection(E_Direction d) { addDirection(d, 1); }
	void addDirection(E_Direction d, float f)
	{
		y -=    (d == UP) * f;
		y +=  (d == DOWN) * f;
		x -=  (d == LEFT) * f;
		x += (d == RIGHT) * f;
	}

	/// +, -, *, /
	// Other XYs
	XY operator+(XY xy) {
		XY result = *this;
		result += xy;

		return result;
	}

	XY operator-(XY xy) {
		XY result = *this;
		result -= xy;

		return result;
	}

	XY operator/(XY xy) {
		XY result = *this;
		result /= xy;

		return result;
	}

	XY operator*(XY xy) {
		XY result = *this;
		result *= xy;

		return result;
	}

	// ints
	XY operator+(int i) {
		XY result = *this;
		result += i;

		return result;
	}

	XY operator-(int i) {
		XY result = *this;
		result -= i;

		return result;
	}

	XY operator*(int i) {
		XY result = *this;
		result *= i;

		return result;
	}

	XY operator/(int i) {
		XY result = *this;
		result /= i;

		return result;
	}


	/// +=, -=, *=, /=
	// Other XYs
	XY operator+=(XY xy) {
		x += xy.x;
		y += xy.y;

		return *this;
	}

	XY operator-=(XY xy) {
		x -= xy.x;
		y -= xy.y;

		return *this;
	}

	XY operator/=(XY xy) {
		x /= xy.x;
		y /= xy.y;

		return *this;
	}

	XY operator*=(XY xy) {
		x *= xy.x;
		y *= xy.y;

		return *this;
	}
	
	// ints
	XY operator+=(int i) {
		x += i;
		y += i;

		return *this;
	}

	XY operator-=(int i) {
		x -= i;
		y -= i;

		return *this;
	}

	XY operator*=(int i) {
		x *= i;
		y *= i;

		return *this;
	}

	XY operator/=(int i) {
		x /= i;
		y /= i;

		return *this;
	}

	// ==
	bool operator==(XY xy) {
		return ((x == xy.x) &&
				(y == xy.y));
	}
};

// A bunch of directions
template <class E>
struct Directions {
	E top, bottom, left, right;

	Directions(E t, E b, E l, E r) 
		     : top(t), bottom(b), left(l), right(r) {} 
};

template <>
struct Directions<float> {
	float top, bottom, left, right;

	Directions(float t, float b, float l, float r) 
		     : top(t), bottom(b), left(l), right(r) {} 

	// Specialised Constructor using XY values
	Directions(XY scalarValues) {
		Directions(-scalarValues.y,
					scalarValues.y,
				   -scalarValues.x,
					scalarValues.x);
	} 
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