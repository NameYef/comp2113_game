#include "board.h"
#include <iostream>

using namespace std;


Board::Board() {
    vector<int> size_of_ships = {3, 4, 4, 5, 6, 10};
    for (int i=0; i< size_of_board; i++){
        for (int j=0; j< size_of_board; j++){
            this->state[i][j] = 1;
        }
    }
    // ships is still 3D, elements accessed through ships[i][j][k]
    // if ship part is blown then can remove that element, the remaining percentage can be shown by ships[i].size() / ships[i].capacity()
    for (int i = 0; i < no_of_ships; i++) {
        vector<vector<int>> temp1;
        for (int j = 0; j < size_of_ships[i]; j++) {
            vector<int> temp2;
            temp2.push_back(-1);
            temp2.push_back(-1);
            temp1.push_back(temp2);
        }
        ships.push_back(temp1);
    }
}

bool Board::ship_empty() {
    for (auto& i : ships) {
        if (! i.empty()) {
            return false;
        }
    }
    return true;
}

const vector<vector<vector<int>>> Board::get_ships() const {
    return ships;
}


int Board::ship_left() {
    int count = 0;
    for (auto i : ships) {
        if (i.empty()) {
            count++;
        }
    }
    return (no_of_ships - count);
}




void Board::draw(WINDOW* win) {
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    int game_row = 2;
    mvwprintw(win, 1, 1, "   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+");
    for (int i = 0; i < size_of_board; i++) {

        int column = 1;
        // handling the row name
        char row_name = 'A' + i;
        mvwprintw(win, game_row, 1, " %c |", row_name);
        column += 4;
        
        for (int j = 0; j < size_of_board; j++) {

            switch (state[j][i]) {
                case -1:
                    mvwprintw(win, game_row, column, " ? |");
                    column += 4;
                    break;
                case 1:
                    mvwprintw(win, game_row, column, "   |");
                    column += 4;
                    break;
                case 2:
                    mvwprintw(win, game_row, column, "███|");
                    column += 4;
                    break;
                case 3:
                    mvwprintw(win, game_row, column, " + |");
                    column += 4;
                    break;
                case 4:
                    mvwprintw(win, game_row, column, " X |");
                    column += 4;
                    break;
                case 5:
                    mvwprintw(win, game_row, column, "█X█");
                    column += 4;
                    break;
            }

        }

        mvwprintw(win, game_row + 1, 1, "   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+");
        game_row += 2;
        
    }
    wrefresh(win);
    refresh();






































    // //first line
    // cout << "   ";
    // for (int i=0; i<size_of_board; i++){
    //     cout << "+---";
    // }
    // cout << "+" << endl;

    // // iterate through each slot and its underline(?)
    // for (int y=0; y<Board::size_of_board; y++){
    //     // alphabet label
    //     char c = 'A'+y;
    //     cout << " " << c << " "; 

    //     for (int x=0; x<Board::size_of_board; x++){
    //         // occ and bombed
    //         if (this->state[x][y] == 4){
    //             cout << "| O ";
    //         }
    //         // bombed but NOT occ
    //         else if (this->state[x][y] == 3){
    //             cout << "| X ";
    //         }
    //         // if revealed
    //         else if (this->state[x][y] > 0){
    //             // if occ
    //             if (this->state[x][y] == 2){
    //                 if (x>0 && this->state[x-1][y] == 2){
    //                     // if there is a revealed occ on the left, print this
    //                     cout << "████";
    //                 }
    //                 else {
    //                     // ifthere is NOT a revealed occ on the left, print this
    //                     cout << "|███";
    //                 }
    //             }
    //             // not occ
    //             else {
    //                 cout << "|   "; 
    //             }
    //         }
    //         // unrevealed
    //         else {
    //             cout << "| ? ";
    //         }
    //     }
    //     cout << "|" <<endl;

    //     cout << "   " ;
    //     for (int x=0; x<Board::size_of_board; x++){
    //         // if this slot and below are both revealed occ
    //         if (this->state[x][y] == 2 && y<(Board::size_of_board-1) && this->state[y+1][x] == 2){
    //             // if slot to the left is revealed occ
    //             if (x>0 && this->state[x-1][y] == 2){
    //                 cout << "████";
    //             }
    //             else {
    //                 cout << "+███";
    //             }
    //         }
    //         else {
    //             cout << "+---";
    //         }
    //     }
    //     cout << "+" << endl;
    // }
    
    // // number label. ? : to make sure align
    // cout << "   ";
    // for (int i=1; i<=Board::size_of_board; i++){
    //     cout << " " << i << (i/10>0 ? " " : "  "); 
    // }
    // cout << endl;
}

