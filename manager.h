#ifndef MANAGER_H
#define MANAGER_H
#include "bot.h"
#include "player.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

class Manager {
public:
    Manager();
    ~Manager();
    void game_setup(); // pregame setup
    void gameplay(); // actual gameplay
    void switch_player();
    bool check_win();
    void draw_status(WINDOW* win, char user);
    void run(); // wrap the whole thing together to run in main
    string game_state; // to know what phase of the game is

private:
    // creating player and bot pointer
    Player* player;
    Bot* bot;
    
    
    char previous_player; // this will be used to implement the turn based mechanics
    int ymax;
    int xmax;
};




#endif