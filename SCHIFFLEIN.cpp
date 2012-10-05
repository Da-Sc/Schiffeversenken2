#include "SCHIFFLEIN.h"

SCHIFFLEIN::SCHIFFLEIN()
{
    //ctor
    oberSchiff=0;
    typ=0;
}

/*
 *Schlüssel für Typ:
 *waagrecht: Großbuchstaben: AB CDE FGHI JKLMN
 *senkrecht: Kleinbuchstaben: ab cde fghi jklmn
 */
SCHIFFLEIN::SCHIFFLEIN(SCHIFF* zugehoerigesSchiff, int laenge, int position)
{
    //ctor
    oberSchiff=zugehoerigesSchiff;
    int tmp=0;
    switch(laenge)
    {
    case 3:
        tmp=2;
        break;
    case 4:
        tmp=5;
        break;
    case 5:
        tmp=9;
        break;
    default:
        break;
    }

    typ = char(65+tmp+position);
}

SCHIFFLEIN::~SCHIFFLEIN()
{
    //dtor
    oberSchiff=0;
}

bool SCHIFFLEIN::istSchiff()
{
    return true;
}
bool SCHIFFLEIN::istVersenkt()
{
    return oberSchiff->istVersenkt();
}

bool SCHIFFLEIN::beschossen()
{
    if(getroffen) return false;
    getroffen=true;
    oberSchiff->getroffen();
    return true;
}

void SCHIFFLEIN::setzesenkrecht(bool senkrecht)
{
    if(senkrecht && typ<='N') typ+=32;
    else if(!senkrecht && typ>='a') typ-=32;
}
