#ifndef BOARDV_H
#define BOARDV_H
#include <vector>
#include <ncurses.h>
#include <fstream>
#include <cstring>
using namespace std;

class Board {
public:
    Board(); // constructor
    void draw(WINDOW* win);
    void deallocate();
    bool ship_empty();
    const vector<vector<vector<int>>> get_ships() const;
    static constexpr int size_of_board = 19;
    static constexpr int no_of_ships = 6;
    void store_state(string fname);
    void load_state(string fname);
    double accuracy();
    double score();

protected:
// variables
    // instance variables 
    vector<vector<vector<int>>> ships;
    int state[size_of_board][size_of_board];
    bool confirmQuit();
};


#endif
