#ifndef MANAGER_H
#define MANAGER_H
#include "bot.h"
#include "player.h"
#include <iostream>

using namespace std;

class Manager {
public:
    Manager();

    void game_setup(); // pregame setup
    void gameplay(); // actual gameplay
    void run(); // wrap the whole thing together to run in main

private:
    // creating player and player pointer
    Player player;
    Player* p = &player;
    // creating bot and bot pointer
    Bot bot;
    Bot* b = &bot;
    char previous_player; // this will be used to implement the turn based mechanics
    string game_state; // to know what phase of the game is
};




#endif