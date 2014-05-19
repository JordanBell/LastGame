#pragma once

struct EntityFormat
{
	EntityFormat(bool _animated,
				 bool _updates,
				 bool _travels,
				 bool _interactable,
				 bool _tangible,
				 bool _illuminates,
				 bool _gridIndependent);
	~EntityFormat(void) {}

	// Array of format booleans
	bool properties[7];

	// Array access convenience overload
	bool operator[](int index);

private:
	// Format information
	bool animated, 
		 updates,
		 travels,
		 interactable,
		 tangible,
		 illuminates,
		 gridOndependent;
};