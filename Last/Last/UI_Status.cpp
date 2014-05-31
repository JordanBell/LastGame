#include "UI_Status.h"
#include "Tools.h"
#include "Config.h"
#include "ToolKit.h"

UI_Status* UI_Fatigue	 = nullptr;
UI_Status* UI_Loneliness = nullptr;
UI_Status* UI_Insanity   = nullptr;
UI_Status* UI_Fear		 = nullptr;

UI_Status::UI_Status(Status* status, const Coordinates& clipIndex) 
	: Entity( ComputePosition(clipIndex), 
			  Dimensions(), 
			  SSID_STATUS, 
			  UI_STATUS_FRMT, 
			  &ComputeClip(clipIndex)),
	m_status(status) {}

SDL_Rect UI_Status::ComputeClip(const Coordinates& clipIndex)
{
	// Determine the clip from the clip index
	Dimensions clipSize;
	Coordinates clipStart;

	clipSize = GetLogicalSize() / 2;
	clipStart = Coordinates(clipSize.x*clipIndex.x, clipSize.y*clipIndex.y);

	return RectFromXY(clipStart, clipSize);
}

Coordinates UI_Status::ComputePosition(const Coordinates& clipIndex)
{
	// Determine the position from the clip index
	Coordinates r_pos;
	SDL_Rect clip = ComputeClip(clipIndex);

	r_pos = r_pos = Coordinates(clip.x, clip.y);

	return r_pos;
}

void UI_Status::E_Update(int delta)
{
	// Update output based on m_status values
}

