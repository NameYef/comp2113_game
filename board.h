#ifndef BOARD_H
#define BOARD_H


class Board {
public:
    Board(); // constructor
    void draw();



private:
// variables
    // static variables 
    static constexpr int size_of_board = 19;
    static constexpr int no_of_ships = 6;
    static constexpr int size_of_ships[no_of_ships] = {3, 4, 4, 5, 6, 10};

    // instance variables 
    int state[size_of_board][size_of_board];
};


#endif