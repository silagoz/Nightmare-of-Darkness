#ifndef MENUCOMMANDS_H
#define MENUCOMMANDS_H

#include "stats.h"
#include "rooms.h"


void saveGame(const char* filepath, Player* player, Room* currentRoom);
int loadGame(const char* filepath, Player* player, Room** currentRoom);
void exitGame();

#endif
