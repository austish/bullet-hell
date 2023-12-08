// Start and end menus
#ifndef MENU_H
#define MENU_H
#include "player.h"
#include "ui.h"
#include <string>

// State of game
enum GameState {
    START,
    GAME,
    END
};

void displayStart(Player p);
void displayEnd(Player p);

#endif