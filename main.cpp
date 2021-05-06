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
            
            std::cin >> playerInput;
            
            if(((playerInput != 'Y') && (playerInput != 'N')) || (std::cin.fail())) {
                
                std::cout << "Please enter \'Y\' or \'N\'.\n";
                
                if(std::cin.fail()) {
                    std::cin.ignore();
                    std::cin.clear();
                }
                
                fail = true;
            }
        } while(fail == true);
    } while(playerInput == 'Y');
    std::cout << std::endl;
        
    uno.PrintScores();
    
    return 0;
}
