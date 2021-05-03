#ifndef HAND_H
#define HAND_H

#include <vector>

#include "Cards.h"

class Hand {
    public:
        ~Hand();
        
        //Print Out Player's Hand
        void PrintHand() const;
        
        //Hand Accessors
        unsigned int Size() const {return hand.size();}
        
        Cards* At(unsigned int i) const {return hand.at(i);}
        
        //Hand Manipulators
        void Push_Back(Cards *card) {hand.push_back(card);}
        void Pop(unsigned int i) {hand.erase(hand.begin()+i);}
        
    private:
        std::vector<Cards*> hand;
};

#endif
