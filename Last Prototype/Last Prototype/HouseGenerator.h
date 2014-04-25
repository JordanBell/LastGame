#pragma once
class HouseGenerator
{
public:
	HouseGenerator(void) : SMALL(HouseSize(7, 7, 1)), MEDIUM(HouseSize(10, 10, 2)), LARGE(HouseSize(13, 13, 3)) {}
	~HouseGenerator(void) {}

	void run(void);

private:
	struct HouseSize
	{
		HouseSize(int _w, int _h, int _rooms) : w(_w), h(_h), numRooms(_rooms) {}

		int w, h;
		int numRooms;
	};

	HouseSize SMALL, MEDIUM, LARGE;
	HouseSize ComputeRandomSize(void);
};

