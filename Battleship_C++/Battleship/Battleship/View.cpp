#include "View.h"
#include <iostream>
#include <string>
#include "Boat.h"

using namespace std;

View::View(Model* model)
{
	m = model;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void View::BotDifficulty()
{
	SetConsoleTextAttribute(hConsole, 112);
	cout << "~BATTLEFIELD~" << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Welcome to the C++ implementation of Battlefield !" << endl;
	cout << "You are going to start playing a match ! What difficulty do you choose ?" << endl << endl;
	cout << "1 - Easy" << endl;
	cout << "2 - Medium" << endl;
	cout << "3 - Hard" << endl << endl;
	cout << "Enter your choice:" << endl;
	cout << ">";
}

void View::DebugMode()
{
	SetConsoleTextAttribute(hConsole, 112);
	cout << "~BATTLEFIELD~" << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Do you want to play the game in Debug mode ?" << endl;
	cout << "(Meant formtesting purposes, the bot grid will be visible to the player)." << endl << endl;
	cout << "1 - Yes" << endl;
	cout << "2 - No" << endl << endl;
	cout << "Enter your choice:" << endl;
	cout << ">";
}

void View::InvalidChoice(int min, int max)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Invalid choice. The index of your choices range between " << min << " and " << max << endl;
	cout << "Please enter a correct choice:" << endl;
	cout << ">";
}

void View::Wait(int seconds)
{
	this_thread::sleep_for(chrono::seconds(seconds));
}

void View::GridDisplay(PlayerInfo* player)
{
	DoubleArray Grid;

	// Get the correct grid and set them based on the player currently playing
	if (player == m->GetPlayer()) {
		Grid = m->GetGrid()->GetPlayerGrid();
		SetConsoleTextAttribute(hConsole, 112);
		cout << "Player grid" << endl << endl;
	}
	else {
		Grid = m->GetGrid()->GetBotGrid();
		SetConsoleTextAttribute(hConsole, 112);
		cout << "Bot grid" << endl << endl;	// Debbuging purposes, in case we want to see what the bot does
	}

	// First row with indexes

	SetConsoleTextAttribute(hConsole, 7);
	for (int i = 0; i <= 10; i++) {
		cout.width(3);
		cout << i << " ";
	}

	if (m->GetShotHistory()) {
		// History only displayed on easy & Medium difficulty
		SetConsoleTextAttribute(hConsole, 7);

		SpaceBetweenGrid();

		for (int i = 0; i <= 10; i++) {
			cout.width(3);
			cout << i << " ";
		}
		
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {

		// Display index
		SetConsoleTextAttribute(hConsole, 7);
		cout.width(3);
		cout << (i + 1) << " ";

		// Display tiles of the boat grid
		for (int j = 0; j < 10; j++) {
			if (Grid.arr[i][j]->GetBoat() != nullptr) {
				if (Grid.arr[i][j]->GetBoat()->destroyed) {
					SetConsoleTextAttribute(hConsole, 29);
					cout.width(4);
					cout << "| X ";
				}
				else {
					if (Grid.arr[i][j]->GetHit()) {
						// Boat is completely intact and safe
						SetConsoleTextAttribute(hConsole, 22);
					}
					else {
						SetConsoleTextAttribute(hConsole, 26);
					}
					cout << "| " << Grid.arr[i][j]->GetBoat()->length << " ";
				}
			}
			else if (Grid.arr[i][j]->GetSpecialTile()) {
				if (Grid.arr[i][j]->GetTileType() == "Explosive") {
					if (Grid.arr[i][j]->GetHit()) {
						SetConsoleTextAttribute(hConsole, 29);
					}
					else {
						SetConsoleTextAttribute(hConsole, 15);
					}
					cout.width(4);
					cout << "| E ";
				}
				else if (Grid.arr[i][j]->GetTileType() == "Movement") {
					if (Grid.arr[i][j]->GetHit()) {
						SetConsoleTextAttribute(hConsole, 29);
					}
					else {
						SetConsoleTextAttribute(hConsole, 16);
					}
					cout.width(4);
					cout << "| M ";
				}
				else if (Grid.arr[i][j]->GetTileType() == "Rotation") {
					if (Grid.arr[i][j]->GetHit()) {
						SetConsoleTextAttribute(hConsole, 29);
					}
					else {
						SetConsoleTextAttribute(hConsole, 16);
					}
					cout.width(4);
					cout << "| R ";
				}
				else if (Grid.arr[i][j]->GetTileType() == "Power") {
					if (Grid.arr[i][j]->GetHit()) {
						SetConsoleTextAttribute(hConsole, 29);
					}
					else {
						SetConsoleTextAttribute(hConsole, 6);
					}
					cout.width(4);
					cout << "| P ";
				}
				else if (Grid.arr[i][j]->GetTileType() == "Angel") {
					if (Grid.arr[i][j]->GetHit()) {
						SetConsoleTextAttribute(hConsole, 29);
					}
					else {
						SetConsoleTextAttribute(hConsole, 111);
					}
					cout.width(4);
					cout << "| A ";
				}
			}
			else {
				// tile not hit yet
				if (Grid.arr[i][j]->GetHit()) {
					SetConsoleTextAttribute(hConsole, 28);
				}
				else {
					SetConsoleTextAttribute(hConsole, 30);
				}
				cout.width(4);
				cout << "| o ";
			}
		}

		SpaceBetweenGrid();

		// Display index

		if (m->GetShotHistory()) {
			// History only displayed on easy & medium difficulty

			SetConsoleTextAttribute(hConsole, 7);
			cout.width(3);
			cout << (i + 1) << " ";

			// Display the tiles of the shoot history
			for (int j = 0; j < 10; j++) {
				if (Grid.hist[i][j]->GetTouch()) {
					// tile got hit and contained something.
					SetConsoleTextAttribute(hConsole, 71);
					cout.width(4);
					cout << "| X ";
				}
				else if (Grid.hist[i][j]->GetHit()) {
					// tile got hit, nothing here.
					SetConsoleTextAttribute(hConsole, 28);
					cout.width(4);
					cout << "| O ";
				}
				else {
					// tile not hit yet
					SetConsoleTextAttribute(hConsole, 30);
					cout.width(4);
					cout << "| o ";
				}
			}
		}

		SetConsoleTextAttribute(hConsole, 7);
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 104; i++) {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "-";
	}

	cout << endl << endl;
}

void View::UpdateDisplay()
{
	SetConsoleTextAttribute(hConsole, 7);
	if (system("CLS")) system("clear");
	GridDisplay(m->GetPlayer());
	
	if (m->GetDebugMode()) {
		GridDisplay(m->GetBot());
	}
}

void View::Clear()
{
	SetConsoleTextAttribute(hConsole, 7);
	if (system("CLS")) system("clear");
}

void View::SpaceBetweenGrid()
{
	for (int i = 0; i < 5; i++) {
		cout.width(3);
		SetConsoleTextAttribute(hConsole, 7);

		if (i == 2) {
			cout << "|";
		}
		else {
			cout << " ";
		}
	}
}

void View::ColorTest()
{
	for (int k = 1; k < 255; k++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(hConsole, k);
		cout << k << " I want to be nice today!" << endl;
	}
}

void View::AskCoordinateMove()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "Enter a row (1 - 10) and a column (1 - 10) separated by a space (in the form \"x y\")." << endl;
	cout << ">";
}

