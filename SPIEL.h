#ifndef SPIEL_H
#define SPIEL_H

#include "SPIELFELD.h"
#include "BO_KOM.h"

class SPIEL
{
    public:
        SPIEL();
        virtual ~SPIEL();
		void setzeSchiffe(int); //Setzt Schiffe für Spieler (übergebener int, 0 oder 1)
		void zeigeSpielfelder(int);
		void spielen(int);
    protected:
    private:
        SPIELFELD* Meer[2];//2 spielfelder
        int AnzahlSchiffe;
        int* Schifflaenge;
};

#endif // SPIEL_H
