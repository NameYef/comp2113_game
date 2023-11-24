#ifndef BOT_H
#define BOT_H
#include "board.h"
#include <ncurses.h>

class Bot : public Board {

public:
    // method for set up
    void setup();

    // method for gameplay
    

private:
    bool valid(char direction, int head_x, int head_y, int no_of_blocks);
    bool overlap(char direction, int head_x, int head_y, int no_of_blocks);
    void state_set(char direction, int head_x, int head_y, int no_of_blocks, int state_no);
    void ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks);
};




#endif 