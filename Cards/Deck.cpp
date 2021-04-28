#include "Deck.h"

void Deck::Shuffle() {

    //Reset Deck
    deck.resize(0);

    //Build / Rebuild Deck
    for(int i = 0; i < 4; i++) {                        //#'s w/ COLORS = 76 CARDS                                                  
        for(int k = 0; k <= 9; k++) {                       //1 '0' for each color
            for(int j = 0; j < 2; j++) {                //2 of each number (1-9) for each color
                Cards *newCard = new Number(k, i);
                
                deck.push_back(newCard);
            }
        }
        
        for(int k = 10; k <= 12; k++) {                 //SPECIAL CARDS w/ COLORS = 24 CARDS                                     
            for(int j = 0; j < 2; j++) {                    //Skip ('10'); Reverse ('11'); Draw ('12')
                Cards *newCard;                         //2 of each special card for each color
                
                switch(k) {
                    case SKIP:
                        newCard = new Skip(i);
                        break;
                    case REVERSE:
                        newCard = new Reverse(i);
                        break;
                    case DRAW2:
                        newCard = new Draw2(i);
                        break;
                }
                
                deck.push_back(newCard);
            }
        }
    }
    
    for(int i = 13; i <= 15; i++) {                     //NEUTRAL CARDS = 12 CARDS                                                    
        for(int j = 0; j < 4; j++) {                        //Wild ('13'), Wild Draw 4 ('14'), Blank ('15')
            Cards *newCard;                             //4 of each type
            
            switch(i) {
                case WILD:
                    newCard = new Wild();
                    break;
                case WILD4:
                    newCard = new Wild4();
                    break;
                case BLANK:
                    newCard = new Blank();
                    break;
            }
            
            deck.push_back(newCard);
        }
    }
}
