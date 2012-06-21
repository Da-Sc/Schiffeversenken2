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
	nochSchwimmendeTeile=0;
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
	nochSchwimmendeTeile=Schifflaenge;
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

bool SCHIFF::setzeaufSpielfeld(ERWEITERTE_POSITION* xy)
{
    if(xy->holeLaenge()!=Schifflaenge)return false;
    for(int i=0; i<Schifflaenge; i++)
    {
        if(xy->holeX(i)<0 || xy->holeY(i)<0) return false;
        if(!aufFeld->ersetzedurchSchifflein(ausSchiffleinBestehend[i],xy->holeX(i),xy->holeY(i))) return false;
    }
    return true;
}

bool SCHIFF::istVersenkt()
{
    if(!nochSchwimmendeTeile)
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
