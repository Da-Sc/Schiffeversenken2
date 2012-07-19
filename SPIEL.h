#ifndef SPIEL_H
#define SPIEL_H

#include "SPIELFELD.h"
#include "BO_VERWALTUNG.h"
#include "POSITION.h"

class SPIEL
{
    public:
        SPIEL();
        virtual ~SPIEL();
        void setzeSchiffe(int); //Setzt Schiffe für Spieler (übergebener int, 0 oder 1)
        char* zeigeSpielfelder(int);
        void spielen(int);
    protected:
    private:
        SPIELFELD* Meer[2];//2 spielfelder
        int AnzahlSchiffe;
        int* Schifflaenge;
        char* auszugebendesSpielfeld;
};

#endif // SPIEL_H
//0:0 IST LINKS UNTEN!
