/*=========================================================================================================
  ==  UNO                                                                                                ==
  ==  Objective:                                                                                         ==
  ==  Create a game of UNO for at least two players.                                                     ==
  ==    - Follow the basic rules of the game: https://service.mattel.com/instruction_sheets/42001pr.pdf  ==
  ==  Requirements:                                                                                      ==
  ==  Inputs                                                                                             ==
  ==    o Name of players                                                                                ==
  ==    o Any decisions the player needs to make about what card to play                                 ==
  ==    o When a player has UNO                                                                          ==
  ==  Outputs                                                                                            ==
  ==    o Player turn                                                                                    ==
  ==    o What cards the player has                                                                      ==
  ==    o What card is being played                                                                      ==
  ==    o Winner                                                                                         ==
  ==  Program Format:                                                                                    ==
  ==    o Directions & Player Name                                                                       ==
  ==    o Comments                                                                                       ==
  ==  Each Participant should be able to:                                                                ==
  ==    o Explain each line of code                                                                      ==
  ==  Program Components                                                                                 ==
  ==    o Branching                                                                                      ==
  ==    o User defined function                                                                          ==
  ==    o Array                                                                                          ==
  ==    o Loop                                                                                           ==
  ==    o Random Number Generator                                                                        ==
  ==  Creative Liberties                                                                                 ==
  ==    o Number of players                                                                              ==
  ==    o Visual display                                                                                 ==
  =========================================================================================================*/

/*=========================================================================================================
  ==  [Milestones]                                                                                       ==
  ==  [√] Required Inputs                                                                                ==
  ==    [√] Player Names                                                                                 ==
  ==    [√] Player Decisions                                                                             ==
  ==    [√] When a Player has UNO                                                                        ==
  ==  [√] Required Outputs                                                                               ==
  ==    [√] Current Turn                                                                                 ==
  ==    [√] Player's Hand                                                                                ==
  ==    [√] Current Card Being Played                                                                    ==
  ==    [√] Winner Who Declared UNO (and their points)                                                   ==
  ==  [√] Program Format                                                                                 ==
  ==    [√] Comments with Directions on How to Play UNO                                                  ==
  ==    [√] Comments about the Function of Various Aspects of Program                                    ==
  ==  [√] Program Components                                                                             ==
  ==    [√] Branching                                                                                    ==
  ==    [√] User Defined Functions                                                                       ==
  ==    [√] Arrays                                                                                       ==
  ==    [√] Loops                                                                                        ==
  ==    [√] Random Number Generation                                                                     ==
  ==  [√] Optional Components                                                                            ==
  ==    [√] Tutorial                                                                                     ==
  =========================================================================================================*/

/*=========================================================================================================
  ==  [Ronald Jock]                                                                                      ==
  ==  [√] My Input: Any decisions the player needs to make about what card to play                       ==
  ==  [√] My Output: What cards the player has                                                           ==
  =========================================================================================================*/

/*=========================================================================================================
  ==  [Denaujay]                                                                                         ==
  ==  []                                                                                                 ==
  ==  [√] My Output: Win Statement                                                                       ==
  =========================================================================================================*/

