#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <ncurses.h>

class Player : public Board {

public:
    void setup();
    void state_set(char& direction, int& head_x, int& head_y, int& no_of_blocks, int state_no);


private:




};




#endif 