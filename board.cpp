#include "board.h"
#include <iostream>
#include <sstream>

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
                    mvwprintw(win, game_row, column, "█X█|");
                    column += 4;
                    break;
            }

        }

        mvwprintw(win, game_row + 1, 1, "   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+");
        game_row += 2;
        
    }
    wrefresh(win);
    refresh();

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

bool Board::confirmQuit() {

    // keypad(stdscr, true);  // Enable keypad for arrow key input
    // noecho();  // Disable echoing of user input

    clear();  // Clear the screen

    // Get the dimensions of the terminal window
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    // Center the message on the screen
    const char* message = "Do you want to quit?";
    int messageLength = strlen(message);
    int row = maxRows / 2;
    int col = (maxCols - messageLength) / 2;

    // Display the message
    mvprintw(row, col, message);

    // Display the options
    const char* optionYes = "[ Yes ]";
    const char* optionNo = "[ No ]";
    int optionWidth = strlen(optionYes);
    int optionRow = row + 2;
    int optionCol = (maxCols - optionWidth * 2) / 2;

    attron(A_REVERSE);  // Highlight the first option
    mvprintw(optionRow, optionCol, optionYes);
    attroff(A_REVERSE);
    mvprintw(optionRow, optionCol + optionWidth, optionNo);

    refresh();  // Refresh the screen

    int currentOption = 0;
    int choice;

    while ((choice = getch())) {
        switch (choice) {
            case KEY_LEFT:
                if (currentOption == 1) {
                    // Highlight the first option
                    mvprintw(optionRow, optionCol, optionYes);
                    attroff(A_REVERSE);
                    mvprintw(optionRow, optionCol + optionWidth, optionNo);
                    currentOption = 0;
                }
                break;
            case KEY_RIGHT:
                if (currentOption == 0) {
                    // Highlight the second option
                    mvprintw(optionRow, optionCol, optionYes);
                    mvprintw(optionRow, optionCol + optionWidth, optionNo);
                    attron(A_REVERSE);
                    mvprintw(optionRow, optionCol + optionWidth, optionNo);
                    currentOption = 1;
                }
                break;
            case '\n':
                // User confirmed selection, clean up and restore the terminal
                endwin();

                if (currentOption == 0) {
                    // User selected "Yes"
                    return true;
                } else {
                    // User selected "No"
                    clear();
                    return false;
                }
        }
    }
}

//run when user exit
void Board::store_state(string fname) {
    ofstream outputFile(fname.c_str());
    if (outputFile.is_open()) {
        for (int i = 0; i < size_of_board; i++) {
            for (int j = 0; j < size_of_board; j++) {
                outputFile << state[i][j] << " ";
            }
            outputFile << endl;
        }
        for (const auto& outerVec : ships) {
            for (const auto& innerVec : outerVec) {
                for (const int& element : innerVec) {
                    outputFile  << element << " ";
                }
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Game state saved successfully." << endl;
    } else {
        cerr << "Failed to open the output file." << endl;
    }
}

//run when user continue
void Board::load_state(string fname) {
    ifstream inputFile(fname.c_str());
    if (inputFile.is_open()) {
        for (int i = 0; i < size_of_board; i++) {
            for (int j = 0; j < size_of_board; j++) {
                inputFile >> state[i][j];
            }
        }
        ships.clear();
        string s;
        getline(inputFile,s);
        while(getline(inputFile,s)){
            istringstream iss(s);
            vector<vector<int>> coords_arr;
            if (s != ""){
                int i,j;
                while (iss >> i >> j){
                    vector<int> coords;
                    coords.push_back(i);
                    coords.push_back(j);
                    coords_arr.push_back(coords);
                }
            }
            ships.push_back(coords_arr);
        }
        inputFile.close();
        cout << "Game state loaded successfully." << endl;

        // ... code to resume the game ...
    } else {
        cerr << "Failed to open the input file." << endl;
    }
}

//get accuracy
double Board::accuracy(){
    double missed_attack_num = 0.0, hitted_attack_num = 0.0;
    for (int i = 0; i < size_of_board; i++) {
            for (int j = 0; j < size_of_board; j++) {
                if (state[i][j] == 4)
                    missed_attack_num++;
                if (state[i][j] == 5)
                    hitted_attack_num++;
            }
    }
    return hitted_attack_num/(missed_attack_num+hitted_attack_num);
}

/* moved to manager
//run when user win
void Board::store_accuracy() {
    ofstream outputFile("game_state.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < size_of_board; i++) {
            for (int j = 0; j < size_of_board; j++) {
                outputFile << state[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
        cout << "Game state saved successfully." << endl;
    } else {
        cerr << "Failed to open the output file." << endl;
    }
}
*/
double Board::score(){
    int count = 27;
    for (const auto& outerVec : ships) {
            for (const auto& innerVec : outerVec) {
                count--;
            }
    }
    return count*accuracy();
}
