#pragma once
#include "Boat.h"
#include "Coordinate.h"
#include "2DArray.h"
#include "Controller.h"
#include "PlayerInfo.h"
#include "Model.h"

class BoatManager
{
public:
	// PUBLIC FUNCTION -------------------
	BoatManager(class Model* model);
	~BoatManager();
	void PlaceBoat(struct Boat* boat, struct coordinate boatxy, struct DoubleArray* grid);
	void RemoveBoat(struct Boat* boat, struct DoubleArray* grid);
	void DestroyBoat(Boat* boat, DoubleArray* grid);
	void DamageBoat(Boat* boat, DoubleArray* grid);
	void RessurectBoat(PlayerInfo* owner, int BoatLength);
	bool ValidRessurect(PlayerInfo* owner, int BoatLength); 
	void CreateBoat(int BoatLength, struct coordinate placement, bool dir, class PlayerInfo* owner);
	bool CheckNearbyBoat(struct coordinate c, bool b, int length, struct DoubleArray* targetGrid, struct Boat* newBoat);

	// Getters and Setters
	void SetPlayerBoats(class Controller* c, class PlayerInfo* owner, struct DoubleArray* targetGrid);
	struct Boat* GetPlayerBoats(int index);
	void SetBotBoats(struct Boat* newBoats);
	struct Boat* GetBotBoats(int index);
	

private:
	// PRIATE VARIABLES
	struct Boat* PlayerBoats[6];
	struct Boat* BotBoats[6];
	class Model* m;
};