void View::AskAbortableCoordinate()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "Enter a row (1 - 10) and a column (1 - 10) separated by a space (in the form \"x y\")." << endl;
	cout << "Type 0 0 to exit." << endl;
	cout << ">";
}

void View::AskBool()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Enter 0 (no) or 1 (yes)." << endl;
	cout << ">";
}

void View::AskChoice()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Enter 0 or 1." << endl;
	cout << ">";
}

void View::AskOrientation()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "Enter 0 (right orientation) or 1 (downwards orientation)." << endl;
	cout << ">";
}

void View::PlaceBoatInstruction(int length)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Setup phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Boat with a length of " << length << " needs to be placed." << endl;
	cout << "You need to enter the coordinate of the boats origin point and then choose a direction." << endl;
	cout << "The boat can spread from the origin point either toward the right (1) or downwards (0)." << endl;
}

void View::InvalidInput()
{
	SetConsoleTextAttribute(hConsole, 4);
	cout << "WARNING" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "The boat goes out of bound ! Please pay attention at the length of the boat when placing it." << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
}

void View::InvalidCoordinate()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Invalid input: Please make sure the entered coordinate goes from 1 to 9." << endl;
}

void View::NearbyBoatPlacement()
{
	SetConsoleTextAttribute(hConsole, 4);
	cout << "WARNING" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "The coordinate you have entered is adjacent to another boat !" << endl;
	cout << "You have to leave a space of minimum 1 tile between each and every boat you place." << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
}

void View::PlaceTileInstruction(string tile, int amount)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << amount << " " << tile << " tile is to be placed." << endl;
	cout << "Enter the coordinates where the new tile will be placed." << endl;
}

void View::TileInvalidPlacement() 
{
	SetConsoleTextAttribute(hConsole, 4);
	cout << "WARNING" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "A special tile can only be placed where there are no other special tiles or boats." << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
}

void View::ShootInstruction()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Please enter the coordinate of the tile you wish to bombard." << endl;
}

void View::BoatHit()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "You ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "The ";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "AI ";
	}

	SetConsoleTextAttribute(hConsole, 7);
	cout << "hit a target !";

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "You ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "can shoot again." << endl;
		cout << ">";
	}
	else {
		Wait(2);
	}
}

void View::PowerUse(int powerLeft)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;
	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "You ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "The AI ";
	}
	SetConsoleTextAttribute(hConsole, 7);
	cout << "missed. A power has been consummed to shoot again." << endl;
	cout << "Number of power left: ";
	if (powerLeft <= 0) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "0" << endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 10);
		cout << powerLeft << endl;
	}

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << endl << "You ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "can shoot again:";
		cout << ">";
	}
	else {
		Wait(3);
	}
}

