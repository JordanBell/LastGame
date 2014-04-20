#pragma once
class HouseGenerator
{
public:
	HouseGenerator(void);
	~HouseGenerator(void) {}

	void run(void);
private:
	/*enum HouseSize
	{
		SMALL, MEDIUM, LARGE
	};*/

	struct HouseSize
	{
		HouseSize(int _w, int _h, int _rooms) : w(_w), h(_h), numRooms(_rooms) {}

		int w, h;
		int numRooms;
	};

	HouseSize SMALL, MEDIUM, LARGE;
	HouseSize ComputeRandomSize(void);
};

