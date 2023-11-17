#include "manager.h"
#include <iostream>

using namespace std;


Manager::Manager() {
    this->player = Player();
    this->bot = Bot();
    this->game_state = "pregame";
}

void Manager::game_setup() {
    this->b->setup();
    this->p->setup();

    this->game_state = "game";
    return;
}

void Manager::gameplay() {

    int input;
    do {
    printw("press up_arrow to quit\n");
    refresh();

    } while ((input = getch()) != KEY_UP);

    game_state = "quit";
    return;
}

void Manager::run() {
    if (this->game_state == "pregame") {
        this->game_setup();
    }
    else if (this->game_state == "game") {
        this->gameplay();
    }
    return;
}