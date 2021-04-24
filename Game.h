#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Cards/Deck.h"
#include "Cards/Hand.h"

class Game {
    public:
        Game();
        void Tutorial() const;
        
        //Runs Through 1 Round of UNO
        void PlayGame();
        
        //Runs Through Player Turn
        void Turn();
        
        //Scores Player Hands
        int ScoreTally() const;
        int CountHandScore() const;
    
    private:
        Deck deckPile; //UNO Deck
        Deck disPile; //Discard Pile
        
        std::vector<Hand> playerHands; //Collection of All Player Hands
        
        
};

#endif
