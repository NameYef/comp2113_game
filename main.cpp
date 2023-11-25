#include "manager.h"
#include <ncurses.h>
#include <iostream>
// #include "board.h"


// Initialize ncurses standard screen, start colour
void game_init(){
  setlocale(LC_ALL, ""); // set locale to draw unicode characters
  initscr();             // Initialize the window

  // start colour if its supported
  if(has_colors() == FALSE)
  {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
  }

  start_color();		    	/* Start color 			*/

  // // raw();			           	/* Line buffering disabled	*/
  keypad(stdscr, TRUE);		/* We get F1, F2 , arrow keys etc..		*/
  noecho();               // Don't echo any keypresses
  curs_set(FALSE);        // Don't display a cursor
  // nodelay(stdscr, true);  //allow to animate screen while waiting input
}


int main(int argc, char ** argv) {

    game_init();
    Manager* manager = new Manager();

    while (manager->game_state != "quit") {

    manager->run();
    
    }

    delete manager;
    

    
    
    
    




    endwin();
    return 0;

}