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

bool SPIELFELD::setzeSchiff(POSITION* positionAnfang, POSITION* positionEnde, int tmpSchiffnummer)//evtl. später noch durch differenzierte fehlermeldungen ersetzen
{
	int tmpSchifflaenge = gesetzteSchiffe[tmpSchiffnummer]->holeSchifflaenge();
	int *x= new int[tmpSchifflaenge];
	int *y= new int[tmpSchifflaenge];

	for(int i=0; i<2; i++)
	{
                if(positionAnfang->holePosition(i)<0 || positionEnde->holePosition(i)<0) return false;
	}
	//überprüfen: passt die Länge, ist es eine reihe
	//setze einzelne Positionen
        if( (positionAnfang->holeX()==positionEnde->holeX() && betrag(positionAnfang->holeY()-positionEnde->holeY())+1==tmpSchifflaenge) )
	{
		for(int i=0; i<tmpSchifflaenge; i++)
		{
                        x[i]=positionAnfang->holeX();
                        y[i]=kleineres(positionAnfang->holeY(),positionEnde->holeY())+i;
		}
	}
        else if( (positionAnfang->holeY()==positionEnde->holeY() && betrag(positionAnfang->holeX()-positionEnde->holeX())+1==tmpSchifflaenge) )
	{
		for(int i=0; i<tmpSchifflaenge; i++)
		{
                        y[i]=positionAnfang->holeY();
                        x[i]=kleineres(positionAnfang->holeX(),positionEnde->holeX())+i;
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

int SPIELFELD::Schuss(int x, int y)//überprüft Schuss auf gültigkeit und führt ihn aus. Bei -1 Fehler, 0 Wasser, 1 Schiff, 2 versenkt
{
    //Fehler beim Schuss aufs angegebene Feld?
    if(x>9 || y>9 || x<0 || y<0) return -1;
    if( !((Feld[x][y])->beschossen()) ) return -1;//ausführung falls möglich

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

char SPIELFELD::zeigeSpielfeldteilfuer(int tmpSpieler, int tmpx, int tmpy)
//Rückgabe:
//Schiff: s
//Schifftreffer: X
//Schiffversenkt: V
//Wasser oder unbekannt 0 (Zeichen!!!)
//Wassertreffer: W
{
    if(tmpSpieler<0 || tmpSpieler>2 || tmpx>9 || tmpy>9 || tmpx<0 || tmpy<0) return 0;

    //alles ausgeben
    if(tmpSpieler==Besitzer)
    {
        //Schiff?
        if( ((Feld[tmpx][tmpy])->istSchiff()) )
        {
            //getroffen?
            if( ((Feld[tmpx][tmpy])->istGetroffen()) )
            {
                if( ((Feld[tmpx][tmpy])->istVersenkt()) )
                {
                    return 'V';
                }
                else{return 'X';}
            }
            else{return 's';}
        }
        //->Wasser
        else
        {
            if(((Feld[tmpx][tmpy])->istGetroffen())) return 'W';
            return '0';
        }
    }
    //nur was gegner bekannt
    else
    {
        //Schiff?
        if( ((Feld[tmpx][tmpy])->istSchiff()) )
        {
            //getroffen?
            if( ((Feld[tmpx][tmpy])->istGetroffen()) ) return 'X';
            return '0';
        }
        //->Wasser
        else
        {
            if(((Feld[tmpx][tmpy])->istGetroffen())) return 'W';
            return '0';
        }
    }

    return 0;
}
bool SPIELFELD::verloren()
{
    return !AnzahlnochschwimmenderSchiffe;
}
