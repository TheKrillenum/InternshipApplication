#pragma once
#include "Tile.h"

struct DoubleArray
{
	// Array where the player places his boats/special tiles
	class Tile* arr[10][10];

	// Array where the player sees the history of his shots
	class HistoryTile* hist[10][10];
};