#pragma once
class HouseGenerator
{
public:
	HouseGenerator(void) : SMALL (HouseSize(XY(7, 7), 1)), 
						   MEDIUM(HouseSize(XY(10, 10), 2)), 
						   LARGE (HouseSize(XY(13, 13), 3)) {}

	// Run the House Generation
	void run(void);

private:
	// Contains information about the dimensions and number of rooms in the house.
	struct HouseSize {
		HouseSize(XY _dimensions, int _rooms) : dimensions(_dimensions), numRooms(_rooms) {}

		XY dimensions;
		int numRooms;
	};

	HouseSize SMALL, MEDIUM, LARGE; // The different house sizes

	// Get a random size from the above house sizes
	HouseSize ComputeRandomSize(void);
};

