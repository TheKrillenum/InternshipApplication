#include "BotAI.h"
#include "time.h"
#include <stdlib.h>

BotAI::BotAI(Model* model, BoatManager* boatManager)
{
	m = model;
	bm = boatManager;
	
	strategy = nullptr;

	for (int i = 0; i < 5; i++) {
		arrayOfGrid[i] = InitArrayOfGrid();
	}
	
	SetAllArrayOfGrid();

	srand(time(NULL));
}

void BotAI::CallShoot(coordinate &coord)
{
	strategy->Shoot(coord);
}

coordinate BotAI::BotInputCoord(int max, int min)
{
	// Random bot coord input
	int Row = rand() % (max - min + 1) + min;
	int Column = rand() % (max - min + 1) + min;
	coordinate output = { Row, Column };
	return output;
}

int BotAI::BotInputInddex(int max, int min)
{
	// Random index
	int output = rand() % (max - min + 1) + min;
	return output;
}

DoubleArray BotAI::InitArrayOfGrid()
{
	DoubleArray output;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			Tile* temp = new Tile();
			output.arr[i][j] = temp;

		}
	}

	return output;
}

void BotAI::setBotStrategy()
{
	if (m->GetDifficulty() == 1) {
		EasyStrategy* temp = new EasyStrategy(m);
		strategy = temp;
	}
	else {
		MediumHardStrategy* temp = new MediumHardStrategy(m);
		strategy = temp;
	}
}

BotStrategy* BotAI::GetStrategy()
{
	return strategy;
}

void BotAI::SetAllArrayOfGrid()
{

	int allBoatLength = 1;

	Boat* boat1 = new Boat;
	boat1->length = ++allBoatLength;
	boat1->origin.x = 0; 
	boat1->origin.y = 0;
	boat1->dirRight = false;
	boat1->intact = true;
	boat1->destroyed = false;
	boat1->owner = m->GetBot();
	for (int i = 0; i < boat1->length; i++) {
		arrayOfGrid[0].arr[boat1->origin.x + i][boat1->origin.y]->SetBoat(boat1);
	}

	Boat* boat2 = new Boat;
	boat2->length = ++allBoatLength;
	boat2->origin.x = 9;
	boat2->origin.y = 7;
	boat2->dirRight = true;
	boat2->intact = true;
	boat2->destroyed = false;
	boat2->owner = m->GetBot();
	for (int i = 0; i < boat2->length; i++) {
		arrayOfGrid[0].arr[boat2->origin.x][boat2->origin.y + i]->SetBoat(boat2);
	}

	Boat* boat3 = new Boat;
	boat3->length = ++allBoatLength;
	boat3->origin.x = 9;
	boat3->origin.y = 0;
	boat3->dirRight = true;
	boat3->intact = true;
	boat3->destroyed = false;
	boat3->owner = m->GetBot();
	for (int i = 0; i < boat3->length; i++) {
		arrayOfGrid[0].arr[boat3->origin.x][boat3->origin.y + i]->SetBoat(boat3);
	}

	Boat* boat4 = new Boat;
	boat4->length = ++allBoatLength;
	boat4->origin.x = 5;
	boat4->origin.y = 5;
	boat4->dirRight = false;
	boat4->intact = true;
	boat4->destroyed = false;
	boat4->owner = m->GetBot();
	for (int i = 0; i < boat4->length; i++) {
		arrayOfGrid[0].arr[boat4->origin.x + i][boat4->origin.y]->SetBoat(boat4);
	}

	Boat* boat5 = new Boat;
	boat5->length = ++allBoatLength;
	boat5->origin.x = 1;
	boat5->origin.y = 8;
	boat5->dirRight = false;
	boat5->intact = true;
	boat5->destroyed = false;
	boat5->owner = m->GetBot();
	for (int i = 0; i < boat5->length; i++) {
		arrayOfGrid[0].arr[boat5->origin.x + i][boat5->origin.y]->SetBoat(boat5);
	}

	Tile* newExplosiveTile1 = new ExplosiveTile();
	arrayOfGrid[0].arr[2][0] = newExplosiveTile1;
	Tile* newExplosiveTile2 = new ExplosiveTile();
	arrayOfGrid[0].arr[1][2] = newExplosiveTile2;
	Tile* newExplosiveTile3 = new ExplosiveTile();
	arrayOfGrid[0].arr[9][4] = newExplosiveTile3;
	Tile* newExplosiveTile4 = new ExplosiveTile();
	arrayOfGrid[0].arr[9][6] = newExplosiveTile4;
	Tile* newExplosiveTile5 = new ExplosiveTile();
	arrayOfGrid[0].arr[7][8] = newExplosiveTile5;

	Tile* newPowerTile1 = new PowerTile();
	arrayOfGrid[0].arr[8][0] = newPowerTile1;
	Tile* newPowerTile2 = new PowerTile();
	arrayOfGrid[0].arr[0][6] = newPowerTile2;

	Tile* newAngelTile = new AngelTile(bm);
	arrayOfGrid[0].arr[0][9] = newAngelTile;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			HistoryTile* histTemp = new HistoryTile();
			arrayOfGrid[0].hist[i][j] = histTemp;

		}
	}
}

DoubleArray BotAI::GetRandomGrid()
{
	return arrayOfGrid[0];
}
