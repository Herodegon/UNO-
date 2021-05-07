uno: main.o Game/Game.o Cards/Deck.o Cards/Hand.o Cards/Cards.o
	g++ main.o Game/Game.o Cards/Deck.o Cards/Hand.o Cards/Cards.o -o uno -std=c++11

main.o: main.cpp Game/Game.h
	g++ -Wall -c main.cpp -o main.o -std=c++11

Game.o: Game/Game.cpp Cards/Deck.h Cards/Hand.h
	g++ -Wall -c Game/Game.cpp -o Game.o -std=c++11

Deck.o: Cards/Deck.cpp Cards/Cards.h
	g++ -Wall -c Cards/Deck.cpp -o Deck.o -std=c++11

Hand.o: Cards/Hand.cpp Cards/Cards.h
	g++ -Wall -c Cards/Hand.cpp -o Hand.o -std=c++11 

Cards.o: Cards/Cards.cpp
	g++ -Wall -c Cards/Cards.cpp -o Cards.o -std=c++11

clean:
	rm *.o *.gch Cards/*.o Cards/*.gch Game/*.o Game/*.gch
