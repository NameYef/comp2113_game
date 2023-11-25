#include <ncurses.h>
#include <string>
#include <vector>
#include "start_title.h"
using namespace std;

void start_title() {
    int yMax, xMax;
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
    keypad(stdscr, TRUE);
    move(yMax-10,xMax/2-10);
    printw("press enter to start");
    int ch;
    while ((ch = getch()) != '\n') {}
    move(yMax - 10, 0);        // Move the cursor to the beginning of the line
    clrtoeol();       // Clear the entire line
    refresh();
    menu();
}
