#ifndef GAME_H
#define GAME_H

#include <fstream>

#include "../Cards/Deck.h"
#include "../Cards/Hand.h"

class Game {
    public:
        Game();
        ~Game();
        
        //Screen Clear Function
        void Clear() const;
        
        //Runs Through 1 Round of UNO
        void GameState();
        
        //Runs Through Player Turn
        void Turn();
        
        void Draw(Hand &player, unsigned int numCards);
        void Play(Hand &player, unsigned int cardInHand);
        
        //Win State Check
        bool WinCheck() const;
        
        //Score Announcement
        void PrintScores() ;
        
        //Error Test
        bool canPlay(Cards *card) const;
        bool isFail() const {return fail == true;}
    
    private:
        unsigned int numPlayers;
        std::vector<std::string> playerNames;
        std::vector<unsigned int> playerScores;
        
        int turn = 0;
        bool isReverse = false;
    
        Deck deckPile; //UNO Deck
        Deck discardPile; //Discard Pile
        
        std::vector<Hand> playerHands; //Collection of All Player Hands
        
        //Info Per Turn
        unsigned int currNum; //Integer Representing Current Player
        Hand* currPlayer;     //Current Player's Hand
        std::string currName; //Current Player's Name
        
        //Start of Game
        void Intro();
        void Tutorial() const;
        
        //Scoring System
        unsigned int TallyHands();
        
        //Special Card Effects
        void SkipCard();
        void ReverseCard();
        void Draw2Card();
        void WildCard();
        void Wild4Card();
        void BlankCard(Cards *card);
        
        bool fail = false;
};

#endif
