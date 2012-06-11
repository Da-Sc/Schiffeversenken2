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
		    for(int j=0; j<2; j++) (Meer[j])->legeSchifflaengefest(i,Laengetmp);
		}
	}
}

void SPIEL::setzeSchiffe(int Spieler)
{
	int tmpPositionAnfang[2];//0=x, 1=y
	int tmpPositionEnde[2];//0=x, 1=y
	//zum Abfangen von Fehlern
	tmpPositionAnfang[0]=0;
	tmpPositionAnfang[1]=0;
	tmpPositionEnde[0]=0;
	tmpPositionEnde[1]=0;
	//ende

	BO_KOM::holeInstanz()->textAusgeben("Spieler ",true); //bei allen ausgeben -> anderer Spieler auch informiert
	BO_KOM::holeInstanz()->zahlAusgeben(Spieler+1,true);
	BO_KOM::holeInstanz()->textAusgeben(" bitte Schiffe setzen:\n",true);

	for(int i=0; i<AnzahlSchiffe; i++)
	{
		BO_KOM::holeInstanz()->textAusgeben("Schiff ",true); //bei allen ausgeben -> anderer Spieler auch informiert
		BO_KOM::holeInstanz()->zahlAusgeben(i+1,true);
		BO_KOM::holeInstanz()->textAusgeben(" Anfang: ",true);
		while(!(BO_KOM::holeInstanz()->positionErfragen(tmpPositionAnfang, 2)))
		{
			BO_KOM::holeInstanz()->textAusgeben("ungültige Position, bitte erneut eingeben:",true);
		}
		
		
		BO_KOM::holeInstanz()->textAusgeben("Schiff ",true); 
		BO_KOM::holeInstanz()->zahlAusgeben(i+1,true);
		BO_KOM::holeInstanz()->textAusgeben(" Ende: ",true);
		while(!(BO_KOM::holeInstanz()->positionErfragen(tmpPositionEnde, 2)))
		{
			BO_KOM::holeInstanz()->textAusgeben("ungültige Position, bitte erneut eingeben:",true);
		}

		//testausgaben
		BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionAnfang[0],true);
		BO_KOM::holeInstanz()->textAusgeben(" : ",true);
		BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionAnfang[1],true);
		BO_KOM::holeInstanz()->textAusgeben("\n",true);
		BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionEnde[0],true);
		BO_KOM::holeInstanz()->textAusgeben(" : ",true);
		BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionEnde[1],true);
		BO_KOM::holeInstanz()->textAusgeben("\n",true);
		//testausgaben

		if(Meer[Spieler]->setzeSchiff(tmpPositionAnfang,tmpPositionEnde,i))
		{
			BO_KOM::holeInstanz()->textAusgeben("Schiff erfolgreich gesetzt.\n",true);
		}
		else
		{
			BO_KOM::holeInstanz()->textAusgeben("Fehler beim platzieren (falsche Länge, anderes Schiff im Weg...)\n",true);
			i--;
		}
	}
}

SPIEL::~SPIEL()
{
    //dtor
}
