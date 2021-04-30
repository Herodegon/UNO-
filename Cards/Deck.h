#ifndef DECK_H
#define DECK_H

#include <vector>

#include "Cards.h"

class Deck {
    public:
        Deck();
        
        //Operators
        void operator=(Deck deck2) {deck = deck2.deck;}
        
        //Create UNO Deck
        void Build();
        
        //Shuffle UNO Deck
        void Shuffle();
        
        //Deck Manipulators
        void Push_Back(Cards *card) {deck.push_back(card);}
        void Pop_Back() {deck.pop_back();}
        
        //Deck Accessors
        unsigned int Size() const   {return deck.size();}
        
        Cards *At(unsigned int i) const {return deck.at(i);}
        Cards *Top() const {return deck.back();}
        Cards *Bottom() const {return deck.front();}
        
    private:
        std::vector<Cards*> deck;
};

#endif
