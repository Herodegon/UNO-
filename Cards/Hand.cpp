#include "Hand.h"

Hand::~Hand() {
    
    for(size_t i = hand.size() - 1; i >= 0; i--) {
        
        delete hand.at(i);
    }
}

void Hand::PrintHand() const {
    
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
