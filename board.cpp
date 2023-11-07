#include "board.h"
#include <iostream>

using namespace std;


Board::Board() {
    for (int i=0; i< Board::size_of_board; i++){
            for (int j=0; j< Board::size_of_board; j++){
                this->state[i][j] = 1;
            }
        }
}

void Board::draw() {
    //first line
    cout << "   ";
    for (int i=0; i<Board::size_of_board; i++){
        cout << "+---";
    }
    cout << "+" << endl;

    // iterate through each slot and its underline(?)
    for (int y=0; y<Board::size_of_board; y++){
        // alphabet label
        char c = 'A'+y;
        cout << " " << c << " "; 

        for (int x=0; x<Board::size_of_board; x++){
            // occ and bombed
            if (this->state[y][x] == 4){
                cout << "| O ";
            }
            // bombed but NOT occ
            else if (this->state[y][x] == 3){
                cout << "| X ";
            }
            // if revealed
            else if (this->state[y][x] > 0){
                // if occ
                if (this->state[y][x] == 2){
                    if (x>0 && this->state[y][x-1] == 2){
                        // if there is a revealed occ on the left, print this
                        cout << "████";
                    }
                    else {
                        // ifthere is NOT a revealed occ on the left, print this
                        cout << "|███";
                    }
                }
                // not occ
                else {
                    cout << "|   "; 
                }
            }
            // unrevealed
            else {
                cout << "| ? ";
            }
        }
        cout << "|" <<endl;

        cout << "   " ;
        for (int x=0; x<Board::size_of_board; x++){
            // if this slot and below are both revealed occ
            if (this->state[y][x] == 2 && y<(Board::size_of_board-1) && this->state[y+1][x] == 2){
                // if slot to the left is revealed occ
                if (x>0 && this->state[y][x-1] == 2){
                    cout << "████";
                }
                else {
                    cout << "+███";
                }
            }
            else {
                cout << "+---";
            }
        }
        cout << "+" << endl;
    }
    
    // number label. ? : to make sure align
    cout << "   ";
    for (int i=1; i<=Board::size_of_board; i++){
        cout << " " << i << (i/10>0 ? " " : "  "); 
    }
    cout << endl;
}
