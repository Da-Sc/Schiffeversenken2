#ifndef SPIEL_H
#define SPIEL_H

#include "SPIELFELD.h"
#include "BO_KOM.h"

class SPIEL
{
    public:
        SPIEL();
        virtual ~SPIEL();
    protected:
    private:
        SPIELFELD* Meer[2];//2 spielfelder
        int AnzahlSchiffe;
        int* Schifflaenge;
};

#endif // SPIEL_H
