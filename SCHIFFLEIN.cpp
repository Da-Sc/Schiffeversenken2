#include "SCHIFFLEIN.h"

SCHIFFLEIN::SCHIFFLEIN()
{
    //ctor
}

SCHIFFLEIN::SCHIFFLEIN(SCHIFF* zugehoerigesSchiff)
{
    //ctor
    oberSchiff=zugehoerigesSchiff;
}

SCHIFFLEIN::~SCHIFFLEIN()
{
    //dtor
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
