#include "manager.h"
#include <iostream>

using namespace std;

// Constructor
Manager::Manager() {
    player = new Player();
    bot = new Bot();
    game_state = "pregame";
    previous_player = "bot";
    getmaxyx(stdscr, ymax, xmax); 
}

// Destructor
Manager::~Manager() {
    delete player;
    delete bot;
}

void Manager::game_setup() {
    bot->setup();
    player->setup();

    game_state = "game";
    return;
}

void Manager::switch_player() {
    previous_player = (previous_player == "player") ? "bot" : "player";
}

bool Manager::check_win() {
    // take both bot and player ship check
    // if anyone wins then return True
    return (player->ship_empty() || bot->ship_empty());
}

void Manager::draw_status(WINDOW* win, string user) {
    if (user == "player") {
        vector<vector<vector<int>>> ships = player->get_ships();
        refresh();
        werase(win);
        wrefresh(win);
        box(win, 0, 0);
        wrefresh(win);

        mvwprintw(win, 0, 1, "Player");
        mvwprintw(win, 1, 1, "Tiny: %lu / %d", ships[0].size(), 3);
        mvwprintw(win, 2, 1, "Small: %lu / %d", ships[1].size(), 4);
        mvwprintw(win, 3, 1, "Small: %lu / %d", ships[2].size(), 4);
        mvwprintw(win, 4, 1, "Medium: %lu / %d", ships[3].size(), 5);
        mvwprintw(win, 5, 1, "Large: %lu / %d", ships[4].size(), 6);
        mvwprintw(win, 6, 1, "Titan: %lu / 10", ships[5].size());
        wrefresh(win);
        refresh();
    }
    else if (user == "bot") {
        vector<vector<vector<int>>> ships = bot->get_ships();
        refresh();
        werase(win);
        wrefresh(win);
        box(win, 0, 0);
        wrefresh(win);
        mvwprintw(win, 0, 1, "Bot");
        mvwprintw(win, 1, 1, "Tiny: %lu / %d", ships[0].size(), 3);
        mvwprintw(win, 2, 1, "Small: %lu / %d", ships[1].size(), 4);
        mvwprintw(win, 3, 1, "Small: %lu / %d", ships[2].size(), 4);
        mvwprintw(win, 4, 1, "Medium: %lu / %d", ships[3].size(), 5);
        mvwprintw(win, 5, 1, "Large: %lu / %d", ships[4].size(), 6);
        mvwprintw(win, 6, 1, "Titan: %lu / 10", ships[5].size());
        wrefresh(win);
        refresh();
    }
}



void Manager::gameplay() {
// implement turn based fundamental gameplay here
    // if no one wins then continue this loop
    WINDOW* bot_board = newwin(41, 83, 0, 0);
    WINDOW* player_board = newwin(41, 83, 0, 119);
    WINDOW* bot_status = newwin(10, 20, 44, 30);
    WINDOW* player_status = newwin(10, 20, 44, 202 - 53);
    WINDOW* announcer = newwin(10, 202 - 170, 20, 85);
    
    while (1) {
        bot->draw(bot_board);
        player->draw(player_board);
        this->draw_status(bot_status, "bot");
        this->draw_status(player_status, "player");


        
        if (previous_player == "bot") {
            // player's turn to attack
            werase(announcer);
            box(announcer, 0, 0);
            mvwprintw(announcer, 6, 5, "Player  %d vs %d   Bot", player->ship_left(), bot->ship_left());
            mvwprintw(announcer, 2, 9, "Player's Turn!");
            mvwprintw(announcer, 3, 7,"Arrow key to move");
            mvwprintw(announcer,4, 8, "ENTER to attack");
            refresh();
            wrefresh(announcer);
            bot->player_attack(bot_board);
        }
        else if (previous_player == "player") {
            // bot's turn to attack
            werase(announcer);
            box(announcer, 0, 0);
            mvwprintw(announcer, 6, 5, "Player  %d vs %d   Bot", player->ship_left(), bot->ship_left());
            mvwprintw(announcer, 2, 5, "Press any key to see");
            mvwprintw(announcer, 3, 9, "bot's attack");
            wrefresh(announcer);
	        player->bot_attack();
            getch();
        }


        switch_player();

        if (check_win()) {

            break;
        }

    }

    // previous_player won, type anything then can return to menu
    // below here add a window to tell player who won, and also store the info of this game into a file

    werase(announcer);
    mvwprintw(announcer, 2, 4, "%s won!", previous_player);
    wrefresh(announcer);

    getch();
    game_state = "quit";
    return;
}

void Manager::run() {
    if (game_state == "menu") {
        // menu stuff
    }
    else if (game_state == "pregame") {
        game_setup();
    }
    else if (game_state == "game") {
        gameplay();
    }
    return;
}
