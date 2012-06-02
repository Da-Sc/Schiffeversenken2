#include "EINZELNES_FELD.h"

EINZELNES_FELD::EINZELNES_FELD()
{
    getroffen=false;
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
