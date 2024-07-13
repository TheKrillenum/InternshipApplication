
#include "Model.h"

Model::Model()
{
	grid = new Grid(this);
	gameOver = false;
	shotHistory = true;

	// Create both players (Human and AI) and 
	player = new PlayerInfo(false);
	bot = new PlayerInfo(true);
	currentPlayer = bot;
	difficulty = 0;
	debugMode = true;
}

Model::~Model()
{
	delete grid;
	delete player;
	delete bot;
}

void Model::PlaceAllBoats(Controller* c)
{
	grid->GetBoatManager()->SetPlayerBoats(c, GetPlayer(), &grid->GetPlayerGrid());
	// Set bot boats too, missing here
}

int Model::TileShot(coordinate shotCoord)
{
	// First get correct grid based on the player's turn (human or AI)
	DoubleArray* HistoryGrid;
	DoubleArray* TargetGrid;
	int output = 0;

	if (currentPlayer == player) {
		HistoryGrid = &grid->GetPlayerGrid();
		TargetGrid = &grid->GetBotGrid();
	}
	else {
		HistoryGrid = &grid->GetBotGrid();
		TargetGrid = &grid->GetPlayerGrid();
	}

	// Set the tile as shot for the history grid
	HistoryGrid->hist[shotCoord.x][shotCoord.y]->SetHit(true);

	
	if (TargetGrid->arr[shotCoord.x][shotCoord.y]->GetHit()) {
		// If the tile was already shot, then miss
		output = 7;
		return output;
	}
	else {
		// Otherwise set tile as shot and hit
		TargetGrid->arr[shotCoord.x][shotCoord.y]->SetHit(true);
	}


	if (TargetGrid->arr[shotCoord.x][shotCoord.y]->GetBoat()) {
		// If it's a boat, set the boat as hit and run all necessary logic
		// (Boat needs to be damaged, and if completely damaged, needs to be destroyed)
		HistoryGrid->hist[shotCoord.x][shotCoord.y]->SetTouch(true);
		grid->GetBoatManager()->DamageBoat(TargetGrid->arr[shotCoord.x][shotCoord.y]->GetBoat(), TargetGrid);
		output = 1;

		return output;
	}
	else if (TargetGrid->arr[shotCoord.x][shotCoord.y]->GetSpecialTile()) {
		// Special tile and their effect
		HistoryGrid->hist[shotCoord.x][shotCoord.y]->SetTouch(true);
		output = TargetGrid->arr[shotCoord.x][shotCoord.y]->SpecialEffect(GetCurrentPlayer());
		return output;
	}
	else {
		// Shot missed
		output = 5;
	}

	return output;
}

int Model::MineExplosion(coordinate shotCoord)
{
	// First get correct grid based on the player's turn (human or AI)
	DoubleArray* Grid;
	DoubleArray* Hist;

	int hit = 0;
	if (GetCurrentPlayer() == player) {
		Grid = &GetGrid()->GetPlayerGrid();
		Hist = &GetGrid()->GetBotGrid();
	}
	else {
		Grid = &GetGrid()->GetBotGrid();
		Hist = &GetGrid()->GetPlayerGrid();
	}

	// The mine explode and destroy everything around it (and it's own tile), to do this we check
	// 3 rows, a row of 3 tile above the mine, a row of 3 tile at the same level as the mine, and a 
	// row of 3 tiles below the mine. Doing this checks all tiles around the mine. If a boat is hit, 
	// run it's damaging logic.
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if ((shotCoord.x + i >= 0) && (shotCoord.x + i < 10) && (shotCoord.y + j >= 0) && (shotCoord.y + j < 10)) {
				if (!Grid->arr[shotCoord.x + i][shotCoord.y + j]->GetHit()) {
					Grid->arr[shotCoord.x + i][shotCoord.y + j]->SetHit(true);
					Hist->hist[shotCoord.x + i][shotCoord.y + j]->SetHit(true);
					if (Grid->arr[shotCoord.x + i][shotCoord.y + j]->GetBoat() != nullptr) {
						grid->GetBoatManager()->DamageBoat(Grid->arr[shotCoord.x + i][shotCoord.y + j]->GetBoat(), Grid);
						Hist->hist[shotCoord.x + i][shotCoord.y + j]->SetTouch(true);
						hit++;
					}

				}
			}
		}
	}

	// Return the amount of hit the mine did
	return hit;
}

bool Model::CheckGameState()
{
	// Check if one of the players (bot or human) has 0 or less remaining boats.
	// If so, the game is over. Otherwise, the game keeps going.
	if ((player->GetRemainingBoats() <= 0) || (bot->GetRemainingBoats() <= 0)) {
		gameOver = true;
		return gameOver;
	}
	else {
		gameOver = false;
		return gameOver;
	}
}

bool Model::GetGameOver()
{
	return gameOver;
}

void Model::SetShotHistory(bool b)
{
	shotHistory = b;
}

bool Model::GetShotHistory()
{
	return shotHistory;
}

PlayerInfo* Model::GetPlayer()
{
	return player;
}

PlayerInfo* Model::GetBot()
{
	return bot;
}

PlayerInfo* Model::GetCurrentPlayer()
{
	return currentPlayer;
}

void Model::SetCurrentPlayer()
{
	// Switch from Bot to Player, and vice-versa
	currentPlayer = (currentPlayer == player) ? bot : player;
}

Grid* Model::GetGrid()
{
	return grid;
}

int Model::GetDifficulty()
{
	return difficulty;
}

void Model::SetDifficulty(int i)
{
	difficulty = i;
}

bool Model::GetDebugMode()
{
	return debugMode;
}

void Model::SetDebugMode(bool b)
{
	debugMode = b;
}
