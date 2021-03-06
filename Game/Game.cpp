#include "Game.h"

Game::Game() {
    
    //Tutorial and Get Number/Names of Players
    Intro();
}

void Game::Clear() const {
    
    for(unsigned int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }
}

void Game::Intro() {
    
    //Intro
    std::cout << "UNO++ v2.0\n"
              << std::endl;

    //Ask If They Would Like A Tutorial
    char tutorialChoice;
    do {
        fail = false;
        
        std::cout << "Would you like to play the tutorial? Enter \'Y\' or \'N\'.\n";
        std::cin >> tutorialChoice;
        
        if((tutorialChoice != 'Y') && (tutorialChoice != 'N')) {
            std::cout << "Please enter \'Y\' or \'N\'.\n"
                      << std::endl;
            fail = true;
        }
    } while(isFail() == true);

    //If 'Y'; Run Tutorial
    if(tutorialChoice == 'Y') {
        Tutorial();
    }
    
    std::cout << std::endl;

    //Declare Number of Players
    do {
        fail = false;
        
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
            
            fail = true;
        }
    } while(isFail() == true);
    std::cout << std::endl;

    //Resize Player Elements
    playerNames.resize(numPlayers);
    playerHands.resize(numPlayers);
    playerScores.resize(numPlayers);
    
    for(size_t i = 0; i < numPlayers; i++) {
        do {
            std::cout << "Please enter Player " << i + 1 << "\'s name.\n";
            std::cin >> playerNames.at(i);
            std::cout << std::endl;
            
            //Character Length Check (Name must be less than 15 chars)
            if(playerNames.at(i).size() > 15) {
                std::cout << "Please use a shorter name (less than 15 characters).\n";
                fail = true;
            }
        } while(isFail() == true);
    }
    std::cout << std::endl;

    /*NOTE: Player order is dictated by the order in which the names
             where typed.

       Ex)   # of Players = 2
             playerNames.at(0) = John; playerNames.at(1) = George

             Therefore:
             John goes first, George goes second
    */
    
    //Clear Terminal
    Clear();
}

///Runs the player through an interactive tutorial for playing UNO
void Game::Tutorial() const {
    std::string str; //Output string
    std::ostringstream inp;
    int endSec; //Flag to see if the line contains "Press 'Enter' to continue..."

    std::ifstream tutorial; //File variable for "tutorial.txt"
    
    //Clear Terminal for Cohesive Tutorial
    Clear();

    tutorial.open("Game/tutorial.txt");
    if(tutorial.is_open()) {
        while(getline(tutorial, str)) { //Output lines from "tutorial.txt" until it hits a line with "Press 'Enter' to continue..."
            endSec = str.find("Press \'Enter\' to continue...");

            inp << str << std::endl;
            if(endSec == 0) {
                //Clear to Seperate Tutorial Sections
                Clear();
                
                //Output Tutorial Section
                std::cout << inp.str() << std::endl;
                
                //Get Empty Output; Clear StringStream
                std::cin.get();
                std::cin.ignore();
                inp.str("");
            }
        }
    }
    else {
        std::cout << "ERROR: Tutorial Failed to Open.\n"
                  << std::endl;
    }
    
    tutorial.close();
    std::cout << "END OF TUTORIAL\n";
}

/*****************************************************/

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
        
        case BLANK:
            discardPile.Top()->Info_SetNumVal(rand() % 10);
            ///Continue to next case
        
        case WILD:  
        case WILD4:
            discardPile.Top()->Info_SetColor(rand() % NUM_COLORS);
            break;
            
        //If Not Wild, Wild4, Blank; Do Nothing
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
    
    //!playerHands.at(0).SetDebugHand(); ///<---------------------------------------------- FIXME; REMOVE

    //Play Turns Until One Player Has No Cards Remaining
    do {
        currNum = turn % numPlayers;
        
        //Retrieve Curr Player's Hand and Name
        currPlayer = &playerHands.at(currNum);
        currName = playerNames.at(currNum);
        
        //Announce Who's Turn It Is
        std::cout << "=== " << currName << "'s Turn ===\n";
        
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
        
        std::cout << "End Hand\n";
        currPlayer->PrintHand();
            
        std::cout << "Top Card on Discard Pile\n";
        discardPile.Top()->PrintCard();
        std::cout << std::endl;
            
        std::cout << "Next up is " << playerNames.at(turn % numPlayers) << std::endl
                  << std::endl
                  << "Press \'Enter\' to continue...\n";
        std::cin.get();
        std::cin.ignore();
        
        Clear();
    } while(WinCheck() == false);
    
    //Calculate Winner's Score
    playerScores.at(currNum) += TallyHands();
}

