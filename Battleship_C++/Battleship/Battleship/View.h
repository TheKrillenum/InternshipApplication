#pragma once
#include "Model.h"
#include <Windows.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "PlayerInfo.h"

using namespace std;

class View
{
public:
	// PUBLIC FUNCTION -------------------
	View(class Model* model);
	void BotDifficulty();
	void DebugMode();
	void InvalidChoice(int min, int max);
	void Wait(int seconds);
	void GridDisplay(PlayerInfo* player);
	void UpdateDisplay();
	void Clear();
	void SpaceBetweenGrid();
	void ColorTest();
	void AskCoordinateMove();
	void AskAbortableCoordinate();
	void AskBool();
	void AskChoice();
	void AskOrientation();
	void PlaceBoatInstruction(int length);
	void InvalidInput();
	void InvalidCoordinate();
	void NearbyBoatPlacement();
	void PlaceTileInstruction(string tile, int amount);
	void TileInvalidPlacement();
	void ShootInstruction();
	void BoatHit();
	void PowerUse(int powerLeft);
	void ShotMissed();
	void DisplayWinner();
	void PowerTileHit();
	void ExplosiveTileHit(int hit);
	void AngelTileHit();
	void AngelInstruction(int caseIndex);
	void AvailableBoats(class PlayerInfo* owner);
	void InvalidRessurect();
	void ChooseBoat();
	void InvalidLenght();
	void ShootAgain();

private:
	class Model* m;
	HANDLE hConsole;
};

/* COLOR SCHEME INT:
	31 -> Normal tile
	26 -> own boat
	15 -> Explosive
	16 -> Movement & Rotation
	 6 -> Power
	111-> Angel

	28 -> shot and miss
	30-> no shot
	71 -> shot and hit

	 7 -> default color (black background, white foreground)

	 Yello (dmaaged) = 6
	 Green = 10
	 Red = 4
*/