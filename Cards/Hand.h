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
        unsigned int Front() const {return 0;}
        unsigned int Back() const {return hand.size() - 1;}
        
        Cards* At(unsigned int i) const {return hand.at(i);}
        Cards* First() const {return hand.front();}
        Cards* Last() const {return hand.back();}
        
        //Hand Manipulators
        void Push_Back(Cards *card) {hand.push_back(card);}
        void Pop(unsigned int i) {hand.erase(hand.begin()+i);}
        void Pop_Back() {hand.pop_back();}
        
    private:
        std::vector<Cards*> hand;
};

#endif
