#include "BoatManager.h"

BoatManager::BoatManager(Model* model) {
    for (int i = 0; i < 6; ++i) {
        PlayerBoats[i] = nullptr;
        BotBoats[i] = nullptr;
    }

    m = model;
}

BoatManager::~BoatManager() {
    for (int i = 0; i < 6; ++i) {
        delete PlayerBoats[i];
        delete BotBoats[i];
    }
}

void BoatManager::PlaceBoat(Boat* b, coordinate c, DoubleArray* grid)
{
    b->origin = c;

    // Set the boat variable of the tile at the desired coordinates and along it 
    // path until it reaches the desired length
    for (int i = 0; i < (b->length); i++) {
        int temp;
        if (b->dirRight) {
            temp = c.y + i;
            grid->arr[c.x][temp]->SetBoat(b);
        }
        else {
            temp = c.x + i;
            grid->arr[temp][c.y]->SetBoat(b);
        }
    }

}

void BoatManager::RemoveBoat(Boat* b, DoubleArray* grid)
{
    coordinate BoatOrigin = b->origin;

    // Replace the boat variables of tiles into nullptr.
    for (int i = 0; i < (b->length); i++) {
        int temp;
        if (b->dirRight) {
            temp = BoatOrigin.y + i;
            grid->arr[BoatOrigin.x][temp]->SetBoat(nullptr);
        }
        else {
            temp = BoatOrigin.x + i;
            grid->arr[temp][BoatOrigin.y]->SetBoat(nullptr);
        }
    }
}

void BoatManager::DestroyBoat(Boat* boat, DoubleArray* grid)
{
    boat->owner->ReduceRemainingBoats();

    coordinate temp = boat->origin;

    // Set the "destroyed" variable of all tiles from a specific boat to true.
    for (int i = 0; i < boat->length; i++) {
        if (boat->dirRight) {
            grid->arr[temp.x][temp.y + i]->GetBoat()->destroyed = true;
        }
        else {
            grid->arr[temp.x + i][temp.y]->GetBoat()->destroyed = true;
        }
    }
}

void BoatManager::DamageBoat(Boat* boat, DoubleArray* grid)
{
    coordinate temp = boat->origin;

    bool boatDestroyed = true;

    // Set the "intact" variable of a boat to false, and if the whole boat has been damaged, then 
    // run "DestroyBoat()".
    for (int i = 0; i < boat->length; i++) {
        if (boat->dirRight) {
            grid->arr[temp.x][temp.y + i]->GetBoat()->intact = false;
            if (!grid->arr[temp.x][temp.y + i]->GetHit()) {
                boatDestroyed = false;
            }
        }
        else {
            grid->arr[temp.x + i][temp.y]->GetBoat()->intact = false;
            if (!grid->arr[temp.x + i][temp.y]->GetHit()) {
                boatDestroyed = false;
            }
        }
    }

    if (boatDestroyed) {
        DestroyBoat(boat, grid);
    }
}

void BoatManager::RessurectBoat(PlayerInfo* owner, int BoatLength)
{
    // For the player: chosen boat with specific lenght is "revived" (bool intact = true, destroyed = false)
    if (m->GetCurrentPlayer() == m->GetPlayer()) {
        owner->IncrementRemainingBoats();
        DoubleArray temp = m->GetGrid()->GetPlayerGrid();

        for (int i = 0; i < BoatLength; i++) {
            if (GetPlayerBoats(BoatLength - 2)->dirRight) {
                temp.arr[GetPlayerBoats(BoatLength - 2)->origin.x][GetPlayerBoats(BoatLength - 2)->origin.y + i]->GetBoat()->destroyed = false;
                temp.arr[GetPlayerBoats(BoatLength - 2)->origin.x][GetPlayerBoats(BoatLength - 2)->origin.y + i]->GetBoat()->intact = true;
            }
            else {
                temp.arr[GetPlayerBoats(BoatLength - 2)->origin.x + i][GetPlayerBoats(BoatLength - 2)->origin.y]->GetBoat()->destroyed = false;
                temp.arr[GetPlayerBoats(BoatLength - 2)->origin.x + i][GetPlayerBoats(BoatLength - 2)->origin.y]->GetBoat()->intact = true;
            }
        }

    }   // For the bot player, not implemented yet, work in progress
    else {
        owner->IncrementRemainingBoats();
        DoubleArray temp = m->GetGrid()->GetBotGrid();

        for (int i = 0; i < BoatLength; i++) {
            if (GetBotBoats(BoatLength - 2)->dirRight) {
                temp.arr[GetBotBoats(BoatLength - 2)->origin.x][GetBotBoats(BoatLength - 2)->origin.y + i]->GetBoat()->destroyed = false;
                temp.arr[GetBotBoats(BoatLength - 2)->origin.x][GetBotBoats(BoatLength - 2)->origin.y + i]->GetBoat()->intact = true;
            }
            else {
                temp.arr[GetBotBoats(BoatLength - 2)->origin.x + i][GetBotBoats(BoatLength - 2)->origin.y]->GetBoat()->destroyed = false;
                temp.arr[GetBotBoats(BoatLength - 2)->origin.x + i][GetBotBoats(BoatLength - 2)->origin.y]->GetBoat()->intact = true;
            }
        }
    }
}