/*=========================================================================================================
  ==  [Chris]                                                                                            ==
  ==  []                                                                                                 ==
  ==  []                                                                                                 ==
  =========================================================================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

// Function Prototype for Tutorial
void Tutorial();
// Function Prototype for DeckBuilder
void DeckBuilder(vector<int>& deckValues, vector<char>& deckValuesColors);
// Function Prototype for DeckShuffle
void DeckShuffle(vector<int>& deckValues, vector<char>& deckValuesColors);
// Function Prototype for DrawCards
void DrawCards(vector<int>& playerHand, vector<char>& playerHandColors  ,
               vector<int>& deckValues,vector<char>& deckColors         ,
               const bool GameStart                                      );
// Function Prototype for DisplayPlayerHand
void DisplayPlayerHand(const vector<int> playerHand, const vector<char> playerHandColors);
// Function Prototype for PlayUno
void PlayUno(vector<int>& player1Hand, vector<char>& player1Colors ,
             vector<int>& player2Hand, vector<char>& player2Colors ,
             vector<int>& player3Hand, vector<char>& player3Colors ,
             vector<int>& player4Hand, vector<char>& player4Colors ,
             vector<int>& deckValues , vector<char>& deckColors    ,
             vector<string>& playerNames, vector<int>& playerScores,
             int numPlayers                                         );
// Function Prototype for SpecialCheck
bool SpecialCheck(const vector<int> playerHand, const vector<char> playerColors,
                  const int topDiscardValue, const char topDiscardColor        ,
                  int playerCardChoice                                          );
// Function Prototype for PlayerTurn
void PlayerTurn(vector<int>& playerHand, vector<char>& playerColors, vector<int>& deckValues, vector<char>& deckColors      ,
                vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool& IsReverse, int& currTurn   );
// Function Prototype for CardPlayed
void CardPlayed(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool& IsReverse, int& currTurn   );
// Function Prototypes for the Special cards
    // Skip Card
    void SkipCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                  vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                  vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                  int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    );
    // Reverse Card
    void ReverseCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                     vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                     vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                     int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool& IsReverse, int& currTurn   );
    // 'Draw 2' Card
    void Draw2Card(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                   vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                   vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                   int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    );
    // Wild Card
    void WildCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                  vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                  vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                  int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    );
    // Wild 'Draw 4' Card
    void Wild4Card(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                   vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                   vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                   int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    );
    // Blank Card
    void BlankCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                   vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                   vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                   int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    );
// Function Prototype for WinCheck
void WinCheck(const string playerName, const int playerNum                 ,
              const vector<int> playerHand, const vector<char> playerColors,
              bool& HasPlayerWon, int& winnerNum                            );
// Function Prototype for ScoreTally
int ScoreTally(vector<int> player1Hand, vector<int> player2Hand,
               vector<int> player3Hand, vector<int> player4Hand );
// Function Prototype for CountHandScore
int CountHandScore(const vector<int> playerHand);



/************************************************************************************************************************/
/************************************************************************************************************************/



