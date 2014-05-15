#pragma once
<<<<<<< HEAD
#include <cmath>
#include <iostream>

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
	XY(const float val) : x(val), y(val) {}
	XY(const float _x, const float _y) : x(_x), y(_y) {}

	// Finding the manhatten distances between the two (or other pythagorean theorum contexts)
	const float manhatten(void) const { return sqrt(x*x + y*y); }

	// Alter the values based on a direction
	void addDirection(const E_Direction d) { addDirection(d, 1); }
	void addDirection(const E_Direction d, const float f)
	{
		y -=    (d == UP) * f;
		y +=  (d == DOWN) * f;
		x -=  (d == LEFT) * f;
		x += (d == RIGHT) * f;
	}

	// Round the values to their integer values towards 0
	void RoundToInt(void)
	{
		x = (int) x;
		y = (int) y;
	}

	void RoundToNearest(void)
	{
		// Add 0.5 to exploit the round-to-zero function of int conversion
		x += 0.5;
		y += 0.5;
		RoundToInt();
	}

	/// +, -, *, /
	// Other XYs
	const XY operator+(const XY& xy) const {
		XY result = *this;
		result += xy;

		return result;
	}

	const XY operator-(const XY& xy) const {
		XY result = *this;
		result -= xy;

		return result;
	}

	const XY operator/(const XY& xy) const {
		XY result = *this;
		result /= xy;

		return result;
	}

	const XY operator*(const XY& xy) const {
		XY result = *this;
		result *= xy;

		return result;
	}

	// floats
	const XY operator+(const float i) const {
		XY result = *this;
		result += i;

		return result;
	}

	const XY operator-(const float i) const {
		XY result = *this;
		result -= i;

		return result;
	}

	const XY operator*(const float i) const {
		XY result = *this;
		result *= i;

		return result;
	}

	const XY operator/(const float i) const {
		XY result = *this;
		result /= i;

		return result;
	}

	// ints
	const XY operator+(const int i) const {
		XY result = *this;
		result += i;

		return result;
	}

	const XY operator-(const int i) const {
		XY result = *this;
		result -= i;

		return result;
	}

	const XY operator*(const int i) const {
		XY result = *this;
		result *= i;

		return result;
	}

	const XY operator/(const int i) const {
		XY result = *this;
		result /= i;

		return result;
	}


	/// +=, -=, *=, /=
	// Other XYs
	const XY operator+=(const XY& xy) {
		x += xy.x;
		y += xy.y;

		return *this;
	}

	const XY operator-=(const XY& xy) {
		x -= xy.x;
		y -= xy.y;

		return *this;
	}

	const XY operator/=(const XY& xy) {
		x /= xy.x;
		y /= xy.y;

		return *this;
	}

	const XY operator*=(const XY& xy) {
		x *= xy.x;
		y *= xy.y;

		return *this;
	}
	
	// floats
	const XY operator+=(const float i) {
		x += i;
		y += i;

		return *this;
	}

	const XY operator-=(const float i) {
		x -= i;
		y -= i;

		return *this;
	}

	const XY operator*=(const float i) {
		x *= i;
		y *= i;

		return *this;
	}

	const XY operator/=(const float i) {
		x /= i;
		y /= i;

		return *this;
	}
	
	// ints
	const XY operator+=(const int i) {
		x += i;
		y += i;

		return *this;
	}

	const XY operator-=(const int i) {
		x -= i;
		y -= i;

		return *this;
	}

	const XY operator*=(const int i) {
		x *= i;
		y *= i;

		return *this;
	}

	const XY operator/=(const int i) {
		x = (int)x / i;
		y = (int)y / i;

		return *this;
	}

	// <, >
	const bool operator<(const XY& xy) const {
		return ((x < xy.x) &&
				(y < xy.y));
	}

	const bool operator>(const XY& xy) const {
		return ((x > xy.x) &&
				(y > xy.y));
	}

	// ==
	const bool operator==(const XY& xy) const {
		return ((x == xy.x) &&
				(y == xy.y));
	}
=======
#include <String>
// An X and Y pairing
struct XY { 
	float x, y; 
	XY(float _x, float _y) : x(_x), y(_y) {}
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
};

// A bunch of directions
template <class E>
struct Directions {
	E top, bottom, left, right;

	Directions(const E& t, const E& b, const E& l, const E& r) 
		     : top(t), bottom(b), left(l), right(r) {}
};

<<<<<<< HEAD
template <>
struct Directions<float> {
	float top, bottom, left, right;

	Directions(const float t, const float b, const float l, const float r) 
		     : top(t), bottom(b), left(l), right(r) 
	{
		top		= t;
		bottom	= b;
		left	= l;
		right	= r;
	} 

	// Specialised Constructor using XY values
	Directions(const XY& base, const XY& scalarDifference) {
		top	   = base.y - scalarDifference.y;
		bottom = base.y + scalarDifference.y;
		left   = base.x - scalarDifference.x;
		right  = base.x + scalarDifference.x;
	} 
};

=======
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
// Bool directions specialisation, with equality overloads
template <>
struct Directions<bool> {
	bool top, bottom, left, right;

	Directions(const bool t, const bool b, const bool l, const bool r) 
		   : top(t), bottom(b), left(l), right(r) {} 

	// Overload equality and inequality operators
	const bool operator==(const bool b) const {
		return ((top	== b) &&
				(bottom == b) &&
				(left	== b) &&
				(right	== b));
	}
	
	const bool operator!=(const bool b) const {
		return ((top	!= b) &&
				(bottom != b) &&
				(left	!= b) &&
				(right	!= b));
	}

	void print(const bool invert = false, const char* title = "Directions are:")
	{
		printf("%s\n", title);
		printf("\tTop: %s\n", (invert? !top : top) ? "Yes" : "No");
		printf("\tBottom: %s\n", (invert? !bottom : bottom) ? "Yes" : "No");
		printf("\tLeft: %s\n", (invert? !left : left) ? "Yes" : "No");
		printf("\tRight: %s\n", (invert? !right : right) ? "Yes" : "No");
	}
};