///Plays out the current player's turn (drawing, choosing a card from their hand, and checking the
///remaining cards in their hand).
void Game::Turn() {
    std::string playerChoice;
    bool exitState;
    
    do {
        //Set to True When Player Can Leave
        exitState = false;
        
        do {
            fail = false;
            
            //Display Player Hand
            playerHands.at(currNum).PrintHand();

            std::cout << "=== Top Card ===\n";
            discardPile.Top()->PrintCard();
            
            std::cout << "Would you like to \'play\' a card, or \'draw\'?\n";
            
            std::cin >> playerChoice;
            std::cout << std::endl;
            
            if((playerChoice != "play") && (playerChoice != "draw")) {
                std::cout << "Please enter \'play\' or \'draw\'.\n"
                          << std::endl;
                fail = true;
            }
        } while(isFail() == true);

        bool isPlay = (playerChoice == "play"); //Player's Decision
        switch(isPlay) {
            
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
                if(clarify == 'N') {
                    break;
                }

                //If Yes; Draw Card
                Draw(*currPlayer, 1);

                //Display New Card
                std::cout << "Card Drawn\n";
                currPlayer->Last()->PrintCard();

                // Check to see if new card can be played
                if(canPlay(currPlayer->Last()) == true) {
                    std::cout << "Your new card can be played.\n"
                              << std::endl;
                    Play(*currPlayer, currPlayer->Back());
                    exitState = true;
                }
                else {
                    std::cout << "Card can't be played.\n"
                              << "Press \'Enter\' to continue...\n";
                    
                    std::cin.get();
                    std::cin.ignore();
                    Clear();
                }
                break;

            ///Play a Card
            case 1:
                unsigned int cardChoice; //Card from 1 to their hand size that player has chosen to play

                do {
                    do {
                        fail = false;
                        
                        //Choose a card between 1 and the maximum size of the hand
                        std::cout << "What card would you like to play? "
                                  << "Enter a number between \'1\' and \'" << currPlayer->Size() << "\'.\n"
                                  << "If you would like to go back and choose another option, enter \'0\'.\n";
                                  
                        std::cin >> cardChoice;
                        std::cout << std::endl;

                        //If choice breaks input or exceeds hand,
                        //reobtain player choice
                        if(((cardChoice < 0) || (cardChoice > currPlayer->Size())) || (std::cin.fail())) {
                            std::cout << "Please choose a card from your hand (with \'1\' being the first card and \'"
                                      << currPlayer->Size() << "\' being the last card).\n"
                                      << std::endl;

                            if(std::cin.fail()) { // If the input was the wrong type i.e., string
                                std::cin.clear();
                                std::cin.ignore();
                            }
                            
                            fail = true;
                            break;
                        }
                        
                        //If card choice is '0', return to "Draw or Play"
                        if(cardChoice == 0) {
                            break;
                        }
                        
                        //If card cannot be played, choose another card
                        if(canPlay(currPlayer->At(cardChoice-1)) == false) {
                            std::cout << "Please choose a card of matching "
                                      << "type, number, or color.\n"
                                      << std::endl;
                        }
                        //Else, player can play card
                        else {
                            exitState = true;
                        }
                    } while(canPlay(currPlayer->At(cardChoice-1)) == false);
                    
                    //Check if Input has Failed
                    if(isFail() == false) {
                        
                        //Continue to Exit
                        if(exitState == false) {
                            break;
                        }
                        //If Not Exit; Play Card and End Turn
                        else {
                            Play(*currPlayer, cardChoice-1);
                        }
                    }
                } while(isFail() == true);
                break;
        }
    } while(exitState == false); //While 'False'; Cannot Exit Turn
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

/*****************************************************/

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
    
    Hand *playerHand;
    CardType cardType;
    for(unsigned int i = 0; i < numPlayers; i++) {
        playerHand = &playerHands.at(i);
        
        if(playerHand->Size() != 0) {
            for(unsigned int k = 0; k < playerHand->Size(); k++) {
                cardType = playerHand->At(k)->Info_GetType();
                
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
                        sum += playerHand->At(k)->Info_GetNumVal();
                        break;
                }
            }
        }
    }

    return sum;
}