// === UNO Card Game ===
int main()
{
    /*!MOVED "Game.h"; REMOVE
    char playTutorial = 'a';         // Check if players want to go through gamerules
    int numPlayers = 2;              // Total # of players (Default 2)
    vector<string> playerNames;      // Names of players
    vector<int> playerScores(4, 0);  // Total scores for each player

    // Intro
    cout << "UNO++ by Team Ayteen\n"
         << "Created By: Ronald Jock, Denaujay LittleJohn, and Chris Keaton\n" << endl;
    cout << "UNO is a 2001 trademark card game by Mattel Games. Any simularities or likeness to the game are done so under "
         << "fair-use.\n" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------\n"
         << endl;

    // Ask If They Would Like A Tutorial
    do {
        cout << "Would you like to play the tutorial? Enter \'y\' or \'n\'.\n";
        cin >> playTutorial;
        cout << endl;
        if((playTutorial != 'y') && (playTutorial != 'n'))
        {
            cout << "Please enter \'y\' or \'n\'.\n"
                 << endl;
        }
    } while((playTutorial != 'y') && (playTutorial != 'n'));

    if(playTutorial == 'y') // Run the tutorial if they respond with 'y'
    {
        Tutorial();
    }


    // # of players
    do {
        cout << "How many players are there? Enter a number between \'2\' and \'4\'.\n";
        cin >> numPlayers;
        if(((numPlayers < 2) || (numPlayers > 4)) || (cin.fail()))  // Player Number Check (Must be number between 2 and 4)
        {
            cout << endl << "Please enter a number between \'2\' and \'4\'.\n";

            if(cin.fail()) // If input was wrong input type i.e., word, clear and ignore input
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while((numPlayers < 2) || (numPlayers > 4));
    cout << endl;

    // Player names
    playerNames.resize(numPlayers);
    for(int i = 0; i < numPlayers; i++)
    {
        do {
            cout << "Please enter Player " << i + 1 << "\'s name.\n";
            cin >> playerNames.at(i);
            cout << endl;
            if(playerNames.at(i).size() > 15)  // Character Length Check (Name must be less than 15 chars)
            {
                cout << "Please use a shorter name (less than 15 characters).\n";
            }
        } while(playerNames.at(i).size() > 15);
    }
    cout << endl;

    /* NOTE: Player order is dictated by the order in which the names
             where typed.

       Ex)   # of Players = 2
             playerNames.at(0) = John; playerNames.at(1) = George

             Therefore:
             John goes first, George goes second

    /* TEST; Names REMOVE
    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Player " << i + 1 << ": " << playerNames.at(i) << endl;
    }
    return 0;
    */

    
    // === UNO Deck ===
    vector<int> deckValues;                          // DECK SIZE = 112 CARDS TOTAL
    vector<char> deckValuesColors;                     // 76 Numbers; 24 Special; 12 Neutral

    DeckBuilder(deckValues, deckValuesColors);

    /* TEST; DeckBuilder REMOVE
    cout << "Deck Test" << endl;
    for(int i = 0; i < deckValues.size(); i++)
    {
        cout << "Card " << i << ": "
             << deckValues.at(i) << " / " << deckValuesColors.at(i) << endl;
    }
    cout << endl << "Total # of Cards: " << deckValues.size()
         << endl << endl;

    // TEST; DeckShuffle REMOVE
    cout << "Shuffle Test" << endl;
    DeckShuffle(deckValues, deckValuesColors);
    for(int i = 0; i < deckValues.size(); i++)
    {
        cout << "Card " << i << ": "
             << deckValues.at(i) << " / " << deckValuesColors.at(i) << endl;
    }
    cout << endl << "Total # of Cards: " << deckValues.size()
         << endl << endl;
    return 0;
    */

    // === Game Start ===
    int currRound = 0; // Current round of game
    srand(time(NULL)); // Random Seed for Shuffling
    char shouldGameContinue; // Determines how long players want the game to go on for

    do {
        // If current round isn't 0, rebuild deck
        if(currRound != 0)
        {
            DeckBuilder(deckValues, deckValuesColors);
        }

        // Player Hands
        // [Player 1]
        vector<int> player1Hand(7);
        vector<char> player1Colors(7);
        // [Player 2]
        vector<int> player2Hand(7);
        vector<char> player2Colors(7);
        // [Player 3]
        vector<int> player3Hand(7);
        vector<char> player3Colors(7);
        // [Player 4]
        vector<int> player4Hand(7);
        vector<char> player4Colors(7);

        /* TEST; DisplayPlayerHand REMOVE
        srand(time(NULL));
        DeckShuffle(deckValues, deckValuesColors);

        player1Hand = {deckValues.at(0), deckValues.at(1), deckValues.at(2), deckValues.at(3), deckValues.at(4)};
        player1Colors = {deckValuesColors.at(0), deckValuesColors.at(1), deckValuesColors.at(2), deckValuesColors.at(3), deckValuesColors.at(4)};

        cout << " === " << playerNames.at(0) << "'s Hand === " << endl;
        DisplayPlayerHand(player1Hand, player1Colors);
        return 0;
        */

        currRound++;

        // Play one round of UNO
        PlayUno(player1Hand, player1Colors   ,
                player2Hand, player2Colors   ,
                player3Hand, player3Colors   ,
                player4Hand, player4Colors   ,
                deckValues , deckValuesColors,
                playerNames, playerScores    ,
                numPlayers                    );

        //Check if player wants to play another round
        do {
            cout << "Do you want to play another round? \'y\' or \'n\'?\n";
            cin >> shouldGameContinue;                                            // Player enters 'y' or 'n' key
            cout << endl;
            if((shouldGameContinue != 'y') && (shouldGameContinue != 'n'))        // If input was not 'y' or 'n',
            {                                                                     // enter input again.
                cout << "Please enter \'y\' or \'n\'.\n"
                     << endl;
            }
        } while((shouldGameContinue != 'y') && (shouldGameContinue != 'n'));

        cout << "=== Curret Scores ===\n";
        for(int i = 0; i < numPlayers; i++)
        {
            cout << playerNames.at(i) << ": " << playerScores.at(i) << endl;
        }
        cout << endl;

    // Game will continue so long as shouldGameContinue == 'y' or doesn't hit the round limit
    } while ((shouldGameContinue == 'y') && (currRound != 5));

    // === Winner Declaration ===
    int maxScore = playerScores.at(0);
    int winner = 0;

    // Calculate winner based on scores
    for(int i = 1; i < playerScores.size(); i++)
    {
        if(playerScores.at(i) > maxScore)
        {
            maxScore = playerScores.at(i);
            winner = i;
        }
    }

    // Output winner and score
    cout << playerNames.at(winner) << " wins with a score of " << playerScores.at(winner) << "!\n"
         << endl << "Thanks for playing!\n"
         << endl;

    cout << "--- END OF GAME ---" << endl;

    return 0;
}



