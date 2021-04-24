#ifndef DECK_H
#define DECK_H

#include <vector>

#include "Cards.h"

class Deck {
    public:
        void Shuffle();
    
    private:
        std::vector<Cards*> deck;
};

#endif
