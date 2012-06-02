#include "SPIELFELD.h"

SPIELFELD::SPIELFELD(int Spielernummer)
{
    //ctor
    if(!(Spielernummer==0 || Spielernummer==1))Besitzer=-1;//Fehler
    else Besitzer=Spielernummer;

    **Feld = new EINZELNES_FELD[10];
    for(int i=0; i<10; i++) *(Feld[i])=new EINZELNES_FELD[10];

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        Feld[i][j] = new EINZELNES_FELD();
    }



}

SPIELFELD::~SPIELFELD()
{
    //dtor
}

bool SPIELFELD::ersetzedurchSchifflein(SCHIFFLEIN* zusetzendesSchiffsteil, int x, int y)
{

    if(zusetzendesSchiffsteil==0 || x>9 || y>9 || x<0 || y<0) return false;
    if(Feld[x][y]->istSchiff()) return false;

    EINZELNES_FELD *tmp=Feld[x][y];
    Feld[x][y]=zusetzendesSchiffsteil;
    delete tmp;
    return true;
}

int SPIELFELD::Schuss(int x, int y)//überprüft Schuss auf gültigkeit und führt ihn aus bei <0 Fehler, 0 Wasser, 1 Schiff, 2 versenkt
{
    //Fehler beim Schuss aufs angegebene Feld?
    if(x>9 || y>9 || x<0 || y<0) return -1;
    if( !((Feld[x][y])->beschossen()) ) return -1;

    //was ist eigentlich genau passiert?
    if( !((Feld[x][y])->istSchiff()) ) return 0;
    int tmprueckgabe=1;
    if( ((Feld[x][y])->istVersenkt()) ) tmprueckgabe++;
    return tmprueckgabe;

}
