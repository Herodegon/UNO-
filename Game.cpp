#include "Game.h"

Game::Game() {
    
    //Tutorial and Get Number/Names of Players
    Intro();
    
    //Shuffle Deck
    deck.Shuffle();
}

//!TODO: REWRITE FUNCTION
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

    /*TEST; Names REMOVE
    for(int i = 0; i < numPlayers; i++) {
        cout << "Player " << i + 1 << ": " << playerNames.at(i) << endl;
    }
    return 0;
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

    /* TEST; Wild Discard Card REMOVE
    topDiscardValue = 13;
    topDiscardColor = 'N';
    */

    /* TEST; Wild 'Draw 4' Discard Card REMOVE
    topDiscardValue = 14;
    topDiscardColor = 'N';
    */

    /* TEST; Blank Discard Card REMOVE
    topDiscardValue = 15;
    topDiscardColor = 'N';
    */

    /* TEST; New Discard Type REMOVE
    cout << "Top Discard Value: " << topDiscardValue << endl;
    */

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
            DrawCards(player4Hand, player4Colors, deckValues, deckColors, 1);
        case 3: // 3-Players
            DrawCards(player3Hand, player3Colors, deckValues, deckColors, 1);
        case 2: // 2-Players
            DrawCards(player2Hand, player2Colors, deckValues, deckColors, 1);
            DrawCards(player1Hand, player1Colors, deckValues, deckColors, 1);
    }

    /* TEST; Reverse Card REMOVE
    player1Hand.push_back(11);
    player1Colors.push_back('B');
    topDiscardValue = 0;
    topDiscardColor = 'B';
    */

    /* TEST; Wild Card REMOVE
    player1Hand.push_back(13);
    player1Colors.push_back('N');
    */

    /* TEST; Blank Card REMOVE
    player1Hand.push_back(15);
    player1Colors.push_back('N');
    */

    /* TEST; Win State REMOVE
    player1Hand.resize(1);
    player1Colors.resize(1);
    player1Hand.at(0) = 0;
    player1Colors.at(0) = 'B';
    topDiscardValue = 0;
    topDiscardColor = 'B';
    */

    // Run player turns while no one has played their last card
    bool IsReverse = false;
    do {
        cout << "Player Turn Runs" << endl; // <--------------------------------------------------------- FIXME; REMOVE
        cout << "=== " << playerNames.at(currTurn % numPlayers) << "\'s Turn ===" << endl;
        switch(currTurn % numPlayers)
        {
            // Player 1's Turn
            case 0:
                PlayerTurn();
                WinCheck();
                break;
            // Player 2's Turn
            case 1:
                PlayerTurn();
                WinCheck();
                break;
            // Player 3's Turn
            case 2:
                PlayerTurn();
                WinCheck();
                break;
            // Player 4's Turn
            case 3:
                PlayerTurn();
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
