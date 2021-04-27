#include "Deck.h"

void Deck::Shuffle() {
    //Card Colors = (Blue, Green, Red, Yellow)

    //Reset Deck
    deck.resize(0);

    //Build / Rebuild Deck
    for(int i = 0; i < 4; i++) {                    //#'s w/ COLORS = 76 CARDS
                                                        //1 '0' for each color
        for(int k = 0; k <= 9; k++) {               //2 of each number (1-9) for each color
            for(int j = 0; j < 2; j++) {
                Cards* newCard = new Number(k, i);
                
                deck.push_back(newCard);
            }
        }
        
        for(int j = 10; j <= 12; j++) {             //SPECIAL CARDS w/ COLORS = 24 CARDS
                                                        //Skip ('10'); Reverse ('11'); Draw ('12')
            for(int k = 0; k < 2; k++) {            //2 of each special card for each color
                deckValues.push_back(j);
                deckValuesColors.push_back(colors[i]);
            }
        }
    }
    for(int i = 13; i <= 15; i++) {                 //NEUTRAL CARDS = 12 CARDS
                                                        //Wild ('13'), Wild Draw 4 ('14'), Blank ('15')
        for(int j = 0; j < 4; j++) {                //4 of each type
        
            deckValues.push_back(i);
            deckValuesColors.push_back('N');
        }
    }
}
