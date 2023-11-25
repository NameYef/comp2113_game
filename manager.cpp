#include "manager.h"
#include <iostream>

using namespace std;

// Constructor
Manager::Manager() {
    player = new Player();
    bot = new Bot();
    game_state = "pregame";
    previous_player = 'b';
}

// Destructor
Manager::~Manager() {
    delete player;
    delete bot;
}

void Manager::game_setup() {
    bot->setup();
    player->setup();

    game_state = "game";
    return;
}

void Manager::switch_player() {
    previous_player = (previous_player == 'p') ? 'b' : 'p';
}

bool Manager::check_win() {
    // take both bot and player ship check
    // if anyone wins then return True
}
void Manager::gameplay() {
// implement turn based fundamental gameplay here
    // if no one wins then continue this loop
    while (! check_win()) {
        if (previous_player == 'b') {
            // player's turn to attack

        }
        else if (previous_player == 'p') {
            // bot's turn to attack
        }

        switch_player();

    }

    // previous_player won, type anything then can return to menu
    // below here add a window to tell player who won, and also store the info of this game into a file




    getch();
    return;
}

void Manager::run() {
    if (game_state == "menu") {
        // menu stuff
    }
    else if (game_state == "pregame") {
        game_setup();
    }
    else if (game_state == "game") {
        gameplay();
    }
    return;
}