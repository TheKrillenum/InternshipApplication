#pragma once
#include "BoatManager.h"
#include "PlayerInfo.h"
#include <string>

using namespace std;

class Tile
{
public:
	// PUBLIC FUNCTION -------------------
	Tile();
	virtual int SpecialEffect(PlayerInfo* shooter);

	// Getters and Setters
	bool GetHit();
	void SetHit(bool shot);
	bool GetSpecialTile();
	struct Boat* GetBoat();
	void SetBoat(struct Boat* newBoat);
	string GetTileType();

protected:
	// Protected variables
	bool hit;
	struct Boat* boat;
	bool specialTile = false;
	string tileType;
};

class AngelTile : public Tile
{
public:
	// Public function
	AngelTile(class BoatManager* boatManager) : Tile() { specialTile = true;  tileType = "Angel";};
	int SpecialEffect(PlayerInfo* shooter);
};

class PowerTile : public Tile
{
public:
	PowerTile() : Tile() { specialTile = true; tileType = "Power";}
	int SpecialEffect(PlayerInfo* shooter);
};

class ExplosiveTile : public Tile
{
public:
	ExplosiveTile() : Tile() { specialTile = true; tileType = "Explosive"; }
	int SpecialEffect(PlayerInfo* shooter);
};

class HistoryTile 
{
public:
	HistoryTile();
	bool GetHit();
	bool GetTouch();
	void SetHit(bool b);
	void SetTouch(bool b);
	
private:
	bool hit;
	bool touch;
};