#include "bot.h"
#include <iostream>
#include <random>
#include <iterator>
using namespace std;

bool Bot::valid(char direction, int head_x, int head_y, int no_of_blocks) {
    if (direction == 'h') {
        if (head_x + no_of_blocks - 1 >= size_of_board) {
            return false;
        }
    }
    else if (direction == 'v') {
        if (head_y + no_of_blocks - 1 >= size_of_board) {
            return false;
        }
    }
    return true;

}

bool Bot::overlap(char direction, int head_x, int head_y, int no_of_blocks) {
    if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x + i][head_y] == 2) {
                return true;
            }
        }
    }
    else if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
            if (state[head_x][head_y + i] == 2) {
                return true;
            }
        }
    }
    return false;
}

void Bot::state_set(char direction, int head_x, int head_y, int no_of_blocks, int state_no) {
    if (direction == 'v') {
        for (int i = 0; i < no_of_blocks; i++) {
                state[head_x][head_y + i] = state_no;
        }
    }
    else if (direction == 'h') {
        for (int i = 0; i < no_of_blocks; i++) {
            state[head_x + i][head_y] = state_no;
        }
    }
}

void Bot::ship_set(char direction, int current_ship, int head_x, int head_y, int no_of_blocks) {
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


void Bot::setup() {
    // // placeholder setup
    // cout << "bot setup finished" << endl;
    // return;

    random_device rd;
    mt19937 gen(rd());

    char directions[2] = {'h', 'v'};

    char direction;
    int current_ship = 0;
    int head_x;
    int head_y;
    int no_of_blocks;

    while (current_ship < no_of_ships) {
        uniform_int_distribution<> dir(0,1);
        uniform_int_distribution<> intd(0, size_of_board);
        direction = directions[dir(gen)];
        no_of_blocks = ships[current_ship].capacity();

        head_x = intd(gen);
        head_y = intd(gen);
        while ((! valid(direction, head_x, head_y, no_of_blocks)) || overlap(direction, head_x, head_y, no_of_blocks)) {
            direction = directions[dir(gen)];
            head_x = intd(gen);
            head_y = intd(gen);
        }
        state_set(direction, head_x, head_y, no_of_blocks, 2);
        ship_set(direction, current_ship, head_x, head_y, no_of_blocks);

        current_ship++;


    }

    for (int i=0; i< size_of_board; i++){
        for (int j=0; j< size_of_board; j++){
            state[i][j] = 1;
        }
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
    return;

}


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
bool Bot::player_attack(WINDOW* win) {
    bool attacked = false;
    int input;
    while (! attacked) {
        prev_state = state[attack_cursor_x][attack_cursor_y];

        state[attack_cursor_x][attack_cursor_y] = 3;

        this->draw(win);
        // mvprintw(47,40,"after %d", after_state);
        // mvprintw(49,40,"prev %d", prev_state);
        input = getch();
        refresh();

        switch (input) {
                case KEY_UP:
                    // move the ship upward and change the state of board back to 1 for the current location
                    if (!(attack_cursor_y - 1 < 0)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state;
                        after_state = state[attack_cursor_x][attack_cursor_y - 1];
                        attack_cursor_y--;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
                case KEY_DOWN:
                    // move the ship down
                    if (!(attack_cursor_y + 1 >= size_of_board)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state;
                        after_state = state[attack_cursor_x][attack_cursor_y + 1];
                        attack_cursor_y++;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
                case KEY_LEFT:
                    // move the ship left
                    if (!(attack_cursor_x - 1 < 0)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state;
                        after_state = state[attack_cursor_x - 1][attack_cursor_y];
                        attack_cursor_x--;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
                case KEY_RIGHT:
                    // move the ship right
                    if (!(attack_cursor_x + 1 >= size_of_board)) {
                        state[attack_cursor_x][attack_cursor_y] = prev_state;
                        after_state = state[attack_cursor_x + 1][attack_cursor_y];
                        attack_cursor_x++;
                        break;
                    }
                    state[attack_cursor_x][attack_cursor_y] = prev_state;
                    break;
                case '\n':  //'n' means enter key
                    if (after_state == 1) {
                        if (hit(attack_cursor_x, attack_cursor_y)) {
                            state[attack_cursor_x][attack_cursor_y] = 5;
                            after_state = 5;
                        }
                        else {
                            state[attack_cursor_x][attack_cursor_y] = 4;
                            after_state = 4;
                            
                        }
                        attacked = true;
                        break;
                    }
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
                        return false;    
                    }
            
        }
    }

}


