#pragma once
#include "Boat.h"

class PlayerInfo
{
public:
	// PUBLIC FUNCTION --------------
	PlayerInfo(bool isBot);

	// Getters and Setters
	int GetRemainingBoats();
	void IncrementRemainingBoats();
	void ReduceRemainingBoats();
	int GetPoweAquired();
	void IncrementPowerAquired();
	bool isBot();

private:
	// PRIATE VARIABLES
	int RemainingBoats;
	int PowerAquired;
	bool bot;
};