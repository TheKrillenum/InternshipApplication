#include "BotStrategy.h"



void EasyStrategy::Shoot(coordinate& coord) {
	
	bool valid = true;
	int Row = 0;
	int Column = 0;

	while (valid) {
		int Row = rand() % 10;
		int Column = rand() % 10;
		
		if (!m->GetGrid()->GetBotGrid().hist[Row][Column]->GetHit()) {
			valid = false;
			coord.x = Row;
			coord.y = Column;
		}
	}
}

//bool MediumHardStrategy::NextShot(coordinate& coord)			DEPRECATED - Didn't take into account.... to many things. Like mines.
//{
//	coordinate output;
//
//	// Case where the bot only discovered one tile of the boat but doesn't know it's orientation
//	if ((m->GetGrid()->GetBotGrid().hist[target->x + 1][target->y]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x + 1][target->y]->GetBoat() != nullptr))
//		|| (m->GetGrid()->GetBotGrid().hist[target->x - 1][target->y]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x - 1][target->y]->GetBoat() != nullptr))
//		|| (m->GetGrid()->GetBotGrid().hist[target->x][target->y + 1]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x][target->y + 1]->GetBoat() != nullptr)) 
//		|| (m->GetGrid()->GetBotGrid().hist[target->x][target->y - 1]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x][target->y - 1]->GetBoat() != nullptr))	) {
//			if (!m->GetGrid()->GetBotGrid().hist[target->x + 1][target->y]->GetHit()) {
//				coord = { target->x + 1, target->y };
//				return true;
//			}
//			else if (!m->GetGrid()->GetBotGrid().hist[target->x - 1][target->y]->GetHit()) {
//				coord = { target->x - 1, target->y };
//				return true;
//			}
//			else if (!m->GetGrid()->GetBotGrid().hist[target->x][target->y + 1]->GetHit()) {
//				coord = { target->x, target->y + 1 };
//				return true;
//			}
//			else if (!m->GetGrid()->GetBotGrid().hist[target->x][target->y - 1]->GetHit()) {
//				coord = { target->x, target->y - 1 };
//				return true;
//			}
//	}
//
//	// Case where we know at least it's orientation
//
//	// vertical orientation
//	if ((m->GetGrid()->GetBotGrid().hist[target->x + 1][target->y]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x + 1][target->y]->GetBoat() != nullptr))
//		|| (m->GetGrid()->GetBotGrid().hist[target->x - 1][target->y]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x - 1][target->y]->GetBoat() != nullptr))) {
//			if (!m->GetGrid()->GetBotGrid().hist[target->x + 1][target->y]->GetHit()) {
//				coord = { target->x + 1 , target->y };
//				return true;
//			}
//			else if (!m->GetGrid()->GetBotGrid().hist[target->x - 1][target->y]->GetHit()) {
//				coord = { target->x - 1 , target->y };
//				return true;
//			}
//			else if (m->GetGrid()->GetPlayerGrid().arr[target->x + 1][target->y]->GetBoat() != nullptr) {
//				// Go toward x++ until shootable tile
//				for (int i = 0; i < 4; i++) {
//					if()
//					if (!m->GetGrid()->GetBotGrid().hist[target->x + 2 + i][target->y]->GetHit()) {
//						coord = { target->x + 2 + i , target->y };
//						return true;
//					}
//				}
//			}
//			else if (m->GetGrid()->GetPlayerGrid().arr[target->x + 1][target->y]->GetBoat() != nullptr) {
//
//			}
//	}
//	else if ((m->GetGrid()->GetBotGrid().hist[target->x][target->y + 1]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x][target->y + 1]->GetBoat() != nullptr))
//		|| (m->GetGrid()->GetBotGrid().hist[target->x][target->y + 1]->GetHit() && (m->GetGrid()->GetPlayerGrid().arr[target->x][target->y + 1]->GetBoat() != nullptr))) {
//			
//	}
//
//	coord = { 0,0 };
//	return false;
//}

void MediumHardStrategy::Shoot(coordinate& coord) {
	
	//if (target != nullptr && NextShot(coord)) {
	//	return;
	//}
	bool valid = true;
	int Row = 0;
	int Column = 0;

	while (valid) {
		int Row = rand() % 10;
		int Column = rand() % 10;

		if (!m->GetGrid()->GetBotGrid().hist[Row][Column]->GetHit()) {
			valid = false;
			coord.x = Row;
			coord.y = Column;
		}
	}
}

BotStrategy::BotStrategy(Model* model)
{
	m = model;
	target = nullptr;
}
