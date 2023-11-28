
#include <ncurses.h>
using namespace std;

#ifndef MENU_H
#define MENU_H
void menu(string &game_state);
bool customComparator(const vector<string>& a, const vector<string>& b);
#endif //MENU_H
