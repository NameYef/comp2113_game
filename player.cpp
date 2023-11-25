#include "player.h"
#include <iostream>
#include <string>
using namespace std;

// set the board to certain state to represent the location of ships
void Player::state_set(char& direction, int& head_x, int& head_y, int& no_of_blocks, int state_no) {
    int tail;
    if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x][head_y + i] != 2) {
                state[head_x][head_y + i] = state_no;
            }
        }
    }
    else if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x + i][head_y] != 2) {
            state[head_x + i][head_y] = state_no;
            }
        }
    }
}

// check if the current ship location overlaps with already occupied slots, state 2 means occupied
bool Player::overlap(char& direction, int& head_x, int& head_y, int& no_of_blocks) {
    if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x][head_y + i] == 2) {
                return true;
            }
            
        }
    }
    else if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x + i][head_y] == 2) {
                return true;
            }
        }
    }
    return false;
}

// add the coordinates to the ships vector for each ship
void Player::ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks) {
    if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
           ships[current_ship][i][0] = head_x;
           ships[current_ship][i][1] = head_y + i;
        }
    }
    else if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
           ships[current_ship][i][0] = head_x + i;
           ships[current_ship][i][1] = head_y;
        }
    }

}

// update the state of the board after an attack
void Player::state_update(int& input_x, int& input_y, char& direction, bool& hit_ship) {
     if (state[input_x][input_y] == 2) {
        state[input_x][input_y] = -1; // assume -1 is the hit indicator
        hit_ship = true;
     }
     if (state[input_x][input_y] == 0) {
        state[input_x][input_y] = -2; // assume -2 is the reveal and hit indicator
        hit_ship = false;
     }
}

void Player::setup() {

    // create new window for set up
    WINDOW* win = newwin(41, 83, 0, 0);
    refresh();

    // variables only used in this method
    int current_ship = 0;
    char direction = 'v';
    int input;
    bool ship_set = false;

    // a while loop to place every ship
    while (current_ship < no_of_ships) {

        // getting the head coordinates of the ship
        int head_x = (size_of_board - 1) / 2;
        int head_y = (size_of_board - 1) / 2;

        // the size of the ship
        int no_of_blocks = ships[current_ship].capacity();

        // a flag to know whether the ship is sucessfully placed
        ship_set = false;

        // while loop to keep prompting the player to place the ship in a valid spot
        while (!ship_set) {

            // set the state to 3 for the ship location to let player see where the ship currently is
            this->state_set(direction, head_x, head_y, no_of_blocks, 3);

            // input to move the ship
            this->draw(win);
            input = getch();
            refresh();


            switch (input) {
                case KEY_UP:
                    // move the ship upward and change the state of board back to 1 for the current location
                    if (!(head_y - 1 < 0)) {
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_y--;
                    }
                    break;
                case KEY_DOWN:
                    // move the ship down
                    if (!((head_y + no_of_blocks >= size_of_board && direction == 'v') || (head_y + 1 >= size_of_board && direction == 'h'))) {
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_y++;
                    }
                    break;
                case KEY_LEFT:
                    // move the ship left
                    if (!(head_x - 1 < 0)) {
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_x--;
                    }
                    break;
                case KEY_RIGHT:
                    // move the ship right
                    if (!(head_x + 1 >= size_of_board)) {
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_x++;
                    }
                    break;
                case 32: // 32 means spacebar
                    // change rotation
                    if (!(head_x + no_of_blocks - 1 >= size_of_board || head_y + no_of_blocks - 1 >= size_of_board)) {
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    direction = (direction == 'h') ? 'v' : 'h';
                    }
                    break;
                case '\n':  //'n' means enter key
                    // check valid or not, if valid then set state to 2 and store the coords and break this loop
                    if (!this->overlap(direction, head_x, head_y, no_of_blocks)) {
                        this->state_set(direction, head_x, head_y, no_of_blocks, 2);
                        this->ship_set(direction, current_ship, head_x, head_y, no_of_blocks);
                        
                        ship_set = true;
                        break;
                    }
                    else {
                        // mvprintw(25, 100, "Invalid move! Choose another position.");
                        break;
                    }
            }
        }
        // move on to the next ship
        current_ship++;

    }


    //erase the window when finish set up
    werase(win);
    wrefresh(win);
    delwin(win);
    clear();
    move(0, 0);
    // refresh();
    printw("set up finished\n");
    refresh();
    return;
}