/************************************************************************************************************************/
/************************************************************************************************************************/


/*!MOVED: "Game.h"; REMOVE
// Runs the player through an interactive tutorial for playing UNO
void Tutorial()
{
    string str; // Output string
    int endSec; // Flag to see if the line contains "Press 'Enter' to continue..."

    ifstream tutorial; // File variable for "tutorial.txt"

    tutorial.open("tutorial.txt");
    if(tutorial.is_open())
    {
        while(getline(tutorial, str)) // Output lines from "tutorial.txt" until it hits a line with "Press 'Enter' to continue..."
        {
            endSec = str.find("Press \'Enter\' to continue...");

            cout << str << endl;
            if(endSec == 0)
            {
                cin.get();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    tutorial.close();
    cout << "END OF TUTORIAL" << endl;
}
*/


// Creates the UNO deck
void DeckBuilder(vector<int>& deckValues, vector<char>& deckValuesColors)
{
    char colors[4] = {'B', 'G', 'R', 'Y'};          // Card Colors = (Blue, Green, Red, Yellow)

    // Reset Deck
    deckValues.resize(0);
    deckValuesColors.resize(0);

    // Build / Rebuild Deck
    for(int i = 0; i < 4; i++)                      // #'s w/ COLORS = 76 CARDS
    {
        deckValues.push_back(0);                     // 1 '0' for each color
        deckValuesColors.push_back(colors[i]);
        for(int j = 1; j <= 9; j++)                 // 2 of each number (1-9) for each color
        {
            for(int k = 0; k < 2; k++)
            {
                deckValues.push_back(j);
                deckValuesColors.push_back(colors[i]);
            }
        }
        for(int j = 10; j <= 12; j++)               // SPECIAL CARDS w/ COLORS = 24 CARDS
        {                                              // Skip ('10'); Reverse ('11'); Draw ('12')
            for(int k = 0; k < 2; k++)              // 2 of each special card for each color
            {
                deckValues.push_back(j);
                deckValuesColors.push_back(colors[i]);
            }
        }
    }
    for(int i = 13; i <= 15; i++)                   // NEUTRAL CARDS = 12 CARDS
    {                                                  // Wild ('13'), Wild Draw 4 ('14'), Blank ('15')
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



// Shuffles the UNO deck. Runs at the beginning of each new round.
void DeckShuffle(vector<int>& deckValues, vector<char>& deckValuesColors)
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 56; j++)
        {
            int randNum1, randNum2;

            // Choose two places in the deck to swap
            do {
                randNum1 = rand() % 112;        // First value to swap
                randNum2 = rand() % 112;        // Second value to swap
            } while (randNum1 == randNum2);

            // Swap the two values
            // [Card Number/Type]
            int tmp1;

            tmp1 = deckValues.at(randNum1);
            deckValues.at(randNum1) = deckValues.at(randNum2);
            deckValues.at(randNum2) = tmp1;

            // [Card Colors]
            char tmp2;

            tmp2 = deckValuesColors.at(randNum1);
            deckValuesColors.at(randNum1) = deckValuesColors.at(randNum2);
            deckValuesColors.at(randNum2) = tmp2;
        }
    }
}



// Draws 5 cards for each player at the start of a round, and draws 1 card for each player for every
// turn thereafter. An exception is the Wild Draw 4 card, where the next player is forced to draw 4
// cards instead of one.
void DrawCards(vector<int>& playerHand, vector<char>& playerHandColors  ,
               vector<int>& deckValues,vector<char>& deckColors         ,
               const bool GameStart = false                              )
{
    bool HandTooBig = (playerHand.size() == 16); // Limiter to keep a player's hand from getting too big

    switch(HandTooBig) // If hand is too big, player draws no cards
    {
        case false: // Hand has room
            if((deckValues.size() != 0) && (deckColors.size() != 0))              // Draw a card as long as the deck isn't empty.
            {                                                                     // If it is, reshuffle and redraw the deck.
                switch(GameStart) // Draw for hands at the start of a new round
                {
                    case true: // Initial Draw
                        for(int i = 0; i < 7; i++)
                        {
                            playerHand.at(i) = deckValues.back();
                            playerHandColors.at(i) = deckColors.back();
                            deckValues.pop_back();
                            deckColors.pop_back();
                        }
                        break;
                    case false: // Normal Draw
                            playerHand.push_back(deckValues.back());
                            playerHandColors.push_back(deckColors.back());
                            deckValues.pop_back();
                            deckColors.pop_back();
                            break;
                }
            }
            else {
                cout << "Deck is empty.\n";
                DeckBuilder(deckValues, deckColors);
                DeckShuffle(deckValues, deckColors);
            }
            break;

    case true: // Hand full
        {
            cout << "Too many cards to draw more\n";
            cout << endl;
        }
        break;
    }
}



