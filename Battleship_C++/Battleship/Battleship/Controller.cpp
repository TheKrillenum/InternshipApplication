#include "Controller.h"
#include "string.h"

using namespace std;

Controller::Controller(Model* model, View* view)
{
	m = model;
	v = view;
	bot = new BotAI(m, m->GetGrid()->GetBoatManager());

	// Give bot his grid array
	m->GetGrid()->SetBotGrid(GetBot()->GetRandomGrid());
}

void Controller::Setup()
{
	// Set player boats & Special tile (setting up grid)
	v->UpdateDisplay();
	m->GetGrid()->GetBoatManager()->SetPlayerBoats(this, m->GetPlayer(), &m->GetGrid()->GetPlayerGrid());
	m->GetGrid()->PlaceAllSpecialTile(this);
}

void Controller::Menu()
{
	// Let the player set the difficulty and debug mode
	int choice;
	v->Clear();
	v->BotDifficulty();
	bool valid2 = true;
	while (valid2) {
		GetInputIndex(choice);
		if (choice >= 1 && choice <= 3) {
			valid2 = false;
		}
		else {
			v->InvalidChoice(1, 3);
		}
	}
	m->SetDifficulty(choice);

	v->Clear();
	v->DebugMode();
	bool valid3 = true;
	while (valid3) {
		GetInputIndex(choice);
		if (choice == 1 || choice == 2) {
			valid3 = false;
		}
		else {
			v->InvalidChoice(1, 2);
		}
	}
	if (choice == 1) {
		m->SetDebugMode(true);
	}
	else if (choice == 2) {
		m->SetDebugMode(false);
	}
}

void Controller::PlayGame()
{
	Menu();

	// Set the game's state with info the player gave in the menu (difficulty, debug mode)
	if (m->GetDifficulty() == 3) {
		m->SetShotHistory(false);
	}
	else {
		m->SetShotHistory(true);
	}

	bot->setBotStrategy();
	v->Clear();

	Setup();

	// Game start
	while (!m->GetGameOver()) {
		// While the game is playing, change player every turn and reset some of their variables
		m->SetCurrentPlayer();
		coordinate input;
		v->UpdateDisplay();

		int numberOfShots = 0;
		bool hit = true;
		
		// Display instruction only if the player is Human (not AI)
		if (m->GetCurrentPlayer() == m->GetPlayer()) {
			v->ShootInstruction();
			v->AskCoordinateMove();
		}

		while (hit) {
			// For every shot, detect what was hit and react. If the shot hit, the loop continues.

			if (m->GetCurrentPlayer() == m->GetPlayer()) {
				GetInputCoordinate(input);
			}
			else if (m->GetCurrentPlayer() == m->GetBot()) {
				bot->CallShoot(input);
			}
			

			switch (m->TileShot(input))
			{
			case 1:		// Boat hit
				BoatHit();
				if (m->GetCurrentPlayer() == m->GetBot() && m->GetDifficulty() != 1) {
					bot->GetStrategy()->target = &input;
				}
				numberOfShots++;
				break;

			case 2:		// Explosion tile hit
				MineHit(input);
				numberOfShots++;
				break;

			case 3:		// Angel tile hit
				AngelHit(input);
				numberOfShots++;
				break;

			case 4:		// Power tile hit
				PowerHit();
				numberOfShots++;
				break;

			case 5:		// Nothing hit
				hit = NoHit(numberOfShots);
				numberOfShots++;
				break;

			default:	// Error message, appear for debugging
				cout << "ERROR: Hit detection mistake" << endl;
				cin.get();
				break;
			}

			// After each shot, check the game state. If a player lost, stop game immediately
			if (m->CheckGameState()) {
				hit = false;
			}
		}
	}
	
	v->DisplayWinner();
	cin.get();
	ExitGame();
}

void Controller::removeWhiteSpace(string& inputLine) {
	int count = 0;
	int i = 0;

	while (inputLine[i++] == ' ') count++;

	inputLine.erase(0, count);

	i = inputLine.length() - 1;
	count = 0;

	while (inputLine[i--] == ' ') count++;

	inputLine.erase(inputLine.length() - count, count);
}

bool Controller::ValidCoordinate(coordinate& coord)
{	// Take player input, and if it is valid set the coord variable with them
	string inputLine;
	do {
		getline(cin, inputLine);
	} while (inputLine == "");

	removeWhiteSpace(inputLine);

	stringstream inputStream(inputLine);

	bool fail1 = (inputStream >> coord.x).fail();
	bool fail2 = (inputStream >> coord.y).fail();
	bool fail3 = inputStream.peek() != EOF;

	return !fail1 && !fail2 && !fail3;
}

bool Controller::GetInputCoordinate(coordinate & coord) {

	while (!ValidCoordinate(coord)) { cout << "Wrong input, retry" << endl; };

	coord.x--;
	coord.y--;

	return (coord.x != -1 || coord.y != -1);
}

