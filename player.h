#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <ncurses.h>

class Player : public Board {

public:
    // methods for set up
    bool setup(); // returns true if confirmed quit
    
    // method for gameplay
    void bot_attack();
    void bot_at_0(mt19937& gen);
    void bot_at_1(mt19937& gen);
    void bot_at_2(mt19937& gen);
    void bot_at_3(mt19937& gen);
    void bot_at_4(mt19937& gen);
    void bot_at_neg1(mt19937& gen);
    void bot_at_neg2(mt19937& gen);
    void bot_at_neg3(mt19937& gen);
    void bot_at_neg4(mt19937& gen);

private:
    void state_set(char& direction, int& head_x, int& head_y, int& no_of_blocks, int state_no);
    void ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks);
    bool overlap(char& direction, int& head_x, int& head_y, int& no_of_blocks);
    
    bool bot_overlap(int x, int y);
    void hit(int cursor_x, int cursor_y);

    int bot_attempts = 0;
    int coordinate_x = 0;
    int coordinate_y = 0;
    int original_x = 0;
    int original_y = 0;




};




#endif 