// Displays the cards in the current player's hand.
void DisplayPlayerHand(const vector<int> playerHand, const vector<char> playerHandColors)
{
    // Card Top
    for(int i = 0; i < playerHand.size(); i++)
    {
        cout << "┌   ┐   ";
    }
    cout << endl;

    // Card Middle
    for(int i = 0; i < playerHand.size(); i++)
    {
        switch(playerHand.at(i))
        {
            case 10:                                                     // Skip Card
                cout << "|S " << playerHandColors.at(i) << "|   ";
                break;
            case 11:                                                     // Reverse Card
                cout << "|R " << playerHandColors.at(i) << "|   ";
                break;
            case 12:                                                     // Draw Card
                cout << "|D " << playerHandColors.at(i) << "|   ";
                break;
            case 13:                                                     // Wild Card
                cout << "| W |   ";
                break;
            case 14:                                                     // Wild Draw 4 Card
                cout << "|W 4|   ";
                break;
            case 15:                                                     // Blank Card
                cout << "| B |   ";
                break;
            default:                                                     // Normal Card (0-9)
                cout << "|" << playerHand.at(i) << " " << playerHandColors.at(i) << "|   ";
                break;
        }
    }
    cout << endl;

    // Card Bottom
    for(int i = 0; i < playerHand.size(); i++)
    {
        cout <<"└   ┘";
        if(i == playerHand.size() - 1)
        {
            break;
        }
        else {
            cout << " , ";
        }
    }
    cout << endl;

    // Card Number
    for(int i = 0; i < playerHand.size(); i++)
    {
        cout << "  " << (i + 1) << "     ";
    }
    cout << endl;
}

void DisplayTopDiscardCard(int discardValue, char discardColor)
{
    // Card Top
    cout << "┌   ┐" << endl;

    // Card Middle
    switch(discardValue)
    {
        case 10:                                                     // Skip Card
            cout << "|S " << discardColor << "|   ";
            break;
        case 11:                                                     // Reverse Card
            cout << "|R " << discardColor << "|   ";
            break;
        case 12:                                                     // Draw Card
            cout << "|D " << discardColor << "|   ";
            break;
        case 13:                                                     // Wild Card
        case 14:                                                     // Wild Draw 4 Card
            cout << "| " << discardColor << " |   ";
            break;
        case 15:                                                     // Blank Card
        default:                                                     // Normal Card (0-9)
            cout << "|" << discardValue << " " << discardColor << "|   ";
            break;
    }
    cout << endl;

    // Card Bottom
    cout << "└   ┘" << endl;
}



// Checks to see if the special card can be played.
bool SpecialCheck(const vector<int> playerHand, const vector<char> playerColors,
                  const int topDiscardValue, const char topDiscardColor        ,
                  int playerCardChoice                                          )
{
    bool CanContinue = true;
    switch(playerHand.at(playerCardChoice))
    {
        // Can only be played if they match the color of the top card on the discard pile
        case 10: // Skip Card
        case 11: // Reverse Card
        case 12: // 'Draw 2' Card
            if((playerHand.at(playerCardChoice) != topDiscardValue) && (playerColors.at(playerCardChoice) != topDiscardColor))
            {
                cout << "Please choose a card that matches the color or number of the top card on the "
                     << "discard pile.\n"
                     << endl;
                CanContinue = false;
                break;
            }
            break;
        // Can only be played if the played has no other cards they can play
        case 14: // Wild 'Draw 4' Card
            {
                bool OtherPlayableCards = false;
                for(int i = 0; i < playerHand.size(); i++)
                {
                    if(((playerHand.at(i) == topDiscardValue) || (playerColors.at(i) == topDiscardColor)) ||
                       ((playerHand.at(i) == 13)              || (playerHand.at(i) == 15))                  )
                    {
                        OtherPlayableCards = true;
                    }
                }

                if(OtherPlayableCards == true)
                {
                    cout << "You can only choose this card when you have no other card you can play from "
                         << "your hand. Please choose another card.\n"
                         << endl;
                    CanContinue = false;
                    break;
                }
                break;
            }
        // Both of these can be played regardless of the top card on the discard pile
        case 13: // Wild Card
        case 15: // Blank Card
            break;
    }
    cout << "Test 1" << endl; // <----------------------------------------------------------------------------- FIXME; REMOVE
    return CanContinue;
}



