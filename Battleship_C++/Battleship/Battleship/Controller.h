#pragma once
#include "Model.h"
#include "View.h"
#include "BotAI.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Coordinate.h"

class Controller
{
public:
	// PUBLIC FUNCTION -------------------
	Controller(class Model* model, class View* view);
	void Setup();
	void Menu();
	void PlayGame();
	void removeWhiteSpace(std::string& inputLine);
	bool ValidCoordinate(struct coordinate& coord);
	bool GetInputCoordinate(struct coordinate& coord);
	bool ValidBool(bool& b);
	bool GetInputBool(bool& b);
	bool ValidIndex(int& index);
	bool GetInputIndex(int& index);
	void ExitGame();
	

	// Getters and Setters
	class BotAI* GetBot();
	class View* GetView();

private:
	// PRIATE VARIABLES
	class Model* m;
	class View* v;
	class BotAI* bot;

	// PRIVATE FUNCTION
	void BoatHit();
	void MineHit(coordinate input);
	void AngelHit(coordinate input);
	void PowerHit();
	bool NoHit(int shots);
};

