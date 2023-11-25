#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <ncurses.h>

class Player : public Board {

public:
    // methods for set up
    void setup();
    
    // method for gameplay
    void gameplay(int& input_x, int& input_y, char& direction);

private:
    void state_set(char& direction, int& head_x, int& head_y, int& no_of_blocks, int state_no);
    void ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks);
    bool overlap(char& direction, int& head_x, int& head_y, int& no_of_blocks);

    void state_update(int& input_x, int& input_y, bool& hit_ship);
    void ship_specific(int& input_x, int& input_y, char& direction);


};




#endif 
