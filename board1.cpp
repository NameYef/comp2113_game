/*
key functions: 
Board.init()
Board.draw()
Board.deallocate()        !! rmb to deallocate at the end cuz used dynamic arr
Board.updateOccupied()
Board.bomb(x,y)         --> return T when not revealed/ bombed, else F
*/

#include "board.h"
#include <iostream>

using namespace std;

const int size_of_board = 19;
const int no_of_ships = 6;
int size_of_ships[no_of_ships] = {3, 4, 4, 5, 6, 10};

struct Board{
    // make list of ship coords
    int (*ships[no_of_ships])[2];
    
    /*
    state of slots: 
    -1  not revealed
    -2  not revealed and occupied
    1   revealed
    2   revealed and occupied
    3   bombed (might discard)
    4   occupied and bombed
    */
    // remeber to *-1 for all after set board!!
    // !!!format: state[y][x] !!! 
    // why? cuz im dumb and too lazy to change it back
    
    int state[size_of_board][size_of_board];

    void init(){
        for (int i=0; i<size_of_board; i++){
            for (int j=0; j<size_of_board; j++){
                state[i][j] = 1;
            }
        }
        for (int i=0; i<no_of_ships; i++){
            ships[i] = new int[size_of_ships[i]][2];
            for (int j=0; j<size_of_ships[i]; j++){
                ships[i][j][0] = -1;    //(technicly only this is needed, if x=-1 then skip draw)
                ships[i][j][1] = -1;
            }
        }
    }

    void deallocate(){
        // free dynamic memory
        for (int i=0; i<no_of_ships; i++){
            delete[] ships[i];
        }
    }

    void updateOccupied(){
        // set all to revealed first
        for (int i=0; i<size_of_board; i++){
            for (int j=0; j<size_of_board; j++){
                state[i][j] = 1;
            }
        }

        // then set ship coords to occupied 
        for (int i=0; i< no_of_ships; i++){
            for (int j=0;j< size_of_ships[i]; j++){
                if (ships[i][j][0] != -1)
                    state[ships[i][j][1]][ships[i][j][0]] = 2;
            }
        }
    }

    void draw(){

        //first line
        cout << "   ";
        for (int i=0; i<size_of_board; i++){
            cout << "+---";
        }
        cout << "+" << endl;

        // iterate through each slot and its underline(?)
        for (int y=0; y<size_of_board; y++){
            // alphabet label
            char c = 'A'+y;
            cout << " " << c << " "; 

            for (int x=0; x<size_of_board; x++){
                // occ and bombed
                if (state[y][x] == 4){
                    cout << "| O ";
                }
                // bombed but NOT occ
                else if (state[y][x] == 3){
                    cout << "| X ";
                }
                // if revealed
                else if (state[y][x] > 0){
                    // if occ
                    if (state[y][x] == 2){
                        if (x>0 && state[y][x-1] == 2){
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
            for (int x=0; x<size_of_board; x++){
                // if this slot and below are both revealed occ
                if (state[y][x] == 2 && y<(size_of_board-1) && state[y+1][x] == 2){
                    // if slot to the left is revealed occ
                    if (x>0 && state[y][x-1] == 2){
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
        for (int i=1; i<=size_of_board; i++){
            cout << " " << i << (i/10>0 ? " " : "  "); 
        }
        cout << endl;
    }


    bool checkSunk(int x, int y, int ship_no){
        // if all non negative true, else false
        for (int i=0; i<size_of_ships[ship_no]; i++){
            if (ships[ship_no][i][0] >= 0){
                return false;
            }
        }
        return true;
    }

    // true if can bomb, else return false and do nothing
    bool bomb(int x, int y){
        if (state[y][x] > 0){
            return false;
        }
        
        // if its occupied and not revealed
        if (state[y][x] == -2){
            // set the state of coords to occ and bombed
            state[y][x] = 4;

            // set the coord in ship list to (-x-1,-y-1)
            // also get which ship it hit
            int ship_no;
            for (int i=0; i<no_of_ships; i++){
                bool found = false;
                for (int j=0; j<size_of_ships[i]; j++){
                    if (ships[i][j][0] == x && ships[i][j][1] == y){
                        found = true;
                        ships[i][j][0] = -ships[i][j][0]-1; // -1 to prevent case of 0,0 being bombed
                        ships[i][j][1] = -ships[i][j][1]-1;
                        break;
                    }
                }
                if (found){
                    ship_no = i;
                    break;
                }
            }
                    
            //check if the ship is sunk
            // if so, reveal the surroundings
            if (checkSunk(x,y,ship_no)){
                // reveal the 8 slots in every occ slot's surrounding if not occ (quite dumb)
                for (int i=0; i< size_of_ships[ship_no]; i++){
                    int original_y = -(ships[ship_no][i][1]+1);
                    int original_x = -(ships[ship_no][i][0]+1);
                    
                    // for max(y/x-1, 0) to min(y/x+1,18) to keep in bound
                    for (int y=(original_y-1>=0 ? original_y-1 : 0); y<=(original_y+1<=18 ? original_y+1 : 18); y++){
                        for (int x=(original_x-1>=0 ? original_x-1 : 0); x<=(original_x+1<=18 ? original_x+1 : 18); x++){
                            state[y][x] = 1;
                            cout << x << ' ' << y;
                        }
                    }

                }

                // make the ship reappear
                for (int i=0; i< size_of_ships[ship_no]; i++){
                    int original_y = -(ships[ship_no][i][1]+1);
                    int original_x = -(ships[ship_no][i][0]+1);
                    state[original_y][original_x] = 2;
                    // change the state to revealed and occ to achieve a diff look when sunk
                }
            }

        }
        else if (state[y][x] == -1){
            state[y][x] = 1;
        }
        return true;
    }
};
