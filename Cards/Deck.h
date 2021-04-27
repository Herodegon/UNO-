#ifndef DECK_H
#define DECK_H

#include <vector>

#include "Cards.h"

class Deck {
    public:
        Deck();
        
        //Shuffle UNO Deck
        void Shuffle();
    
    private:
        std::vector<Cards*> deck;
};

#endif
