#include "EINZELNES_FELD.h"

EINZELNES_FELD::EINZELNES_FELD()
{
    getroffen=false;
    typ='W';
    //ctor
}

EINZELNES_FELD::~EINZELNES_FELD()
{
    //dtor
}

bool EINZELNES_FELD::beschossen()
{
    if(getroffen) return false;
    getroffen=true;
    return true;
}
bool EINZELNES_FELD::istSchiff()
{
    return false;
}
bool EINZELNES_FELD::istVersenkt()
{
    return false;
}
bool EINZELNES_FELD::istGetroffen()
{
    return getroffen;
}

char EINZELNES_FELD::holeTyp()
{
    return typ;
}