bool BoatManager::ValidRessurect(PlayerInfo* owner, int BoatLength)
{
    // Return true if the boat is not destroyed (and exist).
    if (owner == m->GetPlayer() && PlayerBoats[BoatLength - 2] != nullptr && !PlayerBoats[BoatLength - 2]->destroyed) {
        return false;
    }
    else if (owner == m->GetBot() && BotBoats[BoatLength - 2] != nullptr && !BotBoats[BoatLength - 2]->destroyed) {
        return false;
    }

    return true;
}

void BoatManager::CreateBoat(int BoatLength, coordinate placement, bool dir, PlayerInfo* owner)
{
    // Simply create and place a boat with the desired length at the desired coordinate
    Boat* temp = new Boat();
    temp->length = BoatLength;
    temp->destroyed = false;
    temp->intact = true;
    temp->dirRight = dir;
    temp->owner = owner;
    temp->origin = placement;

    // Place the boat on the correct grid (Player or Bot)
    if (owner = m->GetPlayer()) {
        PlayerBoats[5] = temp;
        PlaceBoat(temp, placement, &m->GetGrid()->GetPlayerGrid());
    }
    else {
        BotBoats[5] = temp;
        PlaceBoat(temp, placement, &m->GetGrid()->GetBotGrid());
    }
}

void BoatManager::SetPlayerBoats(Controller* c, PlayerInfo* owner, struct DoubleArray* targetGrid)
{
    coordinate tempC = { 0, 0 };
    bool tempB;

    // Set each boat one by one, starting with boat of length 2, ending with boat of length 6
    for (int i = 0; i < 5; i++) {
        Boat* temp = new Boat();
        bool validInput = true;
        int tempLength = (i + 2);
        temp->length = tempLength;

        // Check if the payer's input is valid (multiple check)
        while (validInput) {
            c->GetView()->PlaceBoatInstruction(temp->length);
            c->GetView()->AskChoice();
            c->GetInputBool(tempB);
            temp->dirRight = tempB;
            c->GetView()->AskCoordinateMove();
            c->GetInputCoordinate(tempC);

            if (tempB && ((tempC.y + (tempLength - 1)) >= 10)) {
                c->GetView()->UpdateDisplay();
                c->GetView()->InvalidInput();
            }
            else if (!tempB && ((tempC.x + (tempLength - 1)) >= 10)) {
                c->GetView()->UpdateDisplay();
                c->GetView()->InvalidInput();
            }
            else if(tempC.x < 0 || tempC.y < 0){
                c->GetView()->UpdateDisplay();
                c->GetView()->InvalidInput();
            }
            else if (CheckNearbyBoat(tempC, tempB, tempLength, targetGrid, temp)) {
                c->GetView()->UpdateDisplay();
                c->GetView()->NearbyBoatPlacement();
            }
            else {
                validInput = false;
            }
        }

        temp->origin = tempC;
        temp->intact = true;
        temp->destroyed = false;
        temp->owner = owner;
        PlayerBoats[i] = temp;

        PlaceBoat(PlayerBoats[i], tempC, targetGrid);
        c->GetView()->UpdateDisplay();
    }
}

Boat* BoatManager::GetPlayerBoats(int index)
{
    return PlayerBoats[index];
}

void BoatManager::SetBotBoats(Boat* newBoats)
{
    // To be done
}

Boat* BoatManager::GetBotBoats(int index)
{
    return BotBoats[index];
}

bool BoatManager::CheckNearbyBoat(coordinate c, bool b, int length, DoubleArray* targetGrid, struct Boat* newBoat)
{
    // Returns "True" if there is a boat nearby the desired sport && if there is a Special tile at the desired location.

    if (!b) {   // Check for boat that faces the right direction
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < (length + 1); j++) {
                if ((c.x + j >= 0 && c.x + j < 10) && (c.y + i >= 0 && c.y + i < 10) && (targetGrid->arr[c.x + j][c.y + i]->GetBoat() != nullptr)) {
                    return true;
                }
                if (i == 0 && (j > (-1) && j < length && targetGrid->arr[c.x + j][c.y + i]->GetSpecialTile())) {
                    return true;
                }
            }
        }
    }
    else {  // Check for boat that faces the downward direction
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < (length + 1); j++) {
                if ((c.x + i >= 0 && c.x + i < 10) && (c.y + j >= 0 && c.y + j < 10) && (targetGrid->arr[c.x + i][c.y + j]->GetBoat() != nullptr)) {
                    return true;
                }
                if (i == 0 && (j > (-1) && j < length && targetGrid->arr[c.x + i][c.y + j]->GetSpecialTile())) {
                    return true;
                }
            }
        }
    }

    return false;
}
