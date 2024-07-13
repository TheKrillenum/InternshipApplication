#include "PlayerInfo.h"
#include <iostream>

PlayerInfo::PlayerInfo(bool isBot)
{
	bot = isBot;
	PowerAquired = 0;
	RemainingBoats = 5;
}

int PlayerInfo::GetRemainingBoats()
{
	return RemainingBoats;
}

void PlayerInfo::IncrementRemainingBoats()
{
	if (RemainingBoats < 6) {
		RemainingBoats++;
	}
	else {
		// This error message should never appear ingame (made just in case for debugging)
		std::cout << "ERROR: Max boat already obtained." << std::endl;
		std::cin.get();
	}
}

void PlayerInfo::ReduceRemainingBoats()
{
	if (RemainingBoats > 0) {
		RemainingBoats--;
	}
	else {
		// This error message should never appear ingame (made just in case for debugging)
		std::cout << "ERROR: Minimum boat already obtained." << std::endl;
		std::cin.get();
	}
}

int PlayerInfo::GetPoweAquired()
{
	return PowerAquired;
}

void PlayerInfo::IncrementPowerAquired()
{
	
	if (PowerAquired < 2) {
		PowerAquired++;
	}
	else {
		// This error message should never appear ingame (made just in case for debugging)
		std::cout << "ERROR: Max power already obtained." << std::endl;
		std::cin.get();
	}
}

bool PlayerInfo::isBot()
{
	return bot;
}