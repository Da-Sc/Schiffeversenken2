#include "SCHIFF.h"

SCHIFF::SCHIFF()
{
    //ctor
	Schifflaenge=0;
	nochSchwimmendeTeile=0;
	ausSchiffleinBestehend=0;
	aufFeld=0;
    positionenSchifflein=0;
}

SCHIFF::SCHIFF(SPIELFELD* tmpfeld)
{
    //ctor
    Schifflaenge=0;
    aufFeld=tmpfeld;
    ausSchiffleinBestehend=0;
	nochSchwimmendeTeile=0;
    positionenSchifflein=0;
}

SCHIFF::~SCHIFF()
{
    //dtor
    if(ausSchiffleinBestehend!=0)
    {
        for(int i=0; i<Schifflaenge; i++)
        {
            delete ausSchiffleinBestehend[i];
        }
    }
    if(positionenSchifflein!=0) delete positionenSchifflein;
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
    positionenSchifflein = new ERWEITERTE_POSITION(xy);//bringt das überhaupt was?
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
