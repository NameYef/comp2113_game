#include "bot.h"
#include <iostream>
#include <random>
#include <iterator>
using namespace std;

// check if the ship placement is valid by taking the direction, head block coords and the length of the ship into consideration
bool Bot::valid(char direction, int head_x, int head_y, int no_of_blocks) {
    if (direction == 'h') { // if direction is horiontal
        if (head_x + no_of_blocks - 1 >= size_of_board) { // if the block after the head is outside of the board
            return false;
        }
    }
    else if (direction == 'v') { // vertical
        if (head_y + no_of_blocks - 1 >= size_of_board) { // if the block after the head is outside of the board
            return false;
        }
    }
    return true;

}

// check if the ship placement overlaps the ships already placed, checked using direction, head block coords and length of the ship
bool Bot::overlap(char direction, int head_x, int head_y, int no_of_blocks) {
    if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x + i][head_y] == 2) { // state is 2 when ship occupied the spot
                return true;
            }
        }
    }
    else if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x][head_y + i] == 2) { // state is 2 when ship occupied the spot
                return true;
            }
        }
    }
    return false; // return false when the placement didnt overlap 
}


// conveniently set the required coords that include the length of provided ship to be the state provided
void Bot::state_set(char direction, int head_x, int head_y, int no_of_blocks, int state_no) {
    if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
                state[head_x][head_y + i] = state_no; // changing the state which makes the ship visible in the board
        }
    }
    else if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
            state[head_x + i][head_y] = state_no; // changing the state which makes the ship visible in the board
        }
    }
}


// storing the coords into the ships array accordingly
void Bot::ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks) {
    if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
           ships[current_ship][i][0] = head_x; // ship[i][j][0] is the x coord of a ship block
           ships[current_ship][i][1] = head_y + i; //ship[i][j][1] is the x coord of a ship block
        }
    }
    else if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
           ships[current_ship][i][0] = head_x + i; // ship[i][j][0] is the x coord of a ship block
           ships[current_ship][i][1] = head_y; //ship[i][j][1] is the x coord of a ship block
        }
    }

}

// responsible for the whole bot set up, which uses the methods above for condition checking and coords storing
void Bot::setup() {
    // // placeholder setup
    // cout << "bot setup finished" << endl;
    // return;

    // generate random variables
    random_device rd;
    mt19937 gen(rd());

    // necessary variables initalised here
    char directions[2] = {'h', 'v'};
    char direction;
    int current_ship = 0;
    int head_x;
    int head_y;
    int no_of_blocks;

    // run when not all ships have been set up
    while (current_ship < no_of_ships) {
        uniform_int_distribution<> dir(0,1); // to generate random directions
        uniform_int_distribution<> intd(0, size_of_board - 1); // generate random coords
        direction = directions[dir(gen)];
        no_of_blocks = ships[current_ship].capacity();

        head_x = intd(gen);
        head_y = intd(gen);

        // if the coords of the head block are not valid, generate until valid
        while ((! valid(direction, head_x, head_y, no_of_blocks)) || overlap(direction, head_x, head_y, no_of_blocks)) {
            direction = directions[dir(gen)];
            head_x = intd(gen);
            head_y = intd(gen);
        }
        // if valid then change the state and store the coords
        state_set(direction, head_x, head_y, no_of_blocks, 2);
        ship_set(direction, current_ship, head_x, head_y, no_of_blocks);

        // move on to the next ship
        current_ship++;


    }

    // WINDOW* win = newwin(41, 83, 0, 0);
    // refresh();
    // this->draw(win);
    // getch();
    // werase(win);
    // wrefresh(win);
    // delwin(win);
    // clear();
    // move(0, 0);

    // after set up is complete, make the board blank again for gameplay later
    for (int i=0; i< size_of_board; i++){
        for (int j=0; j< size_of_board; j++){
            state[i][j] = 1;
        }
    }
    return;

}

// takes the coords player wants to attack, return true if one of the ships block has the same coords and delete that ship block from ships vector
bool Bot::hit(int cursor_x, int cursor_y) {
    for (auto& i : ships) {
        for (vector<vector<int>>::iterator j = i.begin(); j != i.end(); j++) {
            if (((*j)[0] == cursor_x) && ((*j)[1] == cursor_y)) {
                i.erase(j);
                return true;
            }
        };
    }
    return false;

}

// responsible for the whole player attack phase, takes a bool paused to remember it is still player's turn after pausing
bool Bot::player_attack(WINDOW* win, bool& paused) {
    bool attacked = false; // records successfully attacked or not
    int input;

    // if not successfully attacked, run this
    while (! attacked) {
        prev_state = state[attack_cursor_x][attack_cursor_y]; // store the previous state of the block to restore when cursor moves

        state[attack_cursor_x][attack_cursor_y] = 3; // shows the cursor

        this->draw(win); // then draw the board to let player see thee cursor
        input = getch(); // takes an input
        refresh();

        switch (input) {
                case KEY_UP:
                    // move the ship upward and change the state of board back to 1 for the current location
                    if (!(attack_cursor_y - 1 < 0)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state; // to show the previous state of the position once cursor moves away from it
                        after_state = state[attack_cursor_x][attack_cursor_y - 1]; // stores the state one block up
                        attack_cursor_y--;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state; // to show the previous state of the position once cursor moves away from it
                    break;
                case KEY_DOWN:
                    // move the ship down
                    if (!(attack_cursor_y + 1 >= size_of_board)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state;
                        after_state = state[attack_cursor_x][attack_cursor_y + 1]; // stores the state one block down
                        attack_cursor_y++;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
                case KEY_LEFT:
                    // move the ship left
                    if (!(attack_cursor_x - 1 < 0)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state;
                        after_state = state[attack_cursor_x - 1][attack_cursor_y]; // stores the state one block left
                        attack_cursor_x--;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
                case KEY_RIGHT:
                    // move the ship right
                    if (!(attack_cursor_x + 1 >= size_of_board)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state;
                        after_state = state[attack_cursor_x + 1][attack_cursor_y]; // stores the state one block right
                        attack_cursor_x++;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
                case '\n':  //'n' means enter key
                    if (after_state == 1) {
                        if (hit(attack_cursor_x, attack_cursor_y)) { // if hit a ship
                            state[attack_cursor_x][attack_cursor_y] = 5; // show destroyed ship block
                            after_state = 5; // for the below 2 else if statements to work
                        }
                        else {
                            state[attack_cursor_x][attack_cursor_y] = 4; // show missed state
                            after_state = 4; // for the below 2 else if statements to work
                            
                        }
                        attacked = true;
                        break;
                    }
                    // the below 2 else if statements are to make sure the player cannot attack the same block
                    else if (after_state == 4) {
                        state[attack_cursor_x][attack_cursor_y] = 4;
                        break;
                    }
                    else if (after_state == 5) {
                        state[attack_cursor_x][attack_cursor_y] = 5;
                        break;
                    }
                case 27: // 27 means escape
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    if (this->confirmQuit()){
                        return true;
                    }
                    else {
                        paused = true;
                        return false;    
                    }
                default:
                    // make sure typing other keys don't mess up the state of the board
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
            
        }
        
    }
    return false;
}


