#include <cstdlib>
#include <ctime>

#include "Game/Game.h"

int main() {
    srand(time(NULL));
    Game uno;
    
    char playerInput = 'N';
    do {
        uno.GameState();
        
        bool fail;
        do {
            fail = false;
            
            std::cout << "Would you like to continue? Enter \'Y\' or \'N\'.\n";
            
            if((playerInput != 'Y') && (playerInput != 'N')) {
                
                std::cout << "Please enter \'Y\' or \'N\'.\n";
                fail = true;
            }
        } while(fail == true);
    } while(playerInput == 'Y');
        
    uno.PrintScores();
    
    return 0;
}
