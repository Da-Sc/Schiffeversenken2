#include "SCHIFF.h"

SCHIFF::SCHIFF()
{
    //ctor
}

SCHIFF::SCHIFF(SPIELFELD* tmpfeld)
{
    //ctor
    tmpfeld=aufFeld;
    ausSchiffleinBestehend=0;
}

SCHIFF::~SCHIFF()
{
    //dtor
    for(int i=0; i<Schifflaenge; i++)
    {
        delete ausSchiffleinBestehend[i];
    }
}

void SCHIFF::legeSchifflaengefest(int tmplaenge)
{
    Schifflaenge=tmplaenge;
    *ausSchiffleinBestehend=new SCHIFFLEIN[Schifflaenge];
    for(int i=0; i<Schifflaenge; i++)
    {
        ausSchiffleinBestehend[i]=new SCHIFFLEIN(this);
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
    if(!(Schifflaenge-nochSchwimmendeTeile))
    {
        aufFeld->Schiffversenkt();
        return true;
    }
    return false;
}

void SCHIFF::getroffen()
{
    nochSchwimmendeTeile--;
}
