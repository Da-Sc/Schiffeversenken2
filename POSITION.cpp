#include "POSITION.h"

POSITION::POSITION()
{
    x=0;
    y=0;
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

void POSITION::inkrementiereX()
{
    x++;
    if(x>9) x=0;
}

void POSITION::inkrementiereY()
{
    y++;
    if(y>9) y=0;
}

ERWEITERTE_POSITION::ERWEITERTE_POSITION(int tmplaenge)
{
    laenge=tmplaenge;
    x=new int[laenge];
    y=new int[laenge];
    for(int i=0; i<laenge; i++)
    {
        x[i]=0;
        y[i]=0;
    }
}
//KopierKonstruktor
ERWEITERTE_POSITION::ERWEITERTE_POSITION(ERWEITERTE_POSITION *tmpZukopieren)
{
    this->laenge=tmpZukopieren->holeLaenge();
    this->x=new int[laenge];
    this->y=new int[laenge];
    for(int i=0; i<laenge; i++)
    {
        x[i]=tmpZukopieren->holeX(i);
        y[i]=tmpZukopieren->holeY(i);
    }
}

ERWEITERTE_POSITION::~ERWEITERTE_POSITION()
{
    delete[] x;
    delete[] y;
}

bool ERWEITERTE_POSITION::setzePositionX(int i, int tmpx)
{
    if(tmpx<0 || tmpx>9 || i<0 || i>=laenge) return false;
    x[i]=tmpx;
    return true;
}

bool ERWEITERTE_POSITION::setzePositionY(int i, int tmpy)
{
    if(tmpy<0 || tmpy>9 || i<0 || i>=laenge) return false;
    y[i]=tmpy;
    return true;
}

int ERWEITERTE_POSITION::holeX(int i)
{
    if(i<0 || i>=laenge)return -1;
    return x[i];
}

int ERWEITERTE_POSITION::holeY(int i)
{
    if(i<0 || i>=laenge)return -1;
    return y[i];
}

int ERWEITERTE_POSITION::holeLaenge()
{
    return laenge;
}
