#include "Cards.h"

char Cards::GetColor() {
    switch(cardInfo.color) {
        case BLUE:
            return 'B';
        case GREEN:
            return 'G';
        case RED:
            return 'R';
        case YELLOW:
            return 'Y';
    }
}

/*****************************************************/

//!TODO: FINISH FUNCTION
//Card Function: Skips the next playr's turn.
void SkipCard() {
    
    if(IsReverse == false) // If player rotation is normal
    {
        currTurn++;
    }
    else {                 // If player rotation is reversed
        currTurn--;
    }
}

//!TODO: FINISH FUNCTION
//Card Function: Reverses the player order (If 3-Players: Player 3, then Player 2, then Player 1).
void ReverseCard() {
    
    if(IsReverse == false) // If player rotation is normal
    {
        IsReverse = true;
    }
    else {                 // If player rotation is already reversed
        IsReverse = false;
    }
}

//!TODO: FINISH FUNCTION
//Card Function: Makes the next player draw 2 cards.
void Draw2Card() {
    
    if((deckValues.size() != 0) && (deckColors.size() != 0))
    {
        for(int i = 0; i < 2; i++) // Draw 2 Cards
        {
            switch(IsReverse)
            {
                // Player rotation is normal
                case false:
                    // If player is last player, make first player draw
                    if((playerNum + 1) == numPlayers)
                    {
                        player1Hand.push_back(deckValues.back());
                        player1Colors.push_back(deckColors.back());
                    }
                    else {
                        switch(playerNum) // Player that has to draw
                        {
                            case 0: // Player 1
                                player2Hand.push_back(deckValues.back());
                                player2Colors.push_back(deckColors.back());
                                break;
                            case 1: // Player 2
                                player3Hand.push_back(deckValues.back());
                                player3Colors.push_back(deckColors.back());
                                break;
                            case 2: // Player 3
                                player4Hand.push_back(deckValues.back());
                                player4Colors.push_back(deckColors.back());
                                break;
                        }
                    }
                    break;

                // Player rotation is reversed
                case true:
                    // If player is first player, make the last player draw i.e., # of players
                    if(playerNum == 0)
                    {
                        playerNum = numPlayers;
                    }
                    switch(playerNum) // Player that has to draw
                    {
                        case 1: // Player 2
                            player1Hand.push_back(deckValues.back());
                            player1Colors.push_back(deckColors.back());
                            break;
                        case 2: // Player 3
                            player2Hand.push_back(deckValues.back());
                            player2Colors.push_back(deckColors.back());
                            break;
                        case 3: // Player 4
                            player3Hand.push_back(deckValues.back());
                            player3Colors.push_back(deckColors.back());
                            break;
                    }
                    break;
            }

            // Erase drawn card from deck
            deckValues.pop_back();
            deckColors.pop_back();
        }
    }
    else {
        cout << "Deck is empty\n";
        DeckBuilder(deckValues, deckColors);
        DeckShuffle(deckValues, deckColors);
    }
}

//!TODO: FINISH FUNCTION
//Card Function: Let's the player choose the color of the top card on the discard pile.
void WildCard() {
    
    char playerColorChoice;
    do {
        cout << "What color would you like the discard pile to be? Enter \'B\', \'G\', \'R\', or \'Y\'.\n";
        cin >> playerColorChoice;
        cout << endl;
        if((playerColorChoice != 'B') && (playerColorChoice != 'G') &&
           (playerColorChoice != 'R') && (playerColorChoice != 'Y'))
        {
            cout << "Please enter a valid color.\n";
        }
    } while((playerColorChoice != 'B') && (playerColorChoice != 'G') &&
            (playerColorChoice != 'R') && (playerColorChoice != 'Y'));

    topDiscardColor = playerColorChoice;
}

//!TODO: FINISH FUNCTION
//Card Function: If the player has no other card in their hand they can play:
//                   1) Player chooses the color of the top card on the
//                      discard pile.
//                   2) Next player must draw 2 cards.
//                   3) Next player loses their turn.
void Wild4Card() {
    
    WildCard();

    for(int i = 0; i < 2; i++)
    {
        Draw2Card(playerCardValue, playerCardColor, deckValues, deckColors       ,
                  player1Hand, player1Colors, player2Hand, player2Colors         ,
                  player3Hand, player3Colors, player4Hand, player4Colors         ,
                  topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
    }

    SkipCard(playerCardValue, playerCardColor, deckValues, deckColors       ,
             player1Hand, player1Colors, player2Hand, player2Colors         ,
             player3Hand, player3Colors, player4Hand, player4Colors         ,
             topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
}

//!TODO: FINISH FUNCTION
//Card Function: Allows the player to choose the number value and color of the top card on the discard pile.
void BlankCard() {
    string playerDecision;
    bool DoesPlayerExit = false;
    int playerChoiceValue;
    char playerChoiceColor;
    
    do {
        do {
            cout << "Would you like to match the \'value\' or \'color\' of the top card on the discard pile?\n";
            DisplayTopDiscardCard(topDiscardValue, topDiscardColor);
            cin >> playerDecision;
            cout << endl;
            if((playerDecision != "value") && (playerDecision != "color"))
            {
                cout << "Please choose either the \'value\' or \'color\'.";
            }
        } while((playerDecision != "value") && (playerDecision != "color"));

        switch(playerDecision == "value")
        {
            case 0: // Choose the number
                do {
                    cout << "Choose your card value. Enter a number between \'0\' and \'9\'. Enter \'-1\' to exit "
                         << "and choose again.\n";
                    cin >> playerChoiceValue;
                    cout << endl;
                    if(playerChoiceValue == -1)
                    {
                        DoesPlayerExit = true;
                        break;
                    }
                    else if((playerChoiceValue < 0) || (playerChoiceValue > 9))
                    {
                        cout << "Please enter a valid number.\n";
                    }
                    else {
                        topDiscardValue = playerChoiceValue;
                    }
                } while((playerChoiceValue < 0) || (playerChoiceValue > 9));
                //cout << "Blank Player Value: " << playerChoiceValue << endl; // <-------------------------------- FIXME; REMOVE
                break;

            case 1: // Choose the color
                do {
                    cout << "Choose your card color. Enter \'B\', \'G\', \'R\', or \'Y\'. Enter \'Q\' to exit "
                         << "and choose again.\n";
                    cin >> playerChoiceColor;
                    cout << endl;
                    if(playerChoiceColor == 'Q')
                    {
                        DoesPlayerExit = true;
                        break;
                    }
                    else if((playerChoiceColor != 'B') && (playerChoiceColor != 'G') &&
                            (playerChoiceColor != 'R') && (playerChoiceColor != 'Y'))
                    {
                        cout << "Please enter a valid color.\n";
                    }
                    else {
                        topDiscardColor = playerChoiceColor;
                    }
                } while((playerChoiceColor != 'B') && (playerChoiceColor != 'G') &&
                        (playerChoiceColor != 'R') && (playerChoiceColor != 'Y'));
                cout << "Blank Player Color: " << playerChoiceColor << endl; // <--------------------------------- FIXME; REMOVE
                break;

        }
    } while(DoesPlayerExit == true);
    //cout << "Blank Discard Value: " << topDiscardValue << endl; // <--------------------------------------------- FIXME; REMOVE
    //cout << "Blank Discard Color: " << topDiscardColor << endl; // <--------------------------------------------- FIXME; REMOVE
}
