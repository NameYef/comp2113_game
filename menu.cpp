
#include <ncurses.h>
#include <string>
#include <iostream>
#include "menu.h"
#include <chrono>
#include <thread>
using namespace std;

void menu(){
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //create a winder for game (y,x,beginY,beginX)
    WINDOW * menuwin = newwin(yMax-30, xMax-20, yMax-35, 10);

    //box the window
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    //allow us to use arrow key
    keypad(menuwin, true);

    //init choices
    string choices[4] = {"new game", "continue", "guideline", "leaderboard"};
    int choice;
    int highlight = 0;

    //selection
    while(1){
        for(int i = 0; i<4; i++){
            //highlight choice
            if(i == highlight )
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+7, xMax/2-15, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
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
                if (highlight == 4)
                    highlight = 3;
                break;
            default:
                break;
        }
        //10 is enter key
        if (choice == 10)
            break;


    }
    if (choices[highlight] == "continue"){
        //continue last game
        // Clear the menu window and free memory
        werase(menuwin);
        wrefresh(menuwin);
        delwin(menuwin);
    }
    else if (choices[highlight] == "guideline"){
        //quick demo or word guide
        // Clear the menu window and free memory
        werase(menuwin);
        wrefresh(menuwin);
        delwin(menuwin);
    }
    else if (choices[highlight] == "leaderboard"){
        //show rank
        // Clear the menu window and free memory
        werase(menuwin);
        wrefresh(menuwin);
        delwin(menuwin);
    }
    //location of printed word should be further modified *also should we introduce rule here?
    cout << '\n';
    cout << "your choice is: " << choices[highlight] << endl;
    cout << "Loading...";
    refresh();
    this_thread::sleep_for(chrono::nanoseconds(10));
    this_thread::sleep_until(chrono::system_clock::now() + chrono::seconds(1));
    //keep window show to see cout
    getch();

    // Clear the menu window and free memory
    werase(menuwin);
    wrefresh(menuwin);
    delwin(menuwin);
    //start new game
    //code for calling manager
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

