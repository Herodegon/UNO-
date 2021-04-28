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
    
        //Print Card in ASCII Characters
        void PrintCard();
        
        std::string Print_CardTop()    {return ".---. \n";}
        virtual std::string Print_CardMiddle() const = 0;
        std::string Print_CardBottom() {return "'---' \n";}
    
    protected:
    
        //Accessors for Card Info
        char GetColor() const;
        std::string GetName() const;
        
        //Print Card Name
        virtual std::string GetDesc() const = 0;
        
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
        
        std::string GetDesc() const;
};

/*************************************************************/

class Skip : public Cards {
    public:
        Skip(unsigned int color) {
            cardInfo.color = static_cast<CardColor>(color);
        }
        
        std::string Print_CardMiddle() const;
        
        std::string GetDesc() const;
};

/*************************************************************/

class Reverse : public Cards {
    public:
        Reverse(unsigned int color) {
            cardInfo.color = static_cast<CardColor>(color);
        }
        
        std::string Print_CardMiddle() const;
        
        std::string GetDesc() const;
};

/*************************************************************/

class Draw2 : public Cards {
    public:
        Draw2(unsigned int color) {
            cardInfo.color = static_cast<CardColor>(color);
        }
        
        std::string Print_CardMiddle() const;
        
        std::string GetDesc() const;
};

/*************************************************************/

class Wild : public Cards {
    public:
    
        std::string Print_CardMiddle() const;
        
        std::string GetDesc() const;
};

/*************************************************************/

class Wild4 : public Cards {
    public:
    
        std::string Print_CardMiddle() const;
        
        std::string GetDesc() const;
};

/*************************************************************/

class Blank : public Cards {
    public:
    
        std::string Print_CardMiddle() const;
        
        std::string GetDesc() const;
};

#endif
