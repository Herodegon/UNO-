#include "Hand.h"

Hand::~Hand() {
    
    for(size_t i = 0; i < hand.size(); i++) {
        
        delete hand.at(i);
    }
}

void Hand::PrintHand() const {
    std::ostringstream hnd; //Stringstream for Player's Hand
    
    //Card Top
    for(size_t i = 0; i < hand.size(); i++) {
        Cards *card = hand.at(i);
                
        hnd << card->Print_CardTop();
    }
    hnd << std::endl;
            
    //Card Middle
    for(size_t i = 0; i < hand.size(); i++) {
        Cards *card = hand.at(i);
                
        hnd << card->Print_CardMiddle();
    }
    hnd << std::endl;
            
    //Card Bottom
    for(size_t i = 0; i < hand.size(); i++) {
        Cards *card = hand.at(i);
                
        hnd << card->Print_CardBottom();
    }
    hnd << std::endl;
            
    //Card Number
    for(size_t i = 0; i < hand.size(); i++) {
                
        hnd << "  " << i+1 << "  ";
                
        if(i != hand.size() - 1) {
            hnd << ",";
        }
    }
    hnd << std::endl;
    
    std::cout << hnd.str() << std::endl;
}

void Hand::SetDebugHand() {
    Cards *card = new Wild;
    
    hand.resize(0);
    hand.push_back(card);
}
