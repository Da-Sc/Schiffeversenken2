//entspricht Schnittstelle
#include "SPIEL.h"

SPIEL::SPIEL()
{
    //ctor

    //grundlegende Regeln (#Schiffe und Größe)
    BO_KOM::holeInstanz()->textAusgeben("Neues Spiel gestartet\n",false);//beim Spiel ausgeben
	do{
		BO_KOM::holeInstanz()->textAusgeben("Bitte die Anzahl an Schiffen (1-5) eingeben: ",false);//beim Spiel ausgeben
		AnzahlSchiffe=BO_KOM::holeInstanz()->intErfragen();
		if(AnzahlSchiffe<1 || AnzahlSchiffe>5) BO_KOM::holeInstanz()->textAusgeben("Ungültige Schiffanzahl!\n\n",false);//beim Spiel ausgeben
	}while(AnzahlSchiffe<1 || AnzahlSchiffe>5);

	//2 Spielfelder erzeugen
	(*Meer)=new SPIELFELD[2];
    for(int i=0; i<2; i++) (Meer[i])=new SPIELFELD(i, AnzahlSchiffe);

	//Schiffe anlegen
	Schifflaenge = new int[AnzahlSchiffe];
	BO_KOM::holeInstanz()->textAusgeben("Und nun bitte die Länge (2-5 Felder) der einzelnen Schiffe:\n",false);//beim Spiel ausgeben
	for(int i=0; i<AnzahlSchiffe; i++)
	{
        BO_KOM::holeInstanz()->textAusgeben("Schiff ",false);//beim Spiel ausgeben
		BO_KOM::holeInstanz()->zahlAusgeben(i+1,false);
		BO_KOM::holeInstanz()->textAusgeben(": ",false);
		int Laengetmp=0;
		Laengetmp=BO_KOM::holeInstanz()->intErfragen();
		if(Laengetmp<2 || Laengetmp>5)
		{
			BO_KOM::holeInstanz()->textAusgeben("Schiff hat eine falsche Länge!\n",false);//beim Spiel ausgeben
			i--;
		}
		else
		{
            Schifflaenge[i]=Laengetmp;
		    for(int j=0; j<2; j++) (Meer[j])->legeSchifflaengefest(j,Laengetmp);
		}
	}
}

SPIEL::~SPIEL()
{
    //dtor
}
