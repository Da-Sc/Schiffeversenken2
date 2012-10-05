#ifndef SCHIFF_H
#define SCHIFF_H

#include "SCHIFFLEIN.h"
#include "SPIELFELD.h"
#include "POSITION.h"

class SCHIFFLEIN;
class SPIELFELD;

class SCHIFF
{
    public:
        SCHIFF();
        SCHIFF(SPIELFELD*);
        virtual ~SCHIFF();
        void legeSchifflaengefest(int);
        int holeSchifflaenge();
        bool setzeaufSpielfeld(ERWEITERTE_POSITION*, bool senkrecht);
        bool istVersenkt();
        void getroffen();
    protected:
    private:
        int Schifflaenge;
        int nochSchwimmendeTeile;
        SCHIFFLEIN* *ausSchiffleinBestehend;
        SPIELFELD* aufFeld;
        ERWEITERTE_POSITION* positionenSchifflein;
};

#endif // SCHIFF_H
