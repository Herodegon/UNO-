#include "Game.h"

Game::Game() {
    
    //Tutorial and Get Number/Names of Players
    Intro();
    
    //Shuffle Deck
    deckPile.Shuffle();
}

void Game::Intro() {
    
    //Intro
    std::cout << "UNO++ v2.0\n"
              << std::endl;

    //Ask If They Would Like A Tutorial
    do {
        std::cout << "Would you like to play the tutorial? Enter \'y\' or \'n\'.\n";
        std::cin.get();
        
        if((std::cin.get() != 'y') && (std::cin.get() != 'n'))
        {
            std::cout << "Please enter \'y\' or \'n\'.\n"
                      << std::endl;
        }
    } while((std::cin.get() != 'y') && (std::cin.get() != 'n'));

    //Run the tutorial if they respond with 'y'
    if(std::cin.get() == 'y') {
        Tutorial();
    }
    
    std::cin.clear();

    //# of players
    do {
        std::cout << "How many players are there? "
                  << "Enter a number between \'2\' and \'4\'.\n";
        
        std::cin >> numPlayers;
        //Player Number Check (Must be number between 2 and 4)
        if(((numPlayers < 2) || (numPlayers > 4)) || (std::cin.fail())) { 
            std::cout << std::endl << "Please enter a number between \'2\' and \'4\'.\n";

            if(std::cin.fail()) { //If input was wrong input type i.e., word, clear and ignore input
                std::cin.clear();
                std::cin.ignore();
            }
        }
    } while((numPlayers < 2) || (numPlayers > 4));
    std::cout << std::endl;

    //Player names
    playerNames.resize(numPlayers);
    for(size_t i = 0; i < numPlayers; i++) {
        do {
            std::cout << "Please enter Player " << i + 1 << "\'s name.\n";
            std::cin >> playerNames.at(i);
            std::cout << std::endl;
            
            //Character Length Check (Name must be less than 15 chars)
            if(playerNames.at(i).size() > 15) {
                std::cout << "Please use a shorter name (less than 15 characters).\n";
            }
        } while(playerNames.at(i).size() > 15);
    }
    std::cout << std::endl;

    /*NOTE: Player order is dictated by the order in which the names
             where typed.

       Ex)   # of Players = 2
             playerNames.at(0) = John; playerNames.at(1) = George

             Therefore:
             John goes first, George goes second
    */
}

//Runs the player through an interactive tutorial for playing UNO
void Game::Tutorial() const {
    
    std::string str; //Output string
    std::ostringstream inp;
    int endSec; //Flag to see if the line contains "Press 'Enter' to continue..."

    std::ifstream tutorial; //File variable for "tutorial.txt"

    tutorial.open("tutorial.txt");
    if(tutorial.is_open()) {
        while(getline(tutorial, str)) { //Output lines from "tutorial.txt" until it hits a line with "Press 'Enter' to continue..."
            endSec = str.find("Press \'Enter\' to continue...");

            inp << str << std::endl;
            if(endSec == 0) {
                std::cout << inp.str() << std::endl;
                inp.flush();
                
                std::cin.get();
                std::cin.ignore();
            }
        }
    }
    tutorial.close();
    std::cout << "END OF TUTORIAL\n";
}

