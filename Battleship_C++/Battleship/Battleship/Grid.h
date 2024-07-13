#pragma once
#include "Tile.h"
#include "BoatManager.h"
#include "2DArray.h"
#include "Controller.h"
#include "Model.h"
#include <string>

using namespace std;

class Grid
{
public:
	// PUBLIC FUNCTION -------------------
	Grid(class Model* model);
	~Grid();
	void PlaceAllSpecialTile(class Controller* c);
	void AddSpecialTile(class Controller* c, string tileName, int amount);

	// Getters and Setters
	struct DoubleArray& GetPlayerGrid();
	struct DoubleArray& GetBotGrid();
	class BoatManager* GetBoatManager();
	void SetBotGrid(struct DoubleArray newGrid);

private:
	// PRIVATE VARIABLES
	struct DoubleArray playerGrid;
	struct DoubleArray botGrid;

	class Model* m;
	class BoatManager* bm;

	// PRIVATE FUNCTION
	void InitializeGrid(DoubleArray& grid);
};