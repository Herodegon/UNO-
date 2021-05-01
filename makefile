uno: main.o
	g++ main.o -o uno -Wall -std=c++11

main.o: main.cpp Game.h
	g++ -c main.cpp -o main.o

Game.o: Game.cpp Cards/Deck.h Cards/Hand.h
	g++ -c Game.cpp -o Game.o

Cards/Deck.o: Cards/Deck.cpp Cards/Cards.h
	g++ -c Cards/Deck.cpp -o Deck.o

Cards/Hand.o: Cards/Hand.cpp Cards/Cards.h
	g++ -c Cards/Hand.cpp -o Hand.o 

Cards/Cards.o: Cards/Cards.cpp
	g++ -c Cards/Cards.cpp -o Cards.o

clean:
	$(RM) $(uno)
