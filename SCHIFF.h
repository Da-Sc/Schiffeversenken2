#ifndef SCHIFF_H
#define SCHIFF_H

#include "SCHIFFLEIN.h"
#include "SPIELFELD.h"
class SCHIFFLEIN;
class SPIELFELD;

class SCHIFF
{
    public:
        SCHIFF(int, SPIELFELD*);
        virtual ~SCHIFF();
        bool istVersenkt();
        void getroffen();
        bool setzeaufSpielfeld(int*,int*);
    protected:
    private:
        int Schifflaenge;
        int nochSchwimmend;
        SCHIFFLEIN* *ausSchiffleinBestehend;
        SPIELFELD* aufFeld;
};

#endif // SCHIFF_H
