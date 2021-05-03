#include "Game.h"

Game::Game() {
    
    //Tutorial and Get Number/Names of Players
    Intro();
}

/*!TODO: FIX DECONSTRUCTOR
Game::~Game() {
    
    //Delete Decks
    delete deckPile;
    delete discardPile;
    
    //Delete Hands
    for(unsigned int i = 0; i < playerHands.size(); i++) {
        
        delete playerHands.at(i);
    }
}
*/

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
    
    //Set Player Scores
    playerScores.resize(0, numPlayers);
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

//Runs a single round of UNO, and tallies a score for the winner based on the other player's hands.
void Game::GameState() {
    
    //(Re)Build Deck and Shuffle
    deckPile.Build();
    deckPile.Shuffle();
    
    //Create Discard Pile
    discardPile.Push_Back(deckPile.Top());

    deckPile.Pop_Back();

    //Check Top Discard for Special Cases
    switch(discardPile.Top()->Info_GetType()) {
        
        //If the card is Blank, choose a random number and color
        case BLANK:
            discardPile.At(0)->Info_SetNumVal(rand() % 10);
            //Continue to Next Case
        
        //If the card is Wild/Wild 'Draw 4', choose a random color
        case WILD:  
        case WILD4:
            discardPile.At(0)->Info_SetColor(rand() % NUM_COLORS);
            break;
            
        //Else, nothing occurs
        default:
            break;
    }

    //Draw Cards for Players
    switch(numPlayers) {
        case 4: // 4-Players
            Draw(&playerHands.at(3), 7);
        case 3: // 3-Players
            Draw(&playerHands.at(2), 7);
        case 2: // 2-Players
            Draw(&playerHands.at(1), 7);
            Draw(&playerHands.at(0), 7);
    }

    //Play Turns Until One Player Has No Cards Remaining
    do {
        currNum = turn % numPlayers;
        
        //Retrieve Curr Player's Hand and Name
        currPlayer = &playerHands.at(currNum);
        currName = playerNames.at(currNum);
        
        //Announce Who's Turn It Is
        std::cout << "=== " << currName << "'s Turn ===\n"
                  << std::endl;
        
        //Execute Curr Player's Turn
        Turn();
        if(WinCheck() == true) {
            break;
        }
        
        //Cycle Turn based on  
        if(isReverse == true) {
            if(turn == 0) {
                turn = numPlayers;
            }
            turn--;
        }
        else {
            turn++;
        }

        // End of Turn Summary
        std::cout << "=== End of Turn ===\n" << std::endl;
            
        std::cout << "Top Card on Discard Pile\n";
        discardPile.Top()->PrintCard();
            
        std::cout << "Next up is " << playerNames.at(turn % numPlayers) << std::endl
                  << std::endl
                  << "Press \'Enter\' to continue...\n";
        std::cin.get();
        std::cin.ignore();
    } while(WinCheck() == false);
    
    //Calculate Winner's Score
    playerScores.at(currNum) += TallyHands();
}

// Checks players hand at the end of each turn to see if they either have 1 card left (calls out UNO),
// or if they have 0 (they've won the round).
bool Game::WinCheck() const {
    
    //Does Player Have UNO?
    if(currPlayer->Size() == 1) {
        std::cout << currName << " has called UNO!\n"
                  << std::endl;
        return false;
    }
    //Has Player Won?
    else if(currPlayer->Size() == 0) {
        std::cout << currName << " won the round!\n"
                  << std::endl;
        return true;
    }
    //No UNO or Win; Ignore function
    else {
        return false;
    }
}

// Converts the player's hand into points, and returns the total.
unsigned int Game::TallyHands() {
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
    unsigned int sum = 0;
    
    Hand playerHand;
    CardType cardType;
    for(unsigned int i = 0; i < numPlayers; i++) {
        playerHand = playerHands.at(i);
        
        if(playerHand.Size() != 0) {
            for(unsigned int k = 0; k < playerHand.Size(); k++) {
                cardType = playerHand.At(k)->Info_GetType();
                
                switch(cardType) {
                    //Reverse, Skip, or Draw 2 == 20 Points
                    case REVERSE:
                    case SKIP:
                    case DRAW2:
                        sum += 20;
                        break;
                    //Wild or Wild 4 == 50 Points
                    case WILD:
                    case WILD4:
                        sum += 50;
                        break;
                    //Blank == 0 Points
                    case BLANK:
                        break;
                    //Number == Card Value in Points
                    default:
                        sum += playerHand.At(k)->Info_GetNumVal();
                        break;
                }
            }
        }
    }

    return sum;
}

/*****************************************************/

void Game::Draw(Hand &player, unsigned int numCards) {
    
    for(unsigned int i = 0; i < numCards; i++) {
        player.Push_Back(deckPile.Top());
        
        deckPile.Pop_Back();
    }
}

void Game::Play(Hand &player, unsigned int cardInHand) {
    Cards *card = player.At(cardInHand);
    
    discardPile.Push_Back(card);
    
    switch(card->Info_GetType()) {
        case SKIP:
            SkipCard();
            break;
        case REVERSE:
            ReverseCard();
            break;
        case DRAW2:
            Draw2Card();
            break;
        case WILD:
            WildCard();
            break;
        case WILD4:
            Wild4Card();
            break;
        case BLANK:
            BlankCard();
            break;
        default:
            break;
    }
    
    player.Pop(cardInHand);
}

//!TODO: FINISH FUNCTION
//Card Function: Skips the next playr's turn.
void Game::SkipCard() {
    
    if(isReverse == false) // If player rotation is normal
    {
        turn++;
    }
    else {                 // If player rotation is reversed
        turn--;
    }
}

//!TODO: FINISH FUNCTION
//Card Function: Reverses the player order (If 3-Players: Player 3, then Player 2, then Player 1).
void Game::ReverseCard() {
    
    if(isReverse == false) // If player rotation is normal
    {
        isReverse = true;
    }
    else {                 // If player rotation is already reversed
        isReverse = false;
    }
}

//!TODO: FINISH FUNCTION
//Card Function: Makes the next player draw 2 cards.
void Game::Draw2Card() {
    
    if(deckPile.size() != 0) {
        for(int i = 0; i < 2; i++) { //Draw 2 Cards
            switch(isReverse) {
                case false: //Player rotation is normal
                    if((playerNum + 1) == numPlayers) {
                        player1Hand.push_back(deckValues.back());
                        player1Colors.push_back(deckColors.back());
                    }
                    else {
                        switch(playerNum) { // Player that has to draw
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
void Game::WildCard() {
    
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
void Game::Wild4Card() {
    
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
