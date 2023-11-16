FLAGS = -pedantic-errors -std=c++11

board.o: board.cpp board.h
	g++ $(FLAGS) -c $<

bot.o: bot.cpp bot.h
	g++ $(FLAGS) -c $<

player.o: player.cpp player.h
	g++ $(FLAGS) -c $<

manager.o: manager.cpp manager.h
	g++ $(FLAGS) -c $<

main: board.o bot.o player.o manager.o main.cpp
	g++ $(FLAGS) $^ -o $@ -lncursesw

clean:
	rm -f main manager.o player.o bot.o board.o 

.PHONY: clean

