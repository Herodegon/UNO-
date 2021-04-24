#include "Deck.h"

void Deck::Build() {
    char colors[4] = {'B', 'G', 'R', 'Y'};          // Card Colors = (Blue, Green, Red, Yellow)

    // Reset Deck
    deckValues.resize(0);
    deckValuesColors.resize(0);

    // Build / Rebuild Deck
    for(int i = 0; i < 4; i++)                      // #'s w/ COLORS = 76 CARDS
    {                                                   // 1 '0' for each color
        deckValues.push_back(0);                    // 2 of each number (1-9) for each color
        deckValuesColors.push_back(colors[i]);      
        for(int j = 1; j <= 9; j++)             
        {
            for(int k = 0; k < 2; k++)
            {
                deckValues.push_back(j);
                deckValuesColors.push_back(colors[i]);
            }
        }
        for(int j = 10; j <= 12; j++)               // SPECIAL CARDS w/ COLORS = 24 CARDS
        {                                               // Skip ('10'); Reverse ('11'); Draw ('12')
            for(int k = 0; k < 2; k++)              // 2 of each special card for each color
            {
                deckValues.push_back(j);
                deckValuesColors.push_back(colors[i]);
            }
        }
    }
    for(int i = 13; i <= 15; i++)                   // NEUTRAL CARDS = 12 CARDS
    {                                                   // Wild ('13'), Wild Draw 4 ('14'), Blank ('15')
        for(int j = 0; j < 4; j++)                  // 4 of each type
        {
            deckValues.push_back(i);
            deckValuesColors.push_back('N');
        }
    }

    /* TEST; DeckBuilder REMOVE
    for(int i = 0; i < deckValues.size(); i++)
    {
        cout << "[Card " << i << "] Type: " << deckValues.at(i) << " / Color: " << deckValuesColors.at(i) << endl;
    }
    cout << endl;
    */
}

void Deck::Shuffle() {

}
