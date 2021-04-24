#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>

enum CardType {
    NUMBER,
    SKIP, REVERSE, DRAW2, WILD, WILD4, BLANK, 
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
    protected:
        
        //Accessors for Card Info
        virtual char GetSymbol() const = 0;
        char GetColor() const;
        std::string GetName() const;
        
        //Print Card in ASCII Characters
        void Print() const;
        std::string Print_CardTop()    {return ".---.";}
        std::string Print_CardBottom() {return "'---'";}
        
        //Card Type and Color
        Info cardInfo;
};

/*************************************************************/

class Number : public Cards {
    public:
        Number(unsigned int num, CardColor color) {
            cardInfo.numValue = num;
            cardInfo.color = color;
        }
        
        char GetSymbol() const {return cardInfo.numValue;}
};

/*************************************************************/

class Skip : public Cards {
    public:
        Skip(CardColor color) {
            cardInfo.color = color;
        }
};

/*************************************************************/

class Reverse : public Cards {
    public:
        Reverse(CardColor color) {
            cardInfo.color = color;
        }
};

/*************************************************************/

class Draw2 : public Cards {
    public:
        Draw2(CardColor color) {
            cardInfo.color = color;
        }
};

/*************************************************************/

class Wild : public Cards {
    public:
        Wild(CardColor color) {
            cardInfo.color = color;
        }
};

/*************************************************************/

class Wild4 : public Cards {
    public:
        Wild4(CardColor color) {
            cardInfo.color = color;
        }
};

/*************************************************************/

class Blank : public Cards {
    public:
        Blank(CardColor color) {
            cardInfo.color = color;
        }
};

#endif
