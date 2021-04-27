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
        void Round();
        
        //Runs Through Player Turn
        void Turn();
        
        //Scores Player Hands
        int ScoreTally() const;
        int CountHandScore() const;
    
    private:
        unsigned int numPlayers;
        std::vector<std::string> playerNames;
        std::vector<unsigned int> playerScores;
        
        int turn;
        bool isReverse;
    
        Deck deckPile; //UNO Deck
        Deck discardPile; //Discard Pile
        
        std::vector<Hand> playerHands; //Collection of All Player Hands
        
        //Tutorial
        void Intro();
        
        //Functions for Turn
        Cards* Draw();
        void Play(Cards*);
        
        //Special Card Effects
        void SkipCard();
        void ReverseCard();
        void Draw2Card();
        void WildCard();
        void Wild4Card();
        void BlankCard();
        
        
};

#endif
