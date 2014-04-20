#pragma once

// An X and Y pairing
struct XY { 
	float x, y; 
	XY(float _x, float _y) : x(_x), y(_y) {}
};

// A bunch of diretions
template <class E>
struct Directions {
	E top, bottom, left, right;

	//Directions(void) { Directions(0, 0, 0, 0); }
	Directions(E t, E b, E l, E r) 
		     : top(t), bottom(b), left(l), right(r) {} 
};