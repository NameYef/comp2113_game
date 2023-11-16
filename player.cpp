#include "player.h"
#include <iostream>
#include <string>
using namespace std;

void Player::setup() {
    // placeholder setup
    // string a;
    // cout << "press enter to finish player setup" << endl;
    // getline(cin, a);

    WINDOW* win = newwin(41, 83, 0, 0);
    refresh();
    
    this->draw(win);

    mvprintw(22, 100, "type anything to complete set up");
    refresh();
    getch();

    werase(win);
    wrefresh(win);
    delwin(win);
    clear();
    move(0, 0);
    // refresh();
    printw("set up finished\n");
    refresh();
    return;
}