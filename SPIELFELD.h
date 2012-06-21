#ifndef SPIELFELD_H
#define SPIELFELD_H

#include "EINZELNES_FELD.h"
#include "SCHIFFLEIN.h"
#include "SCHIFF.h"
#include "GLOBALEFUNKTIONEN.h"
#include "POSITION.h"

class SCHIFFLEIN;
class SCHIFF;

class SPIELFELD
{
    public:
        SPIELFELD();
        SPIELFELD(int,int);
        virtual ~SPIELFELD();
        void legeSchifflaengefest(int,int);
        bool setzeSchiff(POSITION*,POSITION*,int);
        bool ersetzedurchSchifflein(SCHIFFLEIN*,int, int);//x,y von 0 bis 9
        int Schuss(int,int);//Rückgabe: -1 Fehler; 0 Wasser; 1 Schiff; 2 versenkt
        void Schiffversenkt();
        char zeigeSpielfeldteilfuer(int, int, int);//int: für welchen Spieler ausgeben (0,1,2=einzelSpielerausgabe), int, int: x,y koordinate); Rückgabe: (später zu enum!, oder klasse)
        bool verloren();
    protected:
    private:
        int Besitzer;
        EINZELNES_FELD* **Feld;//10x10 array wobei indizes die [x][y] koordinaten sind
        int AnzahlnochschwimmenderSchiffe;
        SCHIFF* *gesetzteSchiffe;
        bool istdaeinSchiff(ERWEITERTE_POSITION* xy);//true = Schiff auf einer der angegebenen Positionen
};

#endif // SPIELFELD_H
