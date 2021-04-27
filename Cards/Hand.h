#ifndef HAND_H
#define HAND_H

#include <vector>

#include "Cards.h"

class Hand {
    public:
        
        //Print Out Player's Hand
        void PrintHand() const {
            
            //Card Top
            for(size_t i = 0; i < hand.size(); i++) {
                Cards *card = hand.at(i);
                
                card->Print_CardTop();
            }
            
            //Card Middle
            for(size_t i = 0; i < hand.size(); i++) {
                Cards *card = hand.at(i);
                
                card->Print_CardMiddle();
            }
            std::cout << std::endl;
            
            //Card Bottom
            for(size_t i = 0; i < hand.size(); i++) {
                Cards *card = hand.at(i);
                
                card->Print_CardBottom();
            }
            std::cout << std::endl;
            
            //Card Number
            for(size_t i = 0; i < hand.size(); i++) {
                
                std::cout << "  " << i+1 << "  ";
                
                if(i != hand.size() - 1) {
                    std::cout << ",";
                }
            }
            std::cout << std::endl;
        }
    
    private:
        std::vector<Cards*> hand;
};

#endif
