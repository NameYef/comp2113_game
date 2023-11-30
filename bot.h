#ifndef BOT_H
#define BOT_H
#include "board.h"
#include <ncurses.h>

class Bot : public Board {

public:
    // method for set up
    void setup();
    bool player_attack(WINDOW* win, bool& paused);
    // method for gameplay
    

private:
    // private methods used in setup and attack
    bool valid(char direction, int head_x, int head_y, int no_of_blocks);
    bool overlap(char direction, int head_x, int head_y, int no_of_blocks);
    bool hit(int cursor_x, int cursor_y);
    void state_set(char direction, int head_x, int head_y, int no_of_blocks, int state_no);
    void ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks);

    // private variables
    int attack_cursor_x = (size_of_board - 1) / 2;
    int attack_cursor_y = (size_of_board - 1) / 2;
    int prev_state;
    int after_state = 1;
};




#endif 