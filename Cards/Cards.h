#ifndef CARDS_H
#define CARDS_H

class Cards {
    protected:
        virtual char Play() const = 0;
        
        char GetChar() const;
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
