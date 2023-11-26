#include <ncurses.h>
#include <string>
#include <iostream>
#include "menu.h"
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

void menu(){
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //create a winder for game (y,x,beginY,beginX)
    //WINDOW * menuwin = newwin(yMax-30, xMax-20, yMax-35, 10);
    WINDOW * menuwin = newwin(18, 30, yMax/2-5, xMax/2-40);

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

        if(highlight == 0)
        {
            content = newwin(14, 56, yMax/2-4, xMax/2-5);
            box(content, 0, 0);
            mvwprintw(content, 6, 13, "ready to start new game?");
            mvwprintw(content, 7, 15, "press Enter to start");
            wrefresh(content);
        }
        if(highlight == 1)
        {
            content = newwin(14, 56, yMax/2-4, xMax/2-5);
            box(content, 0, 0);
            mvwprintw(content, 6, 12, "ready to continue last game?");
            mvwprintw(content, 7, 14, "press Enter to continue");
            wrefresh(content);
        }
        // for the instruction choice the instruction window pops out
        if(highlight == 2)
        {
            content = newwin(14, 56, yMax/2-4, xMax/2-5);
            box(content, 0, 0);
            mvwprintw(content, 2, 2, "Controls :");
            mvwprintw(content, 3, 2, "Move -> arrow keys");
            mvwprintw(content, 4, 2, "Quit game -> dunno yet");
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
            int n = 0;              // nth score in descending order
            fstream op("score_and_time.txt");
            //input data
            content = newwin(14, 56, yMax/2-4, xMax/2-5);
            box(content, 0, 0);
            mvwprintw(content, 1,2, "rank");

            /*// store the scores from file to vector with istream_iterator
            vector<int> scores((istream_iterator<int>(op)), istream_iterator<int>());
            sort(scores.begin(), scores.end(), greater<int>()); // sorts in descending order

            // print top 10 scores from vec
            for (const auto& e: scores){
                if (n >= 9) break; // only output top 10 scores
                mvwprintw(content, n+highlight, 3, "%d.", n+1);
                mvwprintw(content, n+highlight, 6,"%d", e);
                n++;

            }*/
            mvwprintw(content, 12, 2, "Press s to continue");
            wrefresh(content);
        }
        // exit choice : delete the menu windows and return to terminal
        if(highlight == 4)
        {
            content = newwin(14, 56, yMax/2-4, xMax/2-5);
            box(content, 0, 0);
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
            clear();
            break;
        }
        if(choice == 10 && highlight == 1){
            //continue game
            clear();
            break;
        }
        if(choice == 10 && highlight == 4){
            //exit game
            endwin(); // end all windows
            exit(1); //quit game
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

