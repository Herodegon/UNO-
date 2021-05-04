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

///Runs the player through an interactive tutorial for playing UNO
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

///Runs a single round of UNO, and tallies a score for the winner based on the other player's hands.
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
            Draw(playerHands.at(3), 7);
        case 3: // 3-Players
            Draw(playerHands.at(2), 7);
        case 2: // 2-Players
            Draw(playerHands.at(1), 7);
            Draw(playerHands.at(0), 7);
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

///Plays out the current player's turn (drawing, choosing a card from their hand, and checking the
///remaining cards in their hand).
void Game::Turn() {
    Hand *player = &playerHands.at(currNum);
    
    // Displays player hand at the start of turn
    playerHands.at(currNum).PrintHand();

    std::cout << "=== Top Card ===\n";
    discardPile.Top()->PrintCard();

    std::string playerChoice;
    bool exitState;
    do {
        exitState = false;
        
        do {
            fail = false;
            
            std::cout << "Would you like to \'play\' a card, or \'draw\'?\n";
            
            std::cin >> playerChoice;
            std::cout << std::endl;
            
            if((playerChoice != "play") && (playerChoice != "draw")) {
                std::cout << "Please enter \'play\' or \'draw\'.\n"
                          << std::endl;
                fail = true;
            }
        } while(isFail() == true);

        bool IsPlayCard = (playerChoice == "play"); // Checks if player wants to play a card in their hand
        bool IsSpecialCard;
        switch(IsPlayCard) {
            
            ///Draw a Card
            case 0:
                char clarify;

                //Double-Check Intention
                do {
                    fail = false;
                    
                    std::cout << "Are you sure you want to draw? Enter \'Y\' or \'N\'.\n";
                    
                    std::cin >> clarify;
                    std::cout << std::endl;
                    
                    if((clarify != 'Y') && (clarify != 'N')) {
                        std::cout << "Please enter either \'Y\' or \'N\'.\n"
                             << std::endl;
                        fail = true;
                    }
                } while(isFail() == true);

                //If No; Return To "Draw or Play"
                if(clarify == 'n') {
                    exitState = true;
                    break;
                }

                //If Yes; Draw Card
                Draw(*player, 1);

                // Display new card
                std::cout << "Card Drawn\n";
                player->Last()->PrintCard();

                // Card top
                cout << "┌   ┐" << endl;
                // Card middle
                switch(playerHand.back())
                {
                    case 10:
                        cout << "|S " << playerColors.back() << "|";
                        break;
                    case 11:
                        cout << "|R " << playerColors.back() << "|";
                        break;
                    case 12:
                        cout << "|D " << playerColors.back() << "|";
                        break;
                    case 13:
                        cout << "| W |";
                        break;
                    case 14:
                        cout << "|W 4|";
                        break;
                    case 15:
                        cout << "| B |";
                        break;
                    default:
                        cout << "|" << playerHand.back() << " " << playerColors.back() << "|";
                        break;
                }
                cout << endl;
                //Card bottom
                cout << "└   ┘" << endl << endl;

                // Check to see if new card can be played
                if((playerHand.back() != topDiscardValue) && (playerColors.back() != topDiscardColor))
                {
                    break; // New card can't be played
                }

                // Check to see if new card is special
                IsSpecialCard = ((playerHand.back() == 10) ||
                                 (playerHand.back() == 11) ||
                                 (playerHand.back() == 12) ||
                                 (playerHand.back() == 13) ||
                                 (playerHand.back() == 14) ||
                                 (playerHand.back() == 15)   );
                if(IsSpecialCard == true)
                {
                    if(SpecialCheck(playerHand, playerColors, topDiscardValue, topDiscardColor, playerHand.size() - 1) == false)
                    {
                        break;
                    }
                }

                // New card can be played = Play new card
                cout << "Your new card can be played.\n"
                     << endl;

                switch(IsSpecialCard)
                {
                    case true:
                        CardPlayed(playerHand.back(), playerColors.back(), deckValues, deckColors ,
                                   player1Hand, player1Colors, player2Hand, player2Colors         ,
                                   player3Hand, player3Colors, player4Hand, player4Colors         ,
                                   topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
                        break;

                    case false:
                        topDiscardValue = playerHand.back();
                        topDiscardColor = playerColors.back();
                        break;
                }
                playerHand.pop_back();
                playerColors.pop_back();
                break;

            case 1: // Play a Card
                int playerCardChoice = -1; // Card from 1 to their hand size that player has chosen to play
                bool FailCheck = false;    // Flag to see if card chosen is inside hand, or is correct var type

                do {
                    do {
                        // Choose a card between 1 and the maximum size of the hand
                        cout << "What card would you like to play? "
                             << "Enter a number between \'1\' and \'" << playerHand.size() << "\'.\n";
                        cout << "If you would like to go back and choose another option, enter \'0\'.\n";
                        cin >> playerCardChoice;
                        cout << endl;

                        // If the player's choice breaks the boundaries of their hand, or is the wrong input type,
                        // make them choose another card from their hand.
                        if(((playerCardChoice < 0) || (playerCardChoice > playerHand.size())) || (cin.fail()))
                        {
                            cout << "Please choose a card from your hand (with \'1\' being the first card and \'"
                                 << playerHand.size() << "\' being the last card).\n"
                                 << endl;

                            if(cin.fail()) // If the input was the wrong type i.e., string
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            FailCheck = true;
                        }
                        cout << "Test 1" << endl; // <--------------------------------------------------------- FIXME;REMOVE
                    } while(FailCheck == true);

                    if(FailCheck == false) // If the player doesn't fail the boundary check, proceed with rest of the checks
                    {
                        // If the player wants to exit their decision, return to decision options
                        if(playerCardChoice == 0)
                        {
                            cout << "Test 2" << endl; // <-------------------------------------------------- FIXME;REMOVE
                            DoesPlayerExit = true;
                            break;
                        }

                        /* TEST; IsSpecialCard Value REMOVE
                        playerHand.push_back(13);
                        playerColors.push_back('N');

                        playerCardChoice = playerHand.size();
                        */

                        IsSpecialCard = ((playerHand.at(playerCardChoice - 1) == 10) ||
                                         (playerHand.at(playerCardChoice - 1) == 11) ||
                                         (playerHand.at(playerCardChoice - 1) == 12) ||
                                         (playerHand.at(playerCardChoice - 1) == 13) ||
                                         (playerHand.at(playerCardChoice - 1) == 14) ||
                                         (playerHand.at(playerCardChoice - 1) == 15)   );

                        // If their card is special, continue to the "Special Card" section
                        if(IsSpecialCard == true)
                        {
                            break;
                        }

                        // If the top card on the discard pile is Wild or Wild 'Draw 4', continue to "Card Played" section
                        if((topDiscardValue == 13) || (topDiscardValue == 14))
                        {
                            break;
                        }

                        // If their card doesn't have the same number or color as the top card on the discard pile,
                        // make them choose another card
                        if((playerHand.at(playerCardChoice - 1) != topDiscardValue)   &&
                           (playerColors.at(playerCardChoice - 1) != topDiscardColor)   )
                        {
                            cout << "Please choose a card that matches the color or number of the top card on the "
                                 << "discard pile.\n"
                                 << endl;
                        }
                    }
                } while(((playerCardChoice < 0) || (playerCardChoice > playerHand.size())) ||
                        ((playerHand.at(playerCardChoice - 1) != topDiscardValue)    &&
                         (playerColors.at(playerCardChoice - 1) != topDiscardColor))       ||
                        (FailCheck == true)                                                  );

                // Check if special card chosen can be played
                if(IsSpecialCard == true)
                {
                    // If card cannot be played, then return to decision options
                    if(SpecialCheck(playerHand, playerColors, topDiscardValue, topDiscardColor, playerCardChoice - 1) == false)
                    {
                        DoesPlayerExit = true;
                        break;
                    }
                }

                // If player wants to return to the decision options, they do not run the following code
                if(DoesPlayerExit != true)
                {
                    // Otherwise, card is played
                    CardPlayed(playerHand.at(playerCardChoice - 1), playerColors.at(playerCardChoice - 1), deckValues, deckColors,
                               player1Hand, player1Colors, player2Hand, player2Colors                                            ,
                               player3Hand, player3Colors, player4Hand, player4Colors                                            ,
                               topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn                       );

                    // Card played is erased from player's hand
                    playerHand.erase(playerHand.begin() + (playerCardChoice - 1));
                    playerColors.erase(playerColors.begin() + (playerCardChoice - 1));
                }
                break;
        }

    } while(DoesPlayerExit == true);



}

///Checks players hand at the end of each turn to see if they either have 1 card left (calls out UNO),
///or if they have 0 (they've won the round).
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

///Converts the player's hand into points, and returns the total.
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
        
        if(deckPile.Size() == 0) {
            std::cout << "Reshuffling Deck...\n";
            deckPile = discardPile;
            deckPile.Shuffle();
        }
        
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

///Card Function: Skips the next playr's turn.
void Game::SkipCard() {
    
    if(isReverse == false) { // If player rotation is normal
        turn++;
    }
    else {                   // If player rotation is reversed
        turn--;
    }
}

///Card Function: Reverses the player order (If 3-Players: Player 3, then Player 2, then Player 1).
void Game::ReverseCard() {
    
    if(isReverse == false) { // If player rotation is normal
        isReverse = true;
    }
    else {                   // If player rotation is already reversed
        isReverse = false;
    }
}

///Card Function: Makes the next player draw 2 cards.
void Game::Draw2Card() {
    unsigned int playerDraw; //Number of Player That Draws 2 Cards
        
    for(unsigned int i = 0; i < 2; i++) { //Draw 2 Cards
        
        if(deckPile.Size() == 0) {
            std::cout << "Reshuffling Deck...";
            deckPile = discardPile;
            deckPile.Shuffle();
        }
        
        switch(isReverse) {
            //Player rotation is normal
            case false:
                playerDraw = (currNum + 1) % numPlayers;
                break;

            // Player rotation is reversed
            case true:
                playerDraw = (currNum - 1) % numPlayers;
        }
            
        Draw(playerHands.at(playerDraw), 2);
    }
}

///Card Function: Let's the player choose the color of the top card on the discard pile.
void Game::WildCard() {
    
    char playerColorChoice;
    
    do {
        fail = false;
        
        //Player Input for Color
        std::cout << "What color would you like the discard pile to be? Enter \'B\', \'G\', \'R\', or \'Y\'.\n";
        std::cin >> playerColorChoice;
        std::cout << std::endl;
        
        //Assign Color to Top of Discard Pile
        unsigned int color;
        switch(playerColorChoice) {
            case 'B':
                color = BLUE;
            case 'G':
                color = GREEN;
                break;
            case 'R':
                color = RED;
                break;
            case 'Y':
                color = YELLOW;
                break;
            default:
                std::cout << "Please enter a color.\n" << std::endl;
                std::cin.ignore();
                fail = true;
                break;
                
        }
        
        discardPile.Top()->Info_SetColor(color);
    } while(isFail() == true);
}

///Card Function: If the player has no other card in their hand they can play:
///                   1) Player chooses the color of the top card on the
///                      discard pile.
///                   2) Next player must draw 2 cards.
///                   3) Next player loses their turn.
void Game::Wild4Card() {
    
    //Player Chooses Top Color of Discard Pile
    WildCard();
    
    //Then, the Next Player Must Draw 4 Cards
    for(unsigned int i = 0; i < 2; i++) {
        Draw2Card();
    }
    
    //Then, the Next Player's Turn is Skipped
    SkipCard();
}

///Card Function: Allows the player to choose the number value and color of the top card on the discard pile.
void Game::BlankCard() {
    unsigned int blankValue;
    unsigned int blankColor;

    do {
        fail = false;
                    
        std::cout << "Choose your card value. Enter a number between \'0\' and \'9\'.\n";
                              
        std::cin >> blankValue;
        std::cout << std::endl;
                    
        if((blankValue < 0) || (blankValue > 9)) {
            std::cout << "Please enter a valid number.\n";
            fail = true;
        }
    } while(isFail() == true);
    
    
    char playerColor;
    do {
        fail = false;
                    
        std::cout << "Choose your card color. Enter \'B\', \'G\', "
                  << "\'R\', or \'Y\'.\n";
                         
        std::cin >> playerColor;
        std::cout << std::endl;
                    
        if((playerColor != 'B') && (playerColor != 'G') &&
           (playerColor != 'R') && (playerColor != 'Y')) {
            std::cout << "Please enter a valid color.\n";
            fail = true;
        }
        else {
            switch(playerColor) {
                case 'B':
                    blankColor = BLUE;
                case 'G':
                    blankColor = GREEN;
                case 'R':
                    blankColor = RED;
                case 'Y':
                    blankColor = YELLOW;
            }
        }
    } while(isFail() == true);
    
    discardPile.Top()->Info_SetNumVal(blankValue);
    discardPile.Top()->Info_SetColor(blankColor);
}
