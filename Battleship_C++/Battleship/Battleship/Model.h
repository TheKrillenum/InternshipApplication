#pragma once
#include "PlayerInfo.h"
#include "Grid.h"
#include "2DArray.h"

class Model
{
public:
	// PUBLIC FUNCTION -------------------
	
	// Setup function
	Model();
	~Model();
	void PlaceAllBoats(class Controller* c);

	// Ingame function
	int TileShot(coordinate shotCoord);
	int MineExplosion(coordinate shotCoord);
	bool CheckGameState();

	// Getters and Setters
	bool GetGameOver();
	void SetShotHistory(bool b);
	bool GetShotHistory();
	class PlayerInfo* GetPlayer();
	class PlayerInfo* GetBot();
	class PlayerInfo* GetCurrentPlayer();
	void SetCurrentPlayer();
	class Grid* GetGrid();
	int GetDifficulty();
	void SetDifficulty(int i);
	bool GetDebugMode();
	void SetDebugMode(bool b);

private:
	// PRIVATE VARIABLES

	// Difficulty setting
	bool shotHistory;
	int difficulty;
	bool debugMode;

	// Game state
	bool gameOver;

	// Information saved for both players (human & AI), as well as who is playing during this specific turn
	class PlayerInfo* player;
	class PlayerInfo* bot;
	class PlayerInfo* currentPlayer;

	// grid
	class Grid* grid;
};

