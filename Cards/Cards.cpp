#include <sstream>

#include "Cards.h"

char Cards::GetColor() const {
    
    switch(cardInfo.color) {
        case BLUE:
            return 'B';
        case GREEN:
            return 'G';
        case RED:
            return 'R';
        case YELLOW:
            return 'Y';
        default:
            std::cout << "ERROR: Out of Bounds\n";
            return '!'; //Error Flag
    }
}

void Cards::PrintCard() {
    
    std::cout << Print_CardTop()
              << Print_CardMiddle()
              << Print_CardBottom();
}

/*****************************************************/

std::string Number::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << cardInfo.numValue << " " << GetColor() << "| \n";
    
    return str.str();
}

/*****************************************************/

std::string Skip::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << 'S' << " " << GetColor() << "| \n";
    
    return str.str();
}

/*****************************************************/

std::string Reverse::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << 'R' << " " << GetColor() << "| \n";
    
    return str.str();
}

/*****************************************************/

std::string Draw2::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << 'D' << " " << GetColor() << "| \n";
    
    return str.str();
}

/*****************************************************/

std::string Wild::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << " W " << "| \n";
    
    return str.str();
}

/*****************************************************/

std::string Wild4::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << "W" << " " << "4" << "| \n";
    
    return str.str();
}

/*****************************************************/

std::string Blank::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << " B " << "| \n";
    
    return str.str();
}
