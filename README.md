# Battleship in C++

## Team members
Group 69

Chan Man Hon 3036077255 [@NameYef](https://github.com/NameYef)

Aisha Zhumabayeva 3035908110 [@aishusha](https://github.com/aishusha)

Ip Hau Ching Adrian 3036064349 [@adrianip03](https://github.com/adrianip03)

Lei Kam Fai 3036104216 [@CashonPierre](https://github.com/CashonPierre)

Ng Sheung Him Brian 3035782566 [@nshb765](https://github.com/nshb765)

## Description of the game
Battleship is a classic strategy-based board game that simulates naval warfare. The player’s goal is to sink all of the opponent's ships before they sink player’s. In our game, a human plays against a computer. The specific configuration/placement of the ships on the board are hidden from opponents. 

The players take turns, the first move is always made by the human player, followed by a computer-generated move. The game consists of 2 square grids where players can place their fleet of ships. The size of the grids in our game is 19\*19. The ships are of different sizes and can be located horizontally or vertically. We have implemented ships with sizes of 3, 4, 5, 6, and 10 cells. 

At the beginning of the game, the player has to place his/her ships on the board and after that the game will start. The game continues until one player has successfully sunk all of their opponent’s ships. 

Battleship is a game where anyone needs strategic thinking, deduction and a bit of luck. It requires patience and determination but rewards you with the best feeling of victory over the computer. 

## Demo video
[![](https://i3.ytimg.com/vi/_dpDKF0lYIg/maxresdefault.jpg)](https://www.youtube.com/watch?v=_dpDKF0lYIg)

## Coding requirements
### Generation of random game sets or events
random sets of coordinates are generated with the use of \<random\> for bot board setup and bot attack, different sets of boards are generated every game and the bot is able to attack the player's board randomly.

### Data structures for storing game status. 
A class for both player and the bot with arrays used to store the state of the boards and vectors used to store the ship's coordinates. 

### Dynamic memory management
The manager class instance responsible for the whole game status and game flow is dynamically allocated and deleted when a game is over, making the game re-playable without quitting

### File input/output (e.g, for loading/saving game status)
The game state is stored whenever the player quits in the middle of the game, game state is loaded when the player wants to continue playing the previous game

### Program codes in multiple files
Easy to modify key components of the game with multiple files. E.g. player.cpp, bot.cpp, board.cpp, manager.cpp, menu.cpp, main.cpp

  
## Non-standard libraries
ncurses "ncurses.h"
- to draw the windows in the terminal


## Compilation and execution instructions
- run `make main` to compile the game
- run `./main` to launch the game

