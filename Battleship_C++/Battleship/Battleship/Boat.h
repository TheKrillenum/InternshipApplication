#pragma once
#include "PlayerInfo.h"
#include "Coordinate.h"

struct Boat
{
	int length;
	coordinate origin;
	bool dirRight;
	// dirRight indicate in which direction the boat is pointing to from the origin. If true, the boat starts at the 
	// origin and proceeds toward the right side. If false, the boat starts at the origin and proceeds downwards.
	bool intact;
	bool destroyed;
	class PlayerInfo* owner;
};