#pragma once
#include "Model.h"
#include "BotStrategy.h"
#include "2DArray.h"
#include "Tile.h"
#include "Boat.h"
#include "BoatManager.h"
#include "Coordinate.h"

class BotAI
{
public:
	// PUBLIC FUNCTION -------------------
	BotAI(class Model* model, class BoatManager* boatManager);
	void CallShoot(coordinate& coord);
	coordinate BotInputCoord (int max, int min);
	int BotInputInddex(int max, int min);
	DoubleArray GetRandomGrid();
	struct DoubleArray InitArrayOfGrid();

	// Getters and Setters
	class BotStrategy* GetStrategy();
	void setBotStrategy();
	void SetAllArrayOfGrid();

private:
	// PRIATE VARIABLES
	class BotStrategy* strategy;
	class Model* m;
	class BoatManager* bm;
	struct DoubleArray arrayOfGrid[5];
};

