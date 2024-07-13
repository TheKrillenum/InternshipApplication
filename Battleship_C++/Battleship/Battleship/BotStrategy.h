#pragma once
#include "Model.h"
#include "Coordinate.h"
#include "Tile.h"

class BotStrategy
{
public:
	//Public functions
	BotStrategy(class Model* model);
	virtual void Shoot(coordinate& coord) = 0;

	// Public Variables
	class Model* m;
	coordinate* target;
};


class EasyStrategy : public BotStrategy
{
public:
	EasyStrategy(class Model* m) : BotStrategy(m){};
	void Shoot(coordinate& coord);
};


class MediumHardStrategy : public BotStrategy
{
private:
	bool NextShot(coordinate &coord);

public:
	MediumHardStrategy(class Model* m) : BotStrategy(m) { target = nullptr; };
	void Shoot(coordinate& coord);
};