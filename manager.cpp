#include "manager.h"
#include <iostream>
#include <ctime>

using namespace std;

// Constructor
Manager::Manager() {
    player = new Player();
    bot = new Bot();
    game_state = "menu";
    previous_player = 'b';
    getmaxyx(stdscr, ymax, xmax);
}

// Destructor
Manager::~Manager() {
    delete player;
    delete bot;
}

void Manager::game_setup() {
    bot->setup();
    if (player->setup()){
        //save the game
        endwin(); // end all windows
        exit(1); //quit game
    }

    game_state = "game";
    return;
}

void Manager::switch_player() {
    previous_player = (previous_player == 'p') ? 'b' : 'p';
}

bool Manager::check_win() {
    // take both bot and player ship check
    // if anyone wins then return True
    return (player->ship_empty() || bot->ship_empty());
}

void Manager::draw_status(WINDOW* win, char user) {
    if (user == 'p') {
        vector<vector<vector<int>>> ships = player->get_ships();
        refresh();
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
    else if (user == 'b') {
        vector<vector<vector<int>>> ships = bot->get_ships();
        refresh();
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
    WINDOW* player_board = newwin(41, 83, 0, xmax - 83);
    WINDOW* bot_status = newwin(10, 20, 44, 30);
    WINDOW* player_status = newwin(10, 20, 44, xmax - 53);

    //start timer
    clock_t start = clock();
    
    while (! check_win()) {
        bot->draw(bot_board);
        player->draw(player_board);
        this->draw_status(bot_status, 'b');
        this->draw_status(player_status, 'p');

        if (previous_player == 'b') {
            // player's turn to attack
            while (true){
                if (bot->player_attack(bot_board)){
                    //save the game
                    bot->store_state("bot_state.txt");
                    player->store_state("player_state.txt");
                    endwin(); // end all windows
                    exit(1); //quit game
                }
                else {
                    bot->draw(bot_board);
                    player->draw(player_board);
                    this->draw_status(bot_status, 'b');
                    this->draw_status(player_status, 'p');
                }
            }
        }
        else if (previous_player == 'p') {
            // bot's turn to attack
            // placeholder below
            getch();
        }

        switch_player();

    }
    clock_t end = clock();
    game_state = "menu";
    // previous_player won, type anything then can return to menu
    // below here add a window to tell player who won, and also store the info of this game into a file




    getch();

    return;
}

void Manager::run() {
    if (game_state == "menu") {
        // menu stuff
        menu(game_state);
        if (game_state == "game"){
            bot->load_state("bot_state.txt");
            player->load_state("player_state.txt");
        }
    }
    else if (game_state == "pregame") {
        game_setup();
    }
    else if (game_state == "game") {
        gameplay();
    }
    return;
}


void Manager::update_score_time(vector<vector<int>> ScoreTimePairs){
    ofstream outputFile("ScoreTime.txt"); // Open the file for writing

    if (outputFile.is_open()) {
        for (const auto& pair : ScoreTimePairs) {
            for (const int& value : pair) {
                outputFile << value << " "; // Write each value separated by a space
            }
            outputFile << endl; // Write a new line after each pair
        }

        outputFile.close(); // Close the file
/*        cout << "Data written to file successfully." << endl;
    } else {
        cout << "Error opening the file." << endl;
    }*/
    }
}