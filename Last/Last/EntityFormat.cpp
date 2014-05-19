#pragma once

#include "EntityFormat.h"
#include "Tools.h"

EntityFormat::EntityFormat(bool _animated,
						   bool _updates,
						   bool _travels,
						   bool _interactable,
						   bool _tangible,
						   bool _illuminates,
						   bool _gridIndependent)
{
	properties[ANIMATED]		= _animated;
	properties[UPDATES]			= _updates;
	properties[TRAVELS]			= _travels;
	properties[INTERACTABLE]	= _interactable;
	properties[TANGIBLE]		= _tangible;
	properties[ILLUMINATES]		= _illuminates;
	properties[GRID_INDEPENDENT]= _gridIndependent;
}

bool EntityFormat::operator[](int index)
{
	return properties[index];
}