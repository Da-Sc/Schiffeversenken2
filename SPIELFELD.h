#ifndef SPIELFELD_H
#define SPIELFELD_H

#include "EINZELNES_FELD.h"
#include "SCHIFFLEIN.h"
class SCHIFFLEIN;

class SPIELFELD
{
    public:
        SPIELFELD(int);
        virtual ~SPIELFELD();
        bool ersetzedurchSchifflein(SCHIFFLEIN*,int, int);//x,y von 0 bis 10
        int Schuss(int,int);//Rückgabe: -1 Fehler; 0 Wasser; 1 Schiff; 2 versenkt
    protected:
    private:
        int Besitzer;
        EINZELNES_FELD* **Feld;//10x10 array wobei indizes die [x][y] koordinaten sind
};

#endif // SPIELFELD_H
