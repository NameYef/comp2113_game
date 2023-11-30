#ifndef MENU_H
#define MENU_H
#include <ncurses.h>
#include <vector>
using namespace std;

void menu(string &game_state);
bool customComparator(const vector<string>& a, const vector<string>& b);
#endif //MENU_H
