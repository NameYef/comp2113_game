#include "player.h"
#include <iostream>
#include <string>
using namespace std;

void Player::state_set(char& direction, int& head_x, int& head_y, int& no_of_blocks, int state_no) {
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


// HAVE NOT IMPLEMENT CHECK VALID INPUT, STORE SHIP COORDINATE


void Player::setup() {
    // placeholder setup
    // string a;
    // cout << "press enter to finish player setup" << endl;
    // getline(cin, a);

    WINDOW* win = newwin(41, 83, 0, 0);
    refresh();
    int current_ship = 0;
    char direction = 'v';
    int input;
    while (current_ship < no_of_ships) {
        int head_x = (size_of_board - 1) / 2;
        int head_y = (size_of_board - 1) / 2;
        int no_of_blocks = ships[current_ship].capacity();

        do {
            
            this->state_set(direction, head_x, head_y, no_of_blocks, 3);

            this->draw(win);
            mvprintw(22, 100, "headx is %d, head y is %d", head_x, head_y);
            mvprintw(23, 100, "last key press = %d", input);
            input = getch();
            refresh();

            switch (input) {
                case KEY_UP:
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_y--;
                    break;
                case KEY_DOWN:
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_y++;
                    break;
                case KEY_LEFT:
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_x--;
                    break;
                case KEY_RIGHT:
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    head_x++;
                    break;
                case 32: // 32 means spacebar
                    this->state_set(direction, head_x, head_y, no_of_blocks, 1);
                    direction = (direction == 'h') ? 'v' : 'h';
                    break;
            }
            
        
        } while (input != '\n');
        
        current_ship++;

    }





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