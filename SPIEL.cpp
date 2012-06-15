//entspricht Schnittstelle
#include "SPIEL.h"

SPIEL::SPIEL()
{
    //ctor

    //grundlegende Regeln (#Schiffe und Größe)
    BO_KOM::holeInstanz()->textAusgeben("Neues Spiel gestartet\n",false);//beim Spiel ausgeben
    BO_KOM::holeInstanz()->begruessung();
    BO_KOM::holeInstanz()->textAusgeben("\nAllgemeine Regeln vereinbaren:\n\n",true);
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

    BO_KOM::holeInstanz()->konsoleLoeschen();
	BO_KOM::holeInstanz()->hinweis();

//Feld zum orientieren Ausgeben!!!
	BO_KOM::holeInstanz()->textAusgeben("SPIELER ",true); //bei allen ausgeben -> anderer Spieler auch informiert
	BO_KOM::holeInstanz()->zahlAusgeben(Spieler+1,true);
	BO_KOM::holeInstanz()->textAusgeben(" bitte Schiffe setzen:\n",true);

	BO_KOM::holeInstanz()->textAusgeben("\n",true);
	zeigeSpielfelder(2);
	BO_KOM::holeInstanz()->textAusgeben("\n",true);

	for(int i=0; i<AnzahlSchiffe; i++)
	{
		BO_KOM::holeInstanz()->textAusgeben("Schiff ",true); //bei allen ausgeben -> anderer Spieler auch informiert
		BO_KOM::holeInstanz()->zahlAusgeben(i+1,true);
		BO_KOM::holeInstanz()->textAusgeben(" (Länge: ",true);
		BO_KOM::holeInstanz()->zahlAusgeben(Schifflaenge[i],true);
		BO_KOM::holeInstanz()->textAusgeben(") Anfang: ",true);
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
		/*BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionAnfang[0],true);
		BO_KOM::holeInstanz()->textAusgeben(" : ",true);
		BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionAnfang[1],true);
		BO_KOM::holeInstanz()->textAusgeben("\n",true);
		BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionEnde[0],true);
		BO_KOM::holeInstanz()->textAusgeben(" : ",true);
		BO_KOM::holeInstanz()->zahlAusgeben(tmpPositionEnde[1],true);
		BO_KOM::holeInstanz()->textAusgeben("\n",true);*/
		//testausgaben

		if(Meer[Spieler]->setzeSchiff(tmpPositionAnfang,tmpPositionEnde,i))
		{
			BO_KOM::holeInstanz()->textAusgeben("Schiff erfolgreich gesetzt.\n\n",true);
		}
		else
		{
			BO_KOM::holeInstanz()->textAusgeben("Fehler beim platzieren (falsche Länge, anderes Schiff im Weg...)\n",true);
			i--;
		}
	}
	BO_KOM::holeInstanz()->konsoleLoeschen();
}

SPIEL::~SPIEL()
{
    //dtor
}


