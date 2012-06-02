#include "SCHIFF.h"

SCHIFF::SCHIFF(int tmplaenge, SPIELFELD* tmpfeld)
{
    //ctor
    Schifflaenge=tmplaenge;
    *ausSchiffleinBestehend=new SCHIFFLEIN[Schifflaenge];
    for(int i=0; i<Schifflaenge; i++)
    {
        ausSchiffleinBestehend[i]=new SCHIFFLEIN(this);
    }

    tmpfeld=aufFeld;
}

SCHIFF::~SCHIFF()
{
    //dtor
    for(int i=0; i<Schifflaenge; i++)
    {
        delete ausSchiffleinBestehend[i];
    }
}

bool SCHIFF::setzeaufSpielfeld(int* x, int* y)
{
    for(int i=0; i<Schifflaenge; i++)
    {
        if(!aufFeld->ersetzedurchSchifflein(ausSchiffleinBestehend[i],x[i],y[i])) return false;
    }
    return true;

}

bool SCHIFF::istVersenkt()
{
    return !(Schifflaenge-nochSchwimmend);
}

void SCHIFF::getroffen()
{
    nochSchwimmend--;
}
