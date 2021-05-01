#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>

enum CardType {
    NUMBER,
    SKIP = 10, 
    REVERSE = 11, 
    DRAW2 = 12, 
    WILD = 13, 
    WILD4 = 14, 
    BLANK = 15, 
    NUM_TYPES
};

enum CardColor {BLUE, GREEN, RED, YELLOW, NUM_COLORS, NOT_SPECIFIED};

//Card Type and Color
struct Info {
    public:
    
        CardType type = NUMBER;
        int numValue = -1;
        CardColor color = NOT_SPECIFIED;
};

class Cards {
    public:
        
        //Accessors for Card Info
        int Info_GetNumVal() const {return cardInfo.numValue;}
        CardType Info_GetType() const {return cardInfo.type;}
        CardColor Info_GetColor() const {return cardInfo.color;}
        
        void Info_SetNumVal(int numValue) {this->cardInfo.numValue = numValue;}
        void Info_SetType(unsigned int type) {this->cardInfo.type = static_cast<CardType>(type);}
        void Info_SetColor(unsigned int color) {this->cardInfo.color = static_cast<CardColor>(color);}
        
        //Print Card in ASCII Characters
        void PrintCard();
        
        std::string Print_CardTop()    {return ".---. \n";}
        virtual std::string Print_CardMiddle() const = 0;
        std::string Print_CardBottom() {return "'---' \n";}
    
    protected:
    
        //Print Functions
        char GetColor() const;
        virtual std::string GetName() const = 0;
        
        //Card Type and Color
        Info cardInfo;
};

/*************************************************************/

class Number : public Cards {
    public:
        Number(unsigned int num, unsigned int color) {
            cardInfo.numValue = num;
            cardInfo.color = static_cast<CardColor>(color);
        }
        
        std::string Print_CardMiddle() const;
        
        std::string GetName() const {return "Number " + Info_GetNumVal();}
};

/*************************************************************/

class Skip : public Cards {
    public:
        Skip(unsigned int color) {
            cardInfo.color = static_cast<CardColor>(color);
        }
        
        std::string Print_CardMiddle() const;
        
        std::string GetName() const {return "Skip";}
};

/*************************************************************/

class Reverse : public Cards {
    public:
        Reverse(unsigned int color) {
            cardInfo.color = static_cast<CardColor>(color);
        }
        
        std::string Print_CardMiddle() const;
        
        std::string GetName() const {return "Reverse";}
};

/*************************************************************/

class Draw2 : public Cards {
    public:
        Draw2(unsigned int color) {
            cardInfo.color = static_cast<CardColor>(color);
        }
        
        std::string Print_CardMiddle() const;
        
        std::string GetName() const {return "Draw 2";}
};

/*************************************************************/

class Wild : public Cards {
    public:
    
        std::string Print_CardMiddle() const;
        
        std::string GetName() const {return "Wild";}
};

/*************************************************************/

class Wild4 : public Cards {
    public:
    
        std::string Print_CardMiddle() const;
        
        std::string GetName() const {return "Wild 4";}
};

/*************************************************************/

class Blank : public Cards {
    public:
    
        std::string Print_CardMiddle() const;
        
        std::string GetName() const {return "Blank";}
};

#endif
