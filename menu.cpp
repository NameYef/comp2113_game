
#include <ncurses.h>
#include <string>
#include <iostream>
#include "menu.h"
using namespace std;

void menu(){
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //create a winder for game (y,x,beginY,beginX)
    WINDOW * menuwin = newwin(yMax-10, xMax-10, 20, 10);

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
            mvwprintw(menuwin, i+1, 1, choices[i].c_str());
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
    cout << endl;
    //print selected choice
    cout << "your choice is: " << choices[highlight] << endl;
    //keep window show to see cout
    getch();
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

