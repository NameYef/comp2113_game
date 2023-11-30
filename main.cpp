#include "manager.h"
#include "start_title.h"
#include <ncurses.h>
#include <iostream>
// #include "board.h"


// Initialize ncurses standard screen, start colour
void game_init(){
    setlocale(LC_ALL, ""); // set locale to draw unicode characters
    initscr();             // Initialize the window

    // start colour if its supported
    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();		    	// Start color 		
    keypad(stdscr, TRUE);		// get arrow keys
    noecho();               // Don't echo any keypresses
    curs_set(FALSE);        // Don't display a cursor
    start_title();
}


int main(int argc, char ** argv) {
    // start ncurses
    game_init();
    // create the manager pointer and set it to nullptr
    Manager* manager = nullptr;

    while (1) {
        // if manager is nullptr then initiate a new instance
        if (manager == nullptr) {
            manager = new Manager();
        }
        // run the game
        manager->run();

        // exit the loop and terminate the game 
        if (manager->game_state == "quit") {
            break;
        }
        // this runs after a game is finished, manager is deleted and re-initiated to reset game status
        if (manager->game_state == "done") {
            delete manager;
            manager = nullptr;
        }
    }
    // the program must go through this step to deallocate memory
    delete manager;
    endwin();
    return 0;

}