#include "SCHIFF.h"

SCHIFF::SCHIFF()
{
    //ctor
	Schifflaenge=0;
	nochSchwimmendeTeile=0;
	ausSchiffleinBestehend=0;
	aufFeld=0;
}

SCHIFF::SCHIFF(SPIELFELD* tmpfeld)
{
    //ctor
    aufFeld=tmpfeld;
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
    ausSchiffleinBestehend=new SCHIFFLEIN*[Schifflaenge];
    for(int i=0; i<Schifflaenge; i++)
    {
        ausSchiffleinBestehend[i]=new SCHIFFLEIN(this);
    }
}

int SCHIFF::holeSchifflaenge()
{
	return Schifflaenge;
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
