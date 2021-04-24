#ifndef CARDS_H
#define CARDS_H

enum CardType {
    NUMBER,
    SKIP, REVERSE, DRAW2, WILD, WILD4, BLANK, 
    NUM_TYPES
};

enum CardColor {BLUE, GREEN, RED, YELLOW, NUM_COLORS, NOT_SPECIFIED};

struct Info {
    public:
        CardType type;
        CardColor color;
};

class Cards {
    protected:
    
        //Accessors for Card Info
        char GetType() const;
        char GetColor() const;
        
        //Print Card in ASCII Characters
        void Print() const;
        
        //Card Type and Color
        Info cardInfo;
};

/*************************************************************/

class Number : public Cards {
    
};

/*************************************************************/

class Skip : public Cards {
    
};

/*************************************************************/

class Reverse : public Cards {
    
};

/*************************************************************/

class Draw2 : public Cards {
    
};

/*************************************************************/

class Wild : public Cards {
    
};

/*************************************************************/

class Wild4 : public Cards {
    
};

/*************************************************************/

class Blank : public Cards {
    
};

#endif