void Game::PrintScores() {
    
    std::cout << "=== Final Scores ===\n"
              << std::endl;
    
    unsigned int winnerNum;      
    for(unsigned int i = 0; i < numPlayers; i++) {
        unsigned int score = 0;
        unsigned int playerNum;
        
        for(unsigned int k = 0; k < numPlayers; k++) {
            
            if(score < playerScores.at(k)) {
                score = playerScores.at(k);
                playerNum = k;
            }
        }
        std::cout << i + 1 << " (" << playerNames.at(i) << ") | "
                  << score << " Points\n";
        
        if(i == 0) {
            winnerNum = playerNum;
        }
        
        playerScores.at(playerNum) = 0;
    }
    std::cout << std::endl;
    
    std::cout << "Congratulations, " << playerNames.at(winnerNum) << "! "
              << "You won!\n"
              << std::endl;
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
    
    //Blank Does Not Push Card
    if(card->Info_GetType() != BLANK) {
        discardPile.Push_Back(card);
    }
    
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
            BlankCard(card);
            discardPile.Push_Back(card);
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
            break;
    }
            
    Draw(playerHands.at(playerDraw), 2);
}

///Card Function: Let's the player choose the color of the top card on the discard pile.
void Game::WildCard() {
    char playerColorChoice;
    unsigned int color;
    
    do {
        fail = false;
        
        //Player Input for Color
        std::cout << "What color would you like the discard pile to be? Enter \'B\', \'G\', \'R\', or \'Y\'.\n";
        
        std::cin >> playerColorChoice;
        std::cout << std::endl;
        
        //Assign Color to Top of Discard Pile
        switch(playerColorChoice) {
            case 'B':
                color = BLUE;
                break;
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
        
    } while(isFail() == true);
    
    discardPile.Top()->Info_SetColor(color);
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
void Game::BlankCard(Cards *card) {
    Cards *topCard = discardPile.Top();
    int blankValue;
    CardColor blankColor;
    
    bool sameNum = false;
    
    do {
        fail = false;
        
        std::cout << "Choose your card value. Enter a number between \'0\' and \'9\'.\n";
                              
        std::cin >> blankValue;
        std::cout << std::endl;
        
        if((blankValue < 0) || (blankValue > 9)) {
            std::cout << "Please enter a valid number.\n";
            fail = true;
        }
        else if(blankValue == topCard->Info_GetNumVal()) {
            sameNum = true;
        }
    } while(isFail() == true);
    
    //If CardNum is Same as Discard; Player Chooses Card Color
    if(sameNum == true) {
        char playerColor;
        
        do {
            fail = false;
                        
            std::cout << "Choose your card's color. Enter \'B\', \'G\', "
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
                        break;
                    case 'G':
                        blankColor = GREEN;
                        break;
                    case 'R':
                        blankColor = RED;
                        break;
                    case 'Y':
                        blankColor = YELLOW;
                        break;
                }
            }
        } while(isFail() == true);
    }
    else {
        blankColor = topCard->Info_GetColor();
    }
    
    card->Info_SetNumVal(blankValue);
    card->Info_SetColor(blankColor);
}

bool Game::canPlay(Cards* card) const {
    Cards *topCard = discardPile.Top();
    bool isNumber = (card->Info_GetType() == NUMBER);
    
    if((isNumber == true) && (card->Info_GetNumVal() == topCard->Info_GetNumVal())) {
        return true;
    }
    else if((isNumber == false) && (card->Info_GetType() == topCard->Info_GetType())) {
        return true;
    }
    else if(card->Info_GetColor() == topCard->Info_GetColor()) {
        return true;
    }
    
    switch(card->Info_GetType()) {
        case WILD:
        case WILD4:
        case BLANK:
            return true;
        default:
            break;
    }
    
    return false;
}
