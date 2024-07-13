#include "Tile.h"
#include "Boat.h"

int AngelTile::SpecialEffect(PlayerInfo* shooter)
{
	return 3;
}

int PowerTile::SpecialEffect(PlayerInfo* shooter)
{
	shooter->IncrementPowerAquired();
	return 4;
}

int ExplosiveTile::SpecialEffect(PlayerInfo* shooter)
{
	return 2;
}

Tile::Tile()
{
	hit = false;
	boat = nullptr;
	tileType = "Tile";
}

int Tile::SpecialEffect(PlayerInfo* shooter)
{
	return 0;
}

bool Tile::GetHit()
{
	return hit;
}

void Tile::SetHit(bool shot)
{
	hit = shot;
}

bool Tile::GetSpecialTile()
{
	return specialTile;
}

Boat* Tile::GetBoat()
{
	return boat;
}

void Tile::SetBoat(Boat* newBoat)
{
	boat = newBoat;
}

string Tile::GetTileType()
{
	return tileType;
}

HistoryTile::HistoryTile()
{
	hit = false;
	touch = false;
}

bool HistoryTile::GetHit()
{
	return hit;
}

bool HistoryTile::GetTouch()
{
	return touch;
}

void HistoryTile::SetHit(bool b)
{
	hit = b;
}

void HistoryTile::SetTouch(bool b)
{
	touch = b;
}