//!TODO: REWRITE FUNCTION
//Runs a single round of UNO, and tallies a score for the winner based on the other player's hands.
void PlayUno() {
    int currTurn = 0;
    bool PlayerPlayedLastCard = false;
    int winnerNum = -1;

    // Shuffle Deck
    DeckShuffle(deckValues, deckColors);

    // Create Discard Pile
    int topDiscardValue = deckValues.back();
    char topDiscardColor = deckColors.back();

    deckValues.pop_back();
    deckColors.pop_back();

    // Check discard card drawn for special cases
    switch(topDiscardValue)
    {
        case 15: // If the card is Blank, choose a random number and color
            topDiscardValue = rand() % 10;

        case 13: // If the card is Wild/Wild 'Draw 4', choose a random color
        case 14:
            char Colors[4] = {'B', 'G', 'R', 'Y'};
            topDiscardColor = Colors[rand() % 4];
            break;
    }

    // Draw Cards for Players
    switch(numPlayers)
    {
        case 4: // 4-Players
            Draw(playerHands.at(3))
        case 3: // 3-Players
            Draw(playerHands.at(2));
        case 2: // 2-Players
            Draw(playerHands.at(1));
            Draw(playerHands.at(0));
    }

    // Run player turns while no one has played their last card
    bool IsReverse = false;
    do {
        cout << "Player Turn Runs" << endl; // <--------------------------------------------------------- FIXME; REMOVE
        cout << "=== " << playerNames.at(currTurn % numPlayers) << "\'s Turn ===" << endl;
        switch(currTurn % numPlayers)
        {
            // Player 1's Turn
            case 0:
                Turn();
                WinCheck();
                break;
            // Player 2's Turn
            case 1:
                Turn();
                WinCheck();
                break;
            // Player 3's Turn
            case 2:
                Turn();
                WinCheck();
                break;
            // Player 4's Turn
            case 3:
                Turn();
                WinCheck();
                break;
        }

        // Next Player
        if(IsReverse == true)
        {
            if(currTurn == 0)
            {
                currTurn = numPlayers;
            }
            currTurn--;
        }
        else {
            currTurn++;
        }

        // End of Turn Summary
        if(PlayerPlayedLastCard != true)
        {
            cout << "=== End of Turn ===\n";
            DisplayTopDiscardCard(topDiscardValue, topDiscardColor); // Displays new top discard card

            cout << "Next up is " << playerNames.at(currTurn % numPlayers) << "'s turn.\n"; // Alerts next player

            // Obtains null input, then discards it to simulate "Press 'enter' to continue..."
            cout << "Press \'Enter\' to continue...\n";
            cin.get();
            cin.ignore();
        }

    } while(PlayerPlayedLastCard != true);

    playerScores.at(winnerNum) += ScoreTally(player1Hand, player2Hand, player3Hand, player4Hand);
}

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

//!TODO: REWRITE FUNCTION
// Checks players hand at the end of each turn to see if they either have 1 card left (calls out UNO),
// or if they have 0 (they've won the round).
void WinCheck(const string playerName, const int playerNum,
              const vector<int> playerHand, const vector<char> playerColors,
              bool& HasPlayerWon, int& winnerNum                            )
{
    // Does player have UNO?
    if((playerHand.size() == 1) && (playerColors.size() == 1))
    {
        cout << playerName << " has called UNO!\n";
        cout << endl;
    }
    // Has player won?
    else if((playerHand.size() == 0) && (playerColors.size() == 0))
    {
        HasPlayerWon = true;
        cout << playerName << " won the round!\n";
        cout << endl;

        winnerNum = playerNum;
    }
    // Player hasn't won and doesn't have UNO
    else {
    }
}

//!TODO: REWRITE FUNCTION
// Tallies up the score values of the playing hands to add to the round winner's total score.
int ScoreTally() const {
    int sum = 0;
    sum += CountHandScore(player1Hand);
    sum += CountHandScore(player2Hand);
    sum += CountHandScore(player3Hand);
    sum += CountHandScore(player4Hand);

    return sum;
}

//!TODO: REWRITE FUNCTION
// Converts the player's hand into points, and returns the total.
int CountHandScore() const {
    /*================================================================
      ==  Point Conversion Table                                    ==
      ==  o Numbered Cards (0-9) -> Face Value                      ==
      ==  o Skip                 -> 20 Points                       ==
      ==  o Reverse              -> 20 Points                       ==
      ==  o 'Draw 2'             -> 20 Points                       ==
      ==  o Wild                 -> 50 Points                       ==
      ==  o Wild 'Draw 4'        -> 50 Points                       ==
      ==  o Blank                -> Don't Count                     ==
      ================================================================*/
    int handSum = 0;

    if(playerHand.size() != 0) {
        for(int i = 0; i < playerHand.size(); i++) {
            switch(playerHand.at(i)) {
                case 10:
                case 11:
                case 12:
                    handSum += 20;
                    break;
                case 13:
                case 14:
                    handSum += 50;
                    break;
                case 15:
                    break;
                default:
                    handSum += playerHand.at(i);
                    break;
            }
        }
    }

    return handSum;
}
