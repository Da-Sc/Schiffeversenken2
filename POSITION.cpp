#include "POSITION.h"

POSITION::POSITION()
{
    x=0;
    y=0;
}

bool POSITION::setzePosition(int tmpx, int tmpy)
{
    if(tmpx<0 || tmpx>9 || tmpy<0 || tmpy>9) return false;
    x=tmpx;
    y=tmpy;
    return true;
}

bool POSITION::setzePositionX(int tmpx)
{
    if(tmpx<0 || tmpx>9) return false;
    x=tmpx;
    return true;
}

bool POSITION::setzePositionY(int tmpy)
{
    if(tmpy<0 || tmpy>9) return false;
    y=tmpy;
    return true;
}

int POSITION::holePosition(int i)
{
    if(i==0) return x;
    if(i==1) return y;
    return -1;
}

int POSITION::holeX()
{
    return x;
}

int POSITION::holeY()
{
    return y;
}
