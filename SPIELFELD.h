#ifndef SPIELFELD_H
#define SPIELFELD_H

#include "EINZELNES_FELD.h"
#include "SCHIFFLEIN.h"
#include "SCHIFF.h"

class SCHIFFLEIN;
class SCHIFF;

class SPIELFELD
{
    public:
        SPIELFELD();
        SPIELFELD(int,int);
        virtual ~SPIELFELD();
        void legeSchifflaengefest(int,int);
        bool ersetzedurchSchifflein(SCHIFFLEIN*,int, int);//x,y von 0 bis 10
        int Schuss(int,int);//Rückgabe: -1 Fehler; 0 Wasser; 1 Schiff; 2 versenkt
        void Schiffversenkt();
    protected:
    private:
        int Besitzer;
        EINZELNES_FELD* **Feld;//10x10 array wobei indizes die [x][y] koordinaten sind
        int AnzahlnochschwimmenderSchiffe;
        SCHIFF* *gesetzteSchiffe;
};

#endif // SPIELFELD_H
