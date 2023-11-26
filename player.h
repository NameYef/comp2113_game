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
    void bot_attack(int& bot_attempts, int& coordinate_x, int& coordinate_y, int& original_x, int& original_y);

private:
    void hit(int cursor_x, int cursor_y);
    void state_set(char& direction, int& head_x, int& head_y, int& no_of_blocks, int state_no);
    void ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks);
    bool overlap(char& direction, int& head_x, int& head_y, int& no_of_blocks);
    bool bot_overlap(int x, int y);

    void state_update(int& input_x, int& input_y, bool& hit_ship);
    void ship_specific(int& input_x, int& input_y, char& direction);


};




#endif 
