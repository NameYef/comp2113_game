FLAGS = -pedantic-errors -std=c++11

board.o: board.cpp board.h
	g++ $(FLAGS) -c $<

bot.o: bot.cpp bot.h
	g++ $(FLAGS) -c $<

player.o: player.cpp player.h
	g++ $(FLAGS) -c $<

manager.o: manager.cpp manager.h
	g++ $(FLAGS) -c $<

start_title.o: start_title.cpp start_title.h
	g++ $(FLAGS) -c $<

menu.o: menu.cpp menu.h
	g++ $(FLAGS) -c $<

main: board.o bot.o player.o manager.o start_title.o menu.o main.cpp
	g++ $(FLAGS) $^ -o $@ -lncurses

clean:
	rm -f main manager.o player.o bot.o board.o menu.o start_title.o

.PHONY: clean