void View::ShotMissed()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);
	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "You ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "The AI ";
	}
	SetConsoleTextAttribute(hConsole, 7);
	 cout << "missed !It is now the";
	 if (m->GetCurrentPlayer() == m->GetPlayer()) {
		 SetConsoleTextAttribute(hConsole, 4);
		 cout << " the AI's ";
	 }
	 else {
		 SetConsoleTextAttribute(hConsole, 10);
		 cout << " Player's ";
	 }
	 SetConsoleTextAttribute(hConsole, 7);
	 cout << "turn to play." << endl << endl;

	 if (m->GetCurrentPlayer() == m->GetPlayer()) {
		 SetConsoleTextAttribute(hConsole, 112);
		 cout << "Press any button to continue.";
		 cin.get();
	 }
	 else {
		 Wait(2);
	 }
}

void View::DisplayWinner()
{
	Clear();

	SetConsoleTextAttribute(hConsole, 112);
	cout << endl << "~GAME OVER~" << endl << endl;
	if (m->GetPlayer()->GetRemainingBoats() > 0) {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "The ";
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Player";
		SetConsoleTextAttribute(hConsole, 7);
		cout << " has won the game. Congratulation !";
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "The ";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "AI";
		SetConsoleTextAttribute(hConsole, 7);
		cout << " has won the game. You are bad !";
	}

	SetConsoleTextAttribute(hConsole, 7);
	cout << "";
}

void View::PowerTileHit()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Your ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "The AI's ";
	}

	SetConsoleTextAttribute(hConsole, 7);
	cout << "number of free shots has increased to ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << m->GetCurrentPlayer()->GetPoweAquired() << endl << endl;

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "You ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "can shoot again." << endl;
		cout << ">";
	}
	else {
		Wait(3);
	}
	
}

void View::ExplosiveTileHit(int hit)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "You ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "The ";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "AI ";
	}
	SetConsoleTextAttribute(hConsole, 7);
	cout << "have shot an explosive mine !" << endl;
	cout << "It damaged " << hit << " of";

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << " your ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		cout << " the ";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "AI's ";
	}

	cout << "tile." << endl << endl;

	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "You ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "can shoot again." << endl;
		cout << ">";
	}
	else {
		Wait(3);
	}
	
}

void View::AngelTileHit()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;
	if (m->GetCurrentPlayer() == m->GetPlayer()) {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Congratulation, ";
		SetConsoleTextAttribute(hConsole, 10);
		cout << "you";
		SetConsoleTextAttribute(hConsole, 7);
		cout << " have hit the ";
	}
	else {
		SetConsoleTextAttribute(hConsole, 7);
		cout << "The ";
		SetConsoleTextAttribute(hConsole, 4);
		cout << "AI ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "hit the";
	}

	SetConsoleTextAttribute(hConsole, 6);
	cout << "Angel";
	SetConsoleTextAttribute(hConsole, 7);
	cout << " tile." << endl;
}

void View::AngelInstruction(int caseIndex)
{
	switch (caseIndex)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, 7);
		cout << "You can now ressurect one of your boats." << endl << endl;
		cout << "Choose which boat to ressurect by entering the length of the chosen destroyed boat" << endl;
		break;

	case 2:
		SetConsoleTextAttribute(hConsole, 7);
		cout << "You can now create a new boat" << endl << endl;
		cout << "Please choose it's size, it's orientation and it's placement coordinate as you" << endl;
		cout << "did to place boats during the setup phase." << endl;
		break;

	default:
		SetConsoleTextAttribute(hConsole, 7);
		cout << "ERROR, wrong parameter View.cpp - 445";
		break;
	}
}

void View::AvailableBoats(PlayerInfo* owner)
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "Here is a list of your current boats:" << endl;
	cout << "(Boats in red are destroyed and can be ressurected, Boats in green can't be ressurected)" << endl << endl;
	cout << "Boats: ";

	for (int i = 0; i < 6; i++) {
		if (m->GetGrid()->GetBoatManager()->GetPlayerBoats(i) != nullptr) {
			if (m->GetGrid()->GetBoatManager()->GetPlayerBoats(i)->destroyed) {
				SetConsoleTextAttribute(hConsole, 4);
				cout << m->GetGrid()->GetBoatManager()->GetPlayerBoats(i)->length << "  ";
			}
			else {
				SetConsoleTextAttribute(hConsole, 10);
				cout << m->GetGrid()->GetBoatManager()->GetPlayerBoats(i)->length << "  ";
			}
		}
	}

	cout << endl;
}

void View::InvalidRessurect()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Invalid input: You can only ressurect boats that have been destroyed entierly. Please try again:" << endl;
	cout << "(Please refer to the list of current boats above)" << endl;
	cout << ">";
}

void View::ChooseBoat()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "Please enter the length of the chosen boat." << endl;
	cout << "(Must be between 2 and 6)" << endl;
	cout << ">";
}

void View::InvalidLenght()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Invalid input: length should range from 2 to 6. Please try again:" << endl;
	cout << ">";
}

void View::ShootAgain()
{
	SetConsoleTextAttribute(hConsole, 7);
	cout << "Shooting phase ~" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout << "----------------" << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);
	cout << "You can shoot again." << endl;
	cout << ">";
}
