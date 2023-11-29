#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <ncurses.h>
#include <random>

class Player : public Board {

public:
    // methods for set up
    bool setup(); // returns true if confirmed quit
    
    // method for gameplay
    void bot_attack();
    //methods used in bot_attack function
    void bot_attempts_0(mt19937& gen);
    void bot_attempts_1(mt19937& gen);
    void bot_attempts_2(mt19937& gen);
    void bot_attempts_3(mt19937& gen);
    void bot_attempts_4(mt19937& gen);
    void bot_attempts_neg1(mt19937& gen);
    void bot_attempts_neg2(mt19937& gen);
    void bot_attempts_neg3(mt19937& gen);
    void bot_attempts_neg4(mt19937& gen);

private:
    void state_set(char& direction, int& head_x, int& head_y, int& no_of_blocks, int state_no);
    void ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks);
    bool overlap(char& direction, int& head_x, int& head_y, int& no_of_blocks);
    
    bool bot_overlap(int x, int y);
    void hit(int cursor_x, int cursor_y);

    //bot_attempts variable is needed for giving directions to bot in bot_attack function
    int bot_attempts = 0;
    //coordinate_x and coordinate_y are used by bot_attack function if it has located a cell with a part of the ship inside
    int coordinate_x = 0;
    int coordinate_y = 0;
    // original_x and original_y coordinates are used in bot_attack function to store
    // the coordinates of x and y when bot_attack finds at least 1 cell with a part of the ship inside
    // original_x and original_y will store the coordinates of that cell
    int original_x = 0;
    int original_y = 0;




};




#endif 
