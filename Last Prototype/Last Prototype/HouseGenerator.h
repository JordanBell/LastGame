#pragma once
class HouseGenerator
{
public:
<<<<<<< HEAD
	// Contains information about the dimensions and number of rooms in the house.
	struct HouseSize {
		HouseSize(XY _dimensions, int _rooms) : dimensions(_dimensions), numRooms(_rooms) {}
=======
	HouseGenerator(void) : SMALL(HouseSize(7, 7, 1)), MEDIUM(HouseSize(10, 10, 2)), LARGE(HouseSize(13, 13, 3)) {}
	~HouseGenerator(void) {}

	void run(void);

private:
	struct HouseSize
	{
		HouseSize(int _w, int _h, int _rooms) : w(_w), h(_h), numRooms(_rooms) {}
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete

		int w, h;
		int numRooms;
	};

<<<<<<< HEAD
	// Generate the house buildings
	static void generate(void);

private:
	// Get a random size from the above house sizes
	static const HouseSize ComputeRandomSize(void);
=======
	HouseSize SMALL, MEDIUM, LARGE;
	HouseSize ComputeRandomSize(void);
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
};

