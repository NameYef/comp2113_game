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
    player = new Player();
    bot = new Bot();
    game_state = "menu";
    previous_player = "bot";
    paused = false;
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
        game_state = "quit";
        return;
    }

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
    
    //start timer
    auto start = chrono::high_resolution_clock::now();
    while (1) {
        paused = false;

        bot->draw(bot_board);
        player->draw(player_board);
        this->draw_status(bot_status, "bot");
        this->draw_status(player_status, "player");

        if (check_win()) {
            break;
        }

        
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


            while (true){
                if (bot->player_attack(bot_board, paused)){
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
                else {
                    break;
                }
            }
        }
        else if (previous_player == "player" && !paused) {
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

        if (!paused) {
            switch_player();
        }



    }
    // stop the clock
    auto end = chrono::high_resolution_clock::now();

    // calculate the elapsed time
    chrono::duration<double> elapsed = end - start;
    duration += elapsed.count();


    game_state = "menu";
    // previous_player won, type anything then can return to menu
    // below here add a window to tell player who won, and also store the info of this game into a file

    werase(announcer);
    box(announcer,0, 0);
    (previous_player == "player") ? mvwprintw(announcer, 2, 10, "Player won!") : mvwprintw(announcer, 2, 12, "Bot won!");
    mvwprintw(announcer, 4, 4, "Press any key to continue");
    wrefresh(announcer);
    getch();

    clear();
    delwin(bot_board);
    delwin(player_board);
    delwin(bot_status);
    delwin(player_status);
    delwin(announcer);

    string name;
    name = enter_name();
    update_score_time(duration, name);

 
    return;
}

void Manager::run() {
    if (game_state == "menu") {
        // menu stuff
        menu(game_state);

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
            // new gae
            duration = 0;
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


/*
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
           cout << "Data written to file successfully." << endl;
    } else {
        cout << "Error opening the file." << endl;
    }
    }
}
*/

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
//run when user win
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
                ScoreTimePairs.push_back({score, time, name}); // Add each pair+name to the 2D vector
            }
        }
        inputFile.close(); // Close the file
    }

    //add new score and time to the rank
    vector<string> new_ScoreTime;
    double score = player->score() - bot->score();
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
