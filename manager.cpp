#include "manager.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;

// Constructor
Manager::Manager() {
    // filling the variables
    player = new Player();
    bot = new Bot();
    game_state = "menu";
    previous_player = "bot";
    paused = false;

}

// Destructor, called when manager is deleted
Manager::~Manager() {
    delete player;
    delete bot;
}

// method for game setup, bot setup first then player setup, if player quit during setup then close the game, if not then proceed
void Manager::game_setup() {
    bot->setup();
    if (player->setup()){
        //save the game
        game_state = "quit";
        return;
    }

    game_state = "game";
    return;
}

// method for turn based mechanics
void Manager::switch_player() {
    previous_player = (previous_player == "player") ? "bot" : "player";
}

// method to check whether the ships vector is empty for player and the bot, if either one is empty that means the game is over
bool Manager::check_win() {
    // take both bot and player ship check
    // if anyone wins then return True
    return (player->ship_empty() || bot->ship_empty());
}

// method to draw the status windows in the gameplay screen
void Manager::draw_status(WINDOW* win, string user) {
    // the ship status window for player
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
    // the ship status window for bot
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


// the whole gameplay is in this method
void Manager::gameplay() {
    // initiating windows 
    WINDOW* bot_board = newwin(41, 83, 0, 0);
    WINDOW* player_board = newwin(41, 83, 0, 119);
    WINDOW* bot_status = newwin(10, 20, 44, 30);
    WINDOW* player_status = newwin(10, 20, 44, 149);
    WINDOW* announcer = newwin(10, 32, 20, 85);
    
    //start timer
    auto start = chrono::high_resolution_clock::now();

    // implement turn based fundamental gameplay here
    // if no one wins then continue this loop
    while (1) {
        // setting paused to false as default
        paused = false;

        // drawing the windows 
        bot->draw(bot_board);
        player->draw(player_board);
        this->draw_status(bot_status, "bot");
        this->draw_status(player_status, "player");

        // if either side's ship array is empty then exit the loop
        if (check_win()) {
            break;
        }

        // when its player's turn, previous player is bot so the current player is the player
        if (previous_player == "bot") {
        // player's turn to attack
            // display the information in the center window
            werase(announcer);
            box(announcer, 0, 0);
            mvwprintw(announcer, 6, 5, "Player  %d vs %d   Bot", player->ship_left(), bot->ship_left());
            mvwprintw(announcer, 2, 9, "Player's Turn!");
            mvwprintw(announcer, 3, 7,"Arrow key to move");
            mvwprintw(announcer,4, 8, "ENTER to attack");
            refresh();
            wrefresh(announcer);

            // during players turn
            while (true){
                if (bot->player_attack(bot_board, paused)){ // if player quit in the middle of the game, run this
                    //save the game
                    bot->store_state("bot_state.txt");
                    player->store_state("player_state.txt");

                    // stop the clock
                    auto end = chrono::high_resolution_clock::now();

                    // calculate the elapsed time
                    chrono::duration<double> elapsed = end - start;
                    duration += elapsed.count();
                    
                    // store the duration
                    ofstream fout;
                    fout.open("duration.txt");
                    fout << duration;
                    fout.close();

                    endwin();
                    game_state = "quit";
                    return;
                }
                else { // player attack is finished and exit this loop
                    break;
                }
            }
        }
        // bot's turn, if game has been paused before then doesnt run this as it would still be player's turn
        else if (previous_player == "player" && !paused) {
        // bot's turn to attack
            // display the information in the center window
            werase(announcer);
            box(announcer, 0, 0);
            mvwprintw(announcer, 6, 5, "Player  %d vs %d   Bot", player->ship_left(), bot->ship_left());
            mvwprintw(announcer, 2, 5, "Press any key to see");
            mvwprintw(announcer, 3, 9, "bot's attack");
            wrefresh(announcer);
            // call bot attack method 
	        player->bot_attack();
            // wait for player to enter something to see where bot attacked
            getch();
        }

        // if the game hasnt been paused before then switch the player
        if (!paused) {
            switch_player();
        }

    }
    // stop the clock
    auto end = chrono::high_resolution_clock::now();

    // calculate the elapsed time
    chrono::duration<double> elapsed = end - start;
    duration += elapsed.count();

    // change game state and delete the files for "continue" since the game is finished
    game_state = "done";
    remove("bot_state.txt");
    remove("player_state.txt");
    remove("duration.txt");

    // windows to tell the player who won
    werase(announcer);
    box(announcer,0, 0);
    (previous_player == "player") ? mvwprintw(announcer, 2, 10, "Player won!") : mvwprintw(announcer, 2, 12, "Bot won!");
    mvwprintw(announcer, 4, 4, "Press any key to continue");
    wrefresh(announcer);
    getch();

    // deleting all the windows to move on to the next screen
    clear();
    delwin(bot_board);
    delwin(player_board);
    delwin(bot_status);
    delwin(player_status);
    delwin(announcer);

    // a screen for player to enter the name and update the score file
    string name;
    name = enter_name();
    update_score_time(duration, name);

 
    return;
}

// this method contains the game flow
void Manager::run() {
    // run menu if game state is menu
    if (game_state == "menu") {
        menu(game_state);

        // run when player press continue
        if (game_state == "game"){
            //continue

            bot->load_state("bot_state.txt");
            player->load_state("player_state.txt");
            
            //load duration
            ifstream fin;
            fin.open("duration.txt");
            fin >> duration;
            fin.close();
        }
        else {
            // new game
            duration = 0;
        }
    }
    // run when game enters pregame stage
    else if (game_state == "pregame") {
        game_setup();
    }
    // run when game enters game stage
    else if (game_state == "game") {
        gameplay();
    }
    return;
}

// method to let player see the enter name screen and enter name
string Manager::enter_name(){

    // keypad(stdscr, true);  // Enable keypad for arrow key input
    echo();  // Allow echoing of user input

    clear();  // Clear the screen

    // Get the dimensions of the terminal window
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    // Center the message on the screen
    const char* message = "Game ended. Please enter your name:";
    int messageLength = strlen(message);
    int row = maxRows / 2;
    int col = (maxCols - messageLength) / 2;

    // Display the message
    mvprintw(row, col, message);
    mvprintw(row+1, col, "My name is ");
    move(row + 1, col + 12);
    char str[100];
    getstr(str);

    refresh();  // Refresh the screen
    if (str[0] == '\0') {
        strcpy(str, "unnamed");
    }

    noecho();  // Disable echoing of user input
    string name(str); 
    if (name.length()==0)
        name = "Unnamed";
    return name;
}

//run when user win, this updates the ScoreTime.txt with the latest game info, taking the duration and name from that game as input
void Manager::update_score_time(double duration, string name) {

    vector<vector<string>> ScoreTimePairs; // 2D vector to store score-time pairs+name

    ifstream inputFile("ScoreTime.txt"); // Open the file for reading
    if (inputFile.is_open()) {
        string score, time, name;
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            if (iss >> score >> time) {
                getline(iss, name);
                name.erase(0,1);
                ScoreTimePairs.push_back({score, time, name}); // Add each pair+name to the 2D vector
            }
        }
        inputFile.close(); // Close the file
    }

    //add new score and time to the rank
    vector<string> new_ScoreTime;
    double score = ((bot->score() * bot->accuracy()) - (player->score() * player->accuracy()));
    new_ScoreTime.push_back(to_string(score));
    new_ScoreTime.push_back(to_string(duration));
    //add name also
    new_ScoreTime.push_back(name);
    // Sort the vector array based on the first and second elements of each sub-vector
    sort(ScoreTimePairs.begin(), ScoreTimePairs.end(), customComparator);
    if (ScoreTimePairs.size() < 10)
        ScoreTimePairs.push_back(new_ScoreTime);
    else if (stod(new_ScoreTime[0]) > stod(ScoreTimePairs[ScoreTimePairs.size()-1][0])){
                ScoreTimePairs.pop_back();
                ScoreTimePairs.push_back(new_ScoreTime);
            }
    
    
    // Sort the vector array based on the first and second elements of each sub-vector
    sort(ScoreTimePairs.begin(), ScoreTimePairs.end(), customComparator);



    ofstream outputFile("ScoreTime.txt"); // Open the file for writing
    if (outputFile.is_open()) {
        for (const auto& pair : ScoreTimePairs) {
            for (const auto& value : pair) {
                outputFile << value << " "; // Write each value separated by a space
            }
            outputFile << endl; // Write a new line after each pair
        }
    }
}
