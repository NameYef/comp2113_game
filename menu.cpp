#include <ncurses.h>
#include <string>
#include <iostream>
#include "menu.h"
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>

using namespace std;

// Custom comparator function
// used in sort() for the vector storing score, time, name set
bool customComparator(const vector<string>& a, const vector<string>& b) {
    if (stod(a[0]) == stod(b[0])) {
        return stod(a[1]) > stod(b[1]); // Sort based on the second element if the first element is the same
        }  
    return stod(a[0]) > stod(b[0]); // Sort based on the first element otherwise
    }

//input game_state by call by reference, such that when player select start new game or continue, respected game_state will be modified
void menu(string &game_state){
    //get screen size
    int yMax, xMax;

    //print titleint yMax, xMax;
    //get screen size
    getmaxyx(stdscr, yMax, xMax);

    //erase screen
    erase();
    //init attribtion
    attrset(0);
    //set color
    init_pair(12, COLOR_RED, COLOR_RED);
    init_pair(13, COLOR_GREEN, COLOR_BLACK);
    //turn on color
    attron(COLOR_PAIR(12));
    //target title
    vector<string> titlename;
    titlename.push_back("###   #  ### ### #   ### ### #  # ### ### ");
    titlename.push_back("#  # # #  #   #  #   #   #   #  #  #  #  #");
    titlename.push_back("###  ###  #   #  #   ### ### ####  #  ### ");
    titlename.push_back("#  # # #  #   #  #   #     # #  #  #  #   ");
    titlename.push_back("###  # #  #   #  ### ### ### #  # ### #   ");

    //set row and column of the place of title
    int r = yMax / 2 - 9, c = (xMax - 42) / 2;
    //loop out all element with respected color
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 42; j++) {
            char tmp = titlename[i][j];
            if (tmp == ' ') {
                mvaddch(r, c, tmp);
            } else {
                attron(COLOR_PAIR(12));
                mvaddch(r, c, tmp);
                attroff(COLOR_PAIR(12));
            }
            c++;
        }
        c = (xMax - 42) / 2;
        r++;
    }



    //create a winder for game (y,x,beginY,beginX)
    //WINDOW * menuwin = newwin(yMax-30, xMax-20, yMax-35, 10);
    WINDOW * menuwin = newwin(18, 30, yMax/2, xMax/2-40);

    WINDOW * content;

    //box the window
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    //allow us to use arrow key
    keypad(menuwin, true);

    //init choices
    string choices[5] = {"new game", "continue", "guideline", "leaderboard", "quit"};
    int choice;
    int highlight = 0;

    //selection
    while(1){
        for(int i = 0; i<5; i++){
            //highlight choice
            if(i == highlight )
                wattron(menuwin, A_REVERSE);
            //mvwprintw(menuwin, i+7, xMax/2-15, choices[i].c_str());
            mvwprintw(menuwin, i+7, 10, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        content = newwin(14, 56, yMax/2+1, xMax/2-5);
        box(content, 0, 0);
        if(highlight == 0)
        {
            mvwprintw(content, 6, 13, "ready to start new game?");
            mvwprintw(content, 7, 15, "press Enter to start");
            wrefresh(content);
        }
        if(highlight == 1)
        {
            fstream test;
            test.open("bot_state.txt");
            if (test.fail()){
                mvwprintw(content, 6, 12, "No record file");
            }
            else {
                mvwprintw(content, 6, 12, "ready to continue last game?");
                mvwprintw(content, 7, 14, "press Enter to continue");
            }
            test.close();
            wrefresh(content);
        }
        // for the instruction choice the instruction window pops out
        if(highlight == 2)
        {
            mvwprintw(content, 2, 2, "Controls :");
            mvwprintw(content, 3, 2, "Move -> arrow keys");
            mvwprintw(content, 4, 2, "Quit game -> ESC");
            mvwprintw(content, 5, 2, "plant your ships first");
            mvwprintw(content, 6, 2, "change direction of ship -> space");
            mvwprintw(content, 7, 2, "select the box you want to attack");
            mvwprintw(content, 8, 2, "display:");
            mvwprintw(content, 9, 2, " + -> your cursor");
            mvwprintw(content, 10, 2, " X -> missed attack");
            mvwprintw(content, 11,2, " █X█ -> successful attack");
            wrefresh(content);
        }
        // Leaderboard choice : trigger the function that shows score board
        if(highlight == 3)
        {
            vector<vector<string>> ScoreTimePairs; // 2D vector to store score-time pairs

            ifstream inputFile("ScoreTime.txt"); // Open the file for reading
            if (inputFile.is_open()) {
                string score, time, name;
                while (inputFile >> score >> time) {
                    getline(inputFile, name);
                    name.erase(0,1);
                    ScoreTimePairs.push_back({score, time, name}); // Add each pair+name to the 2D vector
                }
                inputFile.close(); // Close the file
            }
            // Sort the vector array based on the first and second elements of each sub-vector
            // sort(ScoreTimePairs.begin(), ScoreTimePairs.end(), customComparator);
            //input data
            mvwprintw(content, 1,2, "rank: (score, time, name)");
            int n=1;
            for (int i=0; i<ScoreTimePairs.size(); i++){
                mvwprintw(content, i+2, 2, "%d.", n);
                mvwprintw(content, i+2, 5, "%s", (ScoreTimePairs[i][0]).c_str());
                mvwprintw(content, i+2, 20, "%dmin %ds", (stoi(ScoreTimePairs[i][1])/60), (stoi(ScoreTimePairs[i][1])%60));
                mvwprintw(content, i+2, 30, "%s", (ScoreTimePairs[i][2]).c_str());
                n++;
            }

            wrefresh(content);
        }
        // exit choice : delete the menu windows and return to terminal
        if(highlight == 4)
        {
            mvwprintw(content, 6, 16, "Are you sure to exit?");
            mvwprintw(content, 7, 16, "press Enter to exit");
            wrefresh(content);
        }

        choice = wgetch(menuwin);

        //selection
        switch (choice) {
            case KEY_UP:
                highlight--;
                //prevent out of bound
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                //prevent out of bound
                if (highlight == 5)
                    highlight = 4;
                break;
            default:
                break;
        }
        //10 is enter key
        if(choice == 10 && highlight == 0)
        {
            //start game
            game_state = "pregame";
            clear();
            return;
        }
        if(choice == 10 && highlight == 1){
            //continue game
            fstream test;
            test.open("bot_state.txt");
            if (test.fail()){
                continue;
            }
            test.close();
            game_state = "game";
            clear();
            return;
        }
        if(choice == 10 && highlight == 4){
            //exit game
            game_state = "quit";
            break;
        }


    }
/*    int row, col;
    getyx(menuwin, row, col);
    move(row,xMax/2-10);*/
    //print selected choice

    /*
    if (choices[highlight] == "continue"){
        //continue last game
    }
    else if (choices[highlight] == "guideline"){
        //quick demo or word guide
    }
    else if (choices[highlight] == "leaderboard"){
        //show rank
    }
     */
    // Clear the content window and free memory
    werase(content);
    wrefresh(content);
    delwin(content);
    // Clear the menu window and free memory
    werase(menuwin);
    wrefresh(menuwin);
    delwin(menuwin);
    clear();
    refresh();
    mvprintw(yMax/2, xMax/2-5, "Loading...");
    refresh();
    this_thread::sleep_for(chrono::nanoseconds(10));
    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
    clear();
    //keep window show to see
    //getch();

}
/*
int main(int argc, char ** argv)
{

    // initialise the screen
    // sets up memory and clears the screen
    initscr();
    //ctrl C to exit
    cbreak();
    //not printing the user input
    noecho();

    menu();

    endwin();

    return 0;
}*/

