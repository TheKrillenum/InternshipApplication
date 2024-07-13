#include "Grid.h"

Grid::Grid(Model* model)
{
	m = model;
	bm = new BoatManager(m);

	InitializeGrid(playerGrid);
	InitializeGrid(botGrid);
}

Grid::~Grid()
{
	delete bm;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			delete playerGrid.arr[i][j];
			delete botGrid.arr[i][j];
			delete playerGrid.hist[i][j];
			delete botGrid.hist[i][j];
		}
	}
}

void Grid::PlaceAllSpecialTile(Controller* c)
{
	AddSpecialTile(c, "Explosive", 5);	// Explosive tile
	AddSpecialTile(c, "Power", 2);	// Power tile
	AddSpecialTile(c, "Angel", 1);	// Angel tile
}

void Grid::AddSpecialTile(Controller* c, string tileName, int amount)
{
	for (int i = 0; i < amount; i++) {
		c->GetView()->PlaceTileInstruction(tileName, amount);

		bool validInput = true;
		coordinate tempC;

		// Get valid coordinates from the player to place the special tile
		while (validInput) {
			c->GetView()->AskCoordinateMove();
			c->GetInputCoordinate(tempC);
			if (tempC.x >= 0 && tempC.x <= 9 && tempC.y >= 0 && tempC.y <= 9) {
				if ((playerGrid.arr[tempC.x][tempC.y]->GetSpecialTile() == true) || (playerGrid.arr[tempC.x][tempC.y]->GetBoat() != nullptr)) {
					c->GetView()->UpdateDisplay();
					c->GetView()->TileInvalidPlacement();
				}
				else {
					validInput = false;
				}
			}
			else {
				c->GetView()->InvalidCoordinate();
			}
		}

		// Create & place the specific special tile at the requested location
		if (tileName == "Explosive") {
			Tile* newTile = new ExplosiveTile();
			playerGrid.arr[tempC.x][tempC.y] = newTile;
		}
		else if (tileName == "Power") {
			Tile* newTile = new PowerTile();
			playerGrid.arr[tempC.x][tempC.y] = newTile;
		}
		else if (tileName == "Angel") {
			Tile* newTile = new AngelTile(bm);
			playerGrid.arr[tempC.x][tempC.y] = newTile;
		}
		c->GetView()->UpdateDisplay();
	}
}

DoubleArray& Grid::GetPlayerGrid()
{
	return playerGrid;
}

DoubleArray& Grid::GetBotGrid()
{
	return botGrid;
}

BoatManager* Grid::GetBoatManager()
{
	return bm;
}

void Grid::SetBotGrid(DoubleArray newGrid)
{
	botGrid = newGrid;
}

void Grid::InitializeGrid(DoubleArray& grid)
{
	// Initialise all grids with empty tiles (they have default value)
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			Tile* arrTemp = new Tile();
			grid.arr[i][j] = arrTemp;

			HistoryTile* histTemp = new HistoryTile();
			grid.hist[i][j] = histTemp;
			
		}
	}
}