void SPIEL::zeigeSpielfelder(int zeigenfuer)//2=allgemein, 3=alles
{
    if(zeigenfuer<0 || zeigenfuer>3) return;

    bool alles=false;
    if(zeigenfuer==3) alles=true;

    char auszugebendesSpielfeld[200];
    for(int i=0; i<200; i++)
    {
        auszugebendesSpielfeld[i]=0;
    }
    int tmpzaehler=0;
    int allesoderallgemein=2;

    for(int zeile=9; zeile>=0; zeile--)
    {
        for(int spieler=0; spieler<2; spieler++)
        {
            for(int spalte=0; spalte<10; spalte++)
            {
                if(alles) zeigenfuer=spieler;
                auszugebendesSpielfeld[tmpzaehler]=Meer[spieler]->zeigeSpielfeldteilfuer(zeigenfuer,spalte,zeile);
                tmpzaehler++;
            }
        }
    }
    BO_KOM::holeInstanz()->spielfeldAusgabe(auszugebendesSpielfeld);

/*
    char spielerchar[37]={'S','p','i','e','l','e','r',' ','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S','p','i','e','l','e','r',' ','2','\n'};
    char zahlen[50]={' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','7',' ','8',' ','9',' ','1','0',' ',' ',' ',' ',' ',' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','7',' ','8',' ','9',' ','1','0','\n'};

    for(int i=0; i<37; i++)
    {
        auszugebendesSpielfeld[tmpzaehler]=spielerchar[i];
        tmpzaehler++;
    }
    for(int i=0; i<50; i++)
    {
        auszugebendesSpielfeld[tmpzaehler]=zahlen[i];
        tmpzaehler++;
    }


    for(int zeile=9; zeile>=0; zeile--)
    {
        for(int spieler=0; spieler<2; spieler++)
        {
                    auszugebendesSpielfeld[tmpzaehler]=74-zeile;
                    tmpzaehler++;
                    auszugebendesSpielfeld[tmpzaehler]=' ';
                    tmpzaehler++;

            for(int spalte=0; spalte<10; spalte++)
            {
                if(alles) zeigenfuer=spieler;
                auszugebendesSpielfeld[tmpzaehler]=Meer[spieler]->zeigeSpielfeldteilfuer(zeigenfuer,spalte,zeile);
                tmpzaehler++;
                auszugebendesSpielfeld[tmpzaehler]=' ';
                tmpzaehler++;
            }
            for(int i=0; i<5; i++)
            {
                auszugebendesSpielfeld[tmpzaehler]=' ';
                tmpzaehler++;
            }
        }
        auszugebendesSpielfeld[tmpzaehler]='\n';
        tmpzaehler++;
    }
    BO_KOM::holeInstanz()->textAusgeben(auszugebendesSpielfeld, true);*/
}

void SPIEL::spielen(int anderreihe)
{
    if(anderreihe>1 || anderreihe<-1) return;
    if(anderreihe==-1)
    {
        anderreihe=0;
        BO_KOM::holeInstanz()->konsoleLoeschen();
        BO_KOM::holeInstanz()->textAusgeben("SPIELSTART\n",true);
    }

    int schussaufposition[2];
    int ergebnis=-1;

    zeigeSpielfelder(2);

    BO_KOM::holeInstanz()->textAusgeben("Schuss von SPIELER ",true);
    BO_KOM::holeInstanz()->zahlAusgeben(anderreihe+1,true);
    BO_KOM::holeInstanz()->textAusgeben(" auf: ",true);
    BO_KOM::holeInstanz()->positionErfragen(schussaufposition,2);

    ergebnis=Meer[anderreihe]->Schuss(schussaufposition[0],schussaufposition[1]);
    if(ergebnis<-1 || ergebnis>2) return;

    //Fehler
    while(ergebnis<0)
    {
        BO_KOM::holeInstanz()->textAusgeben("Ausführung nicht möglich! Evtl. wurde dieses Feld bereits beschossen.\n",true);
        BO_KOM::holeInstanz()->textAusgeben("SPIELER ",true);
        BO_KOM::holeInstanz()->zahlAusgeben(anderreihe+1,true);
        BO_KOM::holeInstanz()->textAusgeben(" bitte widerholen: ",true);
        BO_KOM::holeInstanz()->positionErfragen(schussaufposition,2);
        ergebnis=Meer[anderreihe]->Schuss(schussaufposition[0],schussaufposition[1]);
    }

    //Wasser
    if(ergebnis==0)
    {
        BO_KOM::holeInstanz()->textAusgeben("WASSER :( \n\n",true);
        spielen((anderreihe+1)%2);
    }

    //Schiff
    if(ergebnis>0)
    {
        BO_KOM::holeInstanz()->textAusgeben("TREFFER ! :) \n",true);
        if(ergebnis==2) BO_KOM::holeInstanz()->textAusgeben("Schiff VERSENKT ;) \n",true);
        BO_KOM::holeInstanz()->textAusgeben("Du bist erneut an der Reihe! \n",true);
        if(Meer[(anderreihe+1)%2]->verloren())
        {
            BO_KOM::holeInstanz()->textAusgeben("\n\nDu hast GEWONNEN!!!\n",true);
            return;
        }
        spielen(anderreihe);
    }
}