bool Controller::ValidBool(bool& b) 
{
	// Take player input, and if it is valid set the bool variable with it
	string inputLine;
	do {
		getline(cin, inputLine);
	} while (inputLine == "");

	removeWhiteSpace(inputLine);

	stringstream inputStream(inputLine);

	bool fail1 = (inputStream >> b).fail();
	bool fail2 = inputStream.peek() != EOF;

	return !fail1 && !fail2;
}

bool Controller::GetInputBool(bool& b)
{
	while (!ValidBool(b)) { cout << "Wrong input, retry" << endl; };

	return b;
}

bool Controller::ValidIndex(int& index)
{
	// Take player input, and if it is valid set the index variable with it
	string inputLine;
	do {
		getline(cin, inputLine);
	} while (inputLine == "");

	removeWhiteSpace(inputLine);

	stringstream inputStream(inputLine);

	bool fail1 = (inputStream >> index).fail();
	bool fail2 = inputStream.peek() != EOF;

	return !fail1 && !fail2;
}

bool Controller::GetInputIndex(int& index)
{
	while (!ValidIndex(index)) { cout << "Wrong input, retry" << endl; };

	return !(index== 0);
}

void Controller::ExitGame()
{
	exit(0);
}

View* Controller::GetView()
{
	return v;
}

BotAI* Controller::GetBot()
{
	return bot;
}

void Controller::BoatHit()
{
	// Visual stuff only, boat hit is handeled in Model.
	v->UpdateDisplay();
	v->BoatHit();
}

void Controller::MineHit(coordinate input)
{
	// Logic is handeled in model, mostly visual stuff (must return the number of item hit by the mine)
	int numberOfHit;
	numberOfHit = m->MineExplosion(input);
	v->UpdateDisplay();
	v->ExplosiveTileHit(numberOfHit);
}

void Controller::AngelHit(coordinate input)
{
	v->UpdateDisplay();
	v->AngelTileHit();
	if (m->GetCurrentPlayer()->GetRemainingBoats() == 5) {
		// If the player has all of his ships, create a new one with the desired length

		if (m->GetCurrentPlayer() == m->GetPlayer()) {
			int intTemp = 0;
			bool bTemp = true;
			v->AngelInstruction(2);
			v->ChooseBoat();
			while (intTemp < 2 || intTemp > 6) {

				GetInputIndex(intTemp);
				if (intTemp < 2 || intTemp > 6) {
					v->InvalidLenght();
				}
			}
			v->AskOrientation();
			GetInputBool(bTemp);
			v->AskCoordinateMove();
			GetInputCoordinate(input);

			m->GetGrid()->GetBoatManager()->CreateBoat(intTemp, input, bTemp, m->GetCurrentPlayer());
			v->UpdateDisplay();
		}
		else {
			// Nothing happens, the bot cannot create a new boat...
		}
	}
	else {
		if (m->GetCurrentPlayer() == m->GetPlayer()) {
			// If the player is missing a ship, show which ships are destroy and ask which one to revive, then revive it.

			v->AngelInstruction(1);
			v->AvailableBoats(m->GetCurrentPlayer());
			v->ChooseBoat();
			int intTemp = 0;
			bool valid = true;
			while (valid) {

				GetInputIndex(intTemp);
				if (intTemp < 2 || intTemp > 6) {
					v->InvalidLenght();
				}
				else if (!m->GetGrid()->GetBoatManager()->ValidRessurect(m->GetCurrentPlayer(), intTemp)) {
					v->InvalidRessurect();
				}
				else {
					valid = false;
				}
			}
			m->GetGrid()->GetBoatManager()->RessurectBoat(m->GetCurrentPlayer(), intTemp);
			v->UpdateDisplay();
		}
		else {
			// Bot implementation, go through all boats and if one of them is destroyed, ressurect it
			bool valid = true;
			for(int i = 4; i > -1; i--){
				if (m->GetGrid()->GetBoatManager()->GetBotBoats(i)->destroyed) {
					m->GetGrid()->GetBoatManager()->RessurectBoat(m->GetCurrentPlayer(), i + 2);
					v->UpdateDisplay();
					return;
				}
			}
		}
	}

	v->ShootAgain();
}

void Controller::PowerHit()
{
	v->UpdateDisplay();
	v->PowerTileHit();
}

bool Controller::NoHit(int shots)
{	
	if (m->GetCurrentPlayer()->GetPoweAquired() > shots) {
		// If the player still has power availabe, then he can shoot again
		v->UpdateDisplay();
		v->PowerUse(m->GetCurrentPlayer()->GetPoweAquired() - (shots + 1));
		return true;
	}
	else {
		// Player missed, turn is over
		v->UpdateDisplay();
		v->ShotMissed();
		return false;
	}
}
