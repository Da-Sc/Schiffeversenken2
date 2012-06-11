#include "SPIELFELD.h"

SPIELFELD::SPIELFELD()
{
    //default konst
    Besitzer=-1;
    Feld=0;
    AnzahlnochschwimmenderSchiffe=0;
}

SPIELFELD::SPIELFELD(int Spielernummer, int tmpSchiffe)
{
    //ctor
    if(!(Spielernummer==0 || Spielernummer==1))Besitzer=-1;//Fehler
    else Besitzer=Spielernummer;

    Feld = new EINZELNES_FELD**[10];
    for(int i=0; i<10; i++) (Feld[i])=new EINZELNES_FELD*[10];

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        (Feld[i][j]) = new EINZELNES_FELD();
    }

    AnzahlnochschwimmenderSchiffe=tmpSchiffe;
    gesetzteSchiffe=new SCHIFF*[AnzahlnochschwimmenderSchiffe];
    for(int i=0; i<AnzahlnochschwimmenderSchiffe; i++)
    {
        (gesetzteSchiffe[i])=new SCHIFF(this);
    }

}

SPIELFELD::~SPIELFELD()
{
    //dtor
}

void SPIELFELD::legeSchifflaengefest(int tmpnummer, int tmplaenge)
{
    (gesetzteSchiffe[tmpnummer])->legeSchifflaengefest(tmplaenge);
}

bool SPIELFELD::istdaeinSchiff(int* x, int* y, int laengeArray)
{
	for(int i=0; i<laengeArray;i++) if(Feld[x[i]][y[i]]->istSchiff())return true;
	return false;
	
}

bool SPIELFELD::setzeSchiff(int* positionAnfang, int* positionEnde, int tmpSchiffnummer)//evtl. später noch durch differenzierte fehlermeldungen ersetzen
{
	int tmpSchifflaenge = gesetzteSchiffe[tmpSchiffnummer]->holeSchifflaenge();
	int *x= new int[tmpSchifflaenge];
	int *y= new int[tmpSchifflaenge];

	for(int i=0; i<2; i++)
	{
		if(positionAnfang[i]>9 || positionAnfang[i]<0 || positionEnde[i]>9 || positionEnde[i]<0) return false;
	}
	//überprüfen: passt die Länge, ist es eine reihe
	//setze einzelne Positionen
	if( (positionAnfang[0]==positionEnde[0] && betrag(positionAnfang[1]-positionEnde[1])+1==tmpSchifflaenge) )
	{
		for(int i=0; i<tmpSchifflaenge; i++)
		{
			x[i]=positionAnfang[0];
			y[i]=kleineres(positionAnfang[1],positionEnde[1])+i;
		}
	}
	else if( (positionAnfang[1]==positionEnde[1] && betrag(positionAnfang[0]-positionEnde[0])+1==tmpSchifflaenge) )
	{
		for(int i=0; i<tmpSchifflaenge; i++)
		{
			y[i]=positionAnfang[1];
			x[i]=kleineres(positionAnfang[0],positionEnde[0])+i;
		}
	}
	else return false;

	if(istdaeinSchiff(x,y,tmpSchifflaenge)) return false;
	if(!gesetzteSchiffe[tmpSchiffnummer]->setzeaufSpielfeld(x,y)) return false;

	delete[] x;
	delete[] y;
    return true;

}

bool SPIELFELD::ersetzedurchSchifflein(SCHIFFLEIN* zusetzendesSchiffsteil, int x, int y)
{

    if(zusetzendesSchiffsteil==0 || x>9 || y>9 || x<0 || y<0) return false;
    if((Feld[x][y])->istSchiff()) return false;

    EINZELNES_FELD *tmp=Feld[x][y];
    Feld[x][y]=zusetzendesSchiffsteil;
    delete tmp;
	tmp=0;
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

void SPIELFELD::Schiffversenkt()
{
    AnzahlnochschwimmenderSchiffe--;
}

int betrag(int zahl)
{
	if(zahl >= 0) return zahl;
	return zahl*(-1);
}
int kleineres(int a, int b)
{
	if(a<=b) return a;
	return b;
}