// Plays out the current player's turn (drawing, choosing a card from their hand, and checking the
// remaining cards in their hand).
void PlayerTurn(vector<int>& playerHand, vector<char>& playerColors, vector<int>& deckValues, vector<char>& deckColors      ,
                vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool& IsReverse, int& currTurn   )
{
    DisplayPlayerHand(playerHand, playerColors);                 // Displays player hand at the start of turn

    cout << "=== Top Card ===" << endl;
    DisplayTopDiscardCard(topDiscardValue, topDiscardColor);     // Displays discard card at the start of turn

    string playerChoice;
    bool DoesPlayerExit;
    do {
        DoesPlayerExit = false;
        do {
            cout << "Would you like to \'play\' a card, or \'draw\'?\n";
            cin >> playerChoice;
            cout << endl;
            if((playerChoice != "play") && (playerChoice != "draw"))
            {
                cout << "Please enter \'play\' or \'draw\'.\n"
                     << endl;
            }
        } while((playerChoice != "play") && (playerChoice != "draw"));

        bool IsPlayCard = (playerChoice == "play"); // Checks if player wants to play a card in their hand
        bool IsSpecialCard;
        switch(IsPlayCard)
        {
            case 0: // Draw a Card
                char doubleCheckPlayerDecision;


                // Double check if player really wants to draw
                do {
                    cout << "Are you sure you want to draw? Enter \'y\' or \'n\'.\n";
                    cin >> doubleCheckPlayerDecision;
                    cout << endl;
                    if((doubleCheckPlayerDecision != 'y') && (doubleCheckPlayerDecision != 'n'))
                    {
                        cout << "Please enter either \'y\' or \'n\'.\n"
                             << endl;
                    }
                } while((doubleCheckPlayerDecision != 'y') && (doubleCheckPlayerDecision != 'n'));

                // If they don't, exit draw and return to decision options
                if(doubleCheckPlayerDecision == 'n')
                {
                    DoesPlayerExit = true;
                    break;
                }

                // If they do, draw a card
                DrawCards(playerHand, playerColors, deckValues, deckColors);

                // Display new card
                cout << "Card Drawn" << endl;

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

/*!MOVED "Game.h"; REMOVE
// Runs a single round of UNO, and tallies a score for the winner based on the other player's hands.
void PlayUno(vector<int>& player1Hand, vector<char>& player1Colors ,
             vector<int>& player2Hand, vector<char>& player2Colors ,
             vector<int>& player3Hand, vector<char>& player3Colors ,
             vector<int>& player4Hand, vector<char>& player4Colors ,
             vector<int>& deckValues , vector<char>& deckColors    ,
             vector<string>& playerNames, vector<int>& playerScores,
             int numPlayers                                         )
{
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

    /* TEST; Wild 'Draw 4' Discard Card REMOVE
    topDiscardValue = 14;
    topDiscardColor = 'N';

    /* TEST; Blank Discard Card REMOVE
    topDiscardValue = 15;
    topDiscardColor = 'N';

    /* TEST; New Discard Type REMOVE
    cout << "Top Discard Value: " << topDiscardValue << endl;

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

    /* TEST; Wild Card REMOVE
    player1Hand.push_back(13);
    player1Colors.push_back('N');

    /* TEST; Blank Card REMOVE
    player1Hand.push_back(15);
    player1Colors.push_back('N');

    /* TEST; Win State REMOVE
    player1Hand.resize(1);
    player1Colors.resize(1);
    player1Hand.at(0) = 0;
    player1Colors.at(0) = 'B';
    topDiscardValue = 0;
    topDiscardColor = 'B';

    // Run player turns while no one has played their last card
    bool IsReverse = false;
    do {
        cout << "Player Turn Runs" << endl; // <--------------------------------------------------------- FIXME; REMOVE
        cout << "=== " << playerNames.at(currTurn % numPlayers) << "\'s Turn ===" << endl;
        switch(currTurn % numPlayers)
        {
            // Player 1's Turn
            case 0:
                PlayerTurn(player1Hand, player1Colors, deckValues, deckColors                 ,
                           player1Hand, player1Colors, player2Hand, player2Colors             ,
                           player3Hand, player3Colors, player4Hand, player4Colors             ,
                           topDiscardValue, topDiscardColor, 0, numPlayers, IsReverse, currTurn);
                WinCheck(playerNames.at(0), 0, player1Hand, player1Colors, PlayerPlayedLastCard, winnerNum);
                break;
            // Player 2's Turn
            case 1:
                PlayerTurn(player2Hand, player2Colors, deckValues, deckColors                 ,
                           player1Hand, player1Colors, player2Hand, player2Colors             ,
                           player3Hand, player3Colors, player4Hand, player4Colors             ,
                           topDiscardValue, topDiscardColor, 1, numPlayers, IsReverse, currTurn);
                WinCheck(playerNames.at(1), 1, player2Hand, player2Colors, PlayerPlayedLastCard, winnerNum);
                break;
            // Player 3's Turn
            case 2:
                PlayerTurn(player3Hand, player3Colors, deckValues, deckColors                 ,
                           player1Hand, player1Colors, player2Hand, player2Colors             ,
                           player3Hand, player3Colors, player4Hand, player4Colors             ,
                           topDiscardValue, topDiscardColor, 2, numPlayers, IsReverse, currTurn);
                WinCheck(playerNames.at(2), 2, player3Hand, player3Colors, PlayerPlayedLastCard, winnerNum);
                break;
            // Player 4's Turn
            case 3:
                PlayerTurn(player4Hand, player4Colors, deckValues, deckColors                 ,
                           player1Hand, player1Colors, player2Hand, player2Colors             ,
                           player3Hand, player3Colors, player4Hand, player4Colors             ,
                           topDiscardValue, topDiscardColor, 3, numPlayers, IsReverse, currTurn);
                WinCheck(playerNames.at(3), 3, player4Hand, player4Colors, PlayerPlayedLastCard, winnerNum);
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while(PlayerPlayedLastCard != true);

    playerScores.at(winnerNum) += ScoreTally(player1Hand, player2Hand, player3Hand, player4Hand);
}
*/


// Chooses a routine based on the player's card value.
void CardPlayed(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool& IsReverse, int& currTurn   )
{
    bool IsSpecialCase = false;
    switch(playerCardValue)
    {
        case 10: // Skip Card
            SkipCard(playerCardValue, playerCardColor, deckValues, deckColors       ,
                     player1Hand, player1Colors, player2Hand, player2Colors         ,
                     player3Hand, player3Colors, player4Hand, player4Colors         ,
                     topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
            break;
        case 11: // Reverse Card
            ReverseCard(playerCardValue, playerCardColor, deckValues, deckColors       ,
                        player1Hand, player1Colors, player2Hand, player2Colors         ,
                        player3Hand, player3Colors, player4Hand, player4Colors         ,
                        topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
            break;
        case 12: // 'Draw 2' Card
            Draw2Card(playerCardValue, playerCardColor, deckValues, deckColors       ,
                      player1Hand, player1Colors, player2Hand, player2Colors         ,
                      player3Hand, player3Colors, player4Hand, player4Colors         ,
                      topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
            break;
        case 13: // Wild Card
            IsSpecialCase = true;
            WildCard(playerCardValue, playerCardColor, deckValues, deckColors       ,
                     player1Hand, player1Colors, player2Hand, player2Colors         ,
                     player3Hand, player3Colors, player4Hand, player4Colors         ,
                     topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
            break;
        case 14: // Wild 'Draw 4' Card
            IsSpecialCase = true;
            Wild4Card(playerCardValue, playerCardColor, deckValues, deckColors       ,
                      player1Hand, player1Colors, player2Hand, player2Colors         ,
                      player3Hand, player3Colors, player4Hand, player4Colors         ,
                      topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
            break;
        case 15: // Blank Card
            IsSpecialCase = true;
            BlankCard(playerCardValue, playerCardColor, deckValues, deckColors       ,
                      player1Hand, player1Colors, player2Hand, player2Colors         ,
                      player3Hand, player3Colors, player4Hand, player4Colors         ,
                      topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);
            //cout << "Top Discard Value: " << topDiscardValue << endl; // <------------------------------------ FIXME; REMOVE
            //cout << "Top Discard Color: " << topDiscardColor << endl; // <------------------------------------ FIXME; REMOVE
            break;
        default: // Normal Card (Only here to be safe)
            break;
    }

    // As long as the card isn't Wild, Wild 'Draw 4', or Blank, set the value and color of the top car on the
    // discard pile.
    if(IsSpecialCase != true)
    {
        topDiscardValue = playerCardValue;
        topDiscardColor = playerCardColor;
    }
}

/*!MOVED "Cards.h"; REMOVE
// Card Function: Skips the next playr's turn.
void SkipCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
              vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
              vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
              int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    )
{
    if(IsReverse == false) // If player rotation is normal
    {
        currTurn++;
    }
    else {                 // If player rotation is reversed
        currTurn--;
    }
}



// Card Function: Reverses the player order (If 3-Players: Player 3, then Player 2, then Player 1).
void ReverseCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
                 vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
                 vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
                 int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool& IsReverse, int& currTurn   )
{
    if(IsReverse == false) // If player rotation is normal
    {
        IsReverse = true;
    }
    else {                 // If player rotation is already reversed
        IsReverse = false;
    }
}



// Card Function: Makes the next player draw 2 cards.
void Draw2Card(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
               vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
               vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
               int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    )
{
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



// Card Function: Let's the player choose the color of the top card on the discard pile.
void WildCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
              vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
              vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
              int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    )
{
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



// Card Function: If the player has no other card in their hand they can play:
//                    1) Player chooses the color of the top card on the
//                       discard pile.
//                    2) Next player must draw 2 cards.
//                    3) Next player loses their turn.
void Wild4Card(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
               vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
               vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
               int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    )
{
    WildCard(playerCardValue, playerCardColor, deckValues, deckColors       ,
             player1Hand, player1Colors, player2Hand, player2Colors         ,
             player3Hand, player3Colors, player4Hand, player4Colors         ,
             topDiscardValue, topDiscardColor, playerNum, numPlayers, IsReverse, currTurn);

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



// Card Function: Allows the player to choose the number value and color of the top card on the discard pile.
void BlankCard(int playerCardValue, char playerCardColor, vector<int>& deckValues, vector<char>& deckColors                ,
               vector<int>& player1Hand, vector<char>& player1Colors, vector<int>& player2Hand, vector<char>& player2Colors,
               vector<int>& player3Hand, vector<char>& player3Colors, vector<int>& player4Hand, vector<char>& player4Colors,
               int& topDiscardValue, char& topDiscardColor, int playerNum, int numPlayers, bool IsReverse, int& currTurn    )
{
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
*/

/*!MOVED "Game.h"; REMOVE
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



// Tallies up the score values of the playing hands to add to the round winner's total score.
int ScoreTally(vector<int> player1Hand, vector<int> player2Hand,
               vector<int> player3Hand, vector<int> player4Hand )
{
    int sum = 0;
    sum += CountHandScore(player1Hand);
    sum += CountHandScore(player2Hand);
    sum += CountHandScore(player3Hand);
    sum += CountHandScore(player4Hand);

    return sum;
}



// Converts the player's hand into points, and returns the total.
int CountHandScore(const vector<int> playerHand)
{
    /*================================================================
      ==  Point Conversion Table                                    ==
      ==  o Numbered Cards (0-9) -> Face Value                      ==
      ==  o Skip                 -> 20 Points                       ==
      ==  o Reverse              -> 20 Points                       ==
      ==  o 'Draw 2'             -> 20 Points                       ==
      ==  o Wild                 -> 50 Points                       ==
      ==  o Wild 'Draw 4'        -> 50 Points                       ==
      ==  o Blank                -> Don't Count                     ==
      ================================================================
    int handSum = 0;

    if(playerHand.size() != 0)
    {
        for(int i = 0; i < playerHand.size(); i++)
        {
            switch(playerHand.at(i))
            {
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
*/
