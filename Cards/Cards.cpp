#include "Cards.h"

char Cards::GetColor() const {
    
    switch(Info_GetColor()) {
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
    
    std::cout << Print_CardTop() << std::endl
              << Print_CardMiddle() << std::endl
              << Print_CardBottom() << std::endl;
}

/*****************************************************/

std::string Number::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << Info_GetNumVal() << " " << GetColor() << "| ";
    
    return str.str();
}

/*****************************************************/

std::string Skip::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << 'S' << " " << GetColor() << "| ";
    
    return str.str();
}

/*****************************************************/

std::string Reverse::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << 'R' << " " << GetColor() << "| ";
    
    return str.str();
}

/*****************************************************/

std::string Draw2::Print_CardMiddle() const {
    std::ostringstream str;
    
    str << "|" << 'D' << " " << GetColor() << "| ";
    
    return str.str();
}

/*****************************************************/

std::string Wild::Print_CardMiddle() const {
    std::ostringstream str;
    
    if(Info_GetColor() == NOT_SPECIFIED) {
        str << "|" << " W " << "| ";
    }
    else {
        str << "| " << GetColor() << " | ";
    }
    
    return str.str();
}

/*****************************************************/

std::string Wild4::Print_CardMiddle() const {
    std::ostringstream str;
    
    if(Info_GetColor() == NOT_SPECIFIED) {
        str << "|" << "W" << " " << "4" << "| ";
    }
    else {
        str << "| " << GetColor() << " | ";
    }
    
    return str.str();
}

/*****************************************************/

std::string Blank::Print_CardMiddle() const {
    std::ostringstream str;
    
    if(Info_GetColor() == NOT_SPECIFIED) {
        str << "|" << " B " << "| ";
    }
    else {
        str << "|" << Info_GetNumVal() << " " << GetColor() << "| ";
    }
    
    return str.str();
}
