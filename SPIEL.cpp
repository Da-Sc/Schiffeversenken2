//entspricht Schnittstelle
#include "SPIEL.h"

SPIEL::SPIEL()
{
    //ctor
    auszugebendesSpielfeld = new char[200+1];
    for(int i=0; i<201; i++)
    {
        auszugebendesSpielfeld[i]=0;
    }

    //grundlegende Regeln (#Schiffe und Größe)
    BO_VERWALTUNG::holeInstanz()->konsoleLoeschen();
    BO_VERWALTUNG::holeInstanz()->textAusgeben("Neues Spiel gestartet\n",false);//beim Spiel ausgeben
    BO_VERWALTUNG::holeInstanz()->begruessung();

    BO_VERWALTUNG::holeInstanz()->textAusgeben("Allgemeine Regeln vereinbaren\n",false);
	do{
                BO_VERWALTUNG::holeInstanz()->textAusgeben("Bitte die Anzahl an Schiffen (1-5) eingeben: ",true);//beim Spiel ausgeben
                AnzahlSchiffe=BO_VERWALTUNG::holeInstanz()->intErfragen();
                if(AnzahlSchiffe<1 || AnzahlSchiffe>5) BO_VERWALTUNG::holeInstanz()->textAusgeben("Ungültige Schiffanzahl!\n",false);//BO_VERWALTUNG::holeInstanz()->textAusgeben("Ungültige Schiffanzahl!\n\n",true);//beim Spiel ausgeben
	}while(AnzahlSchiffe<1 || AnzahlSchiffe>5);

	//2 Spielfelder erzeugen
    for(int i=0; i<2; i++) (Meer[i])=new SPIELFELD(i, AnzahlSchiffe);

	//Schiffe anlegen
	Schifflaenge = new int[AnzahlSchiffe];
    BO_VERWALTUNG::holeInstanz()->textAusgeben("Und nun bitte die Länge (2-5 Felder) der einzelnen Schiffe\n",false);//beim Spiel ausgeben
	for(int i=0; i<AnzahlSchiffe; i++)
	{
        BO_VERWALTUNG::holeInstanz()->textAusgeben("Schiff ",false);//beim Spiel ausgeben
        BO_VERWALTUNG::holeInstanz()->zahlAusgeben(i+1,false);
        BO_VERWALTUNG::holeInstanz()->textAusgeben(": ",true);

		int Laengetmp=0;
        Laengetmp=BO_VERWALTUNG::holeInstanz()->intErfragen();

		if(Laengetmp<2 || Laengetmp>5)
		{
                        BO_VERWALTUNG::holeInstanz()->textAusgeben("Schiff hat eine falsche Länge!\n",false);//beim Spiel ausgeben
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
    POSITION *tmpPositionAnfang=new POSITION();
    POSITION *tmpPositionEnde=new POSITION();

    BO_VERWALTUNG::holeInstanz()->konsoleLoeschen();
    BO_VERWALTUNG::holeInstanz()->hinweis();

    //Feld zum orientieren Ausgeben!!!
    BO_VERWALTUNG::holeInstanz()->textAusgeben("SPIELER ",false); //bei allen ausgeben -> anderer Spieler auch informiert
    BO_VERWALTUNG::holeInstanz()->zahlAusgeben(Spieler+1,false);
    BO_VERWALTUNG::holeInstanz()->textAusgeben(" bitte Schiffe setzen:\n",false);

    BO_VERWALTUNG::holeInstanz()->spielfeldAusgabe(zeigeSpielfelder(2));

    bool falschgestzt=false;

    do{
        if(falschgestzt) Meer[Spieler]->entferneSchiffe();
        for(int i=0; i<AnzahlSchiffe; i++)
        {
            BO_VERWALTUNG::holeInstanz()->textAusgeben("Schiff ",false); //bei allen ausgeben -> anderer Spieler auch informiert
            BO_VERWALTUNG::holeInstanz()->zahlAusgeben(i+1,false);
            BO_VERWALTUNG::holeInstanz()->textAusgeben(" (Länge: ",false);
            BO_VERWALTUNG::holeInstanz()->zahlAusgeben(Schifflaenge[i],false);
            BO_VERWALTUNG::holeInstanz()->textAusgeben(") Anfang: ",false);
            if(!(BO_VERWALTUNG::holeInstanz()->positionErfragen(tmpPositionAnfang,Spieler)))
            {
                BO_VERWALTUNG::holeInstanz()->textAusgeben("ungültige Position, bitte erneut eingeben.\n",false);
                i--;
            }
            else
            {
                BO_VERWALTUNG::holeInstanz()->textAusgeben("Schiff ",false);
                BO_VERWALTUNG::holeInstanz()->zahlAusgeben(i+1,false);
                BO_VERWALTUNG::holeInstanz()->textAusgeben(" Ende: ",true);
                if(!(BO_VERWALTUNG::holeInstanz()->positionErfragen(tmpPositionEnde,Spieler)))
                {
                    BO_VERWALTUNG::holeInstanz()->textAusgeben("ungültige Position, bitte erneut eingeben.\n",false);
                    i--;
                }
                else
                {
                    if(!Meer[Spieler]->setzeSchiff(tmpPositionAnfang,tmpPositionEnde,i))
                    {
                        BO_VERWALTUNG::holeInstanz()->textAusgeben("Fehler beim platzieren (falsche Länge, anderes Schiff im Weg...)\n",false);
                        i--;
                    }
                    else
                    {
                        BO_VERWALTUNG::holeInstanz()->textAusgeben("Schiff erfolgreich gesetzt.\n",true);
                    }
                }
            }
        }
        falschgestzt = BO_VERWALTUNG::holeInstanz()->nachfrageGesetzteSchiffe(zeigeSpielfelder(Spieler));
    }while(falschgestzt);

    BO_VERWALTUNG::holeInstanz()->konsoleLoeschen();

}

SPIEL::~SPIEL()
{
    //dtor
    if(auszugebendesSpielfeld!=0) delete[] auszugebendesSpielfeld;
}


char* SPIEL::zeigeSpielfelder(int zeigenfuer)//2=allgemein, 3=alles
{
    if(zeigenfuer<0 || zeigenfuer>3) return 0;

    bool alles=false;
    if(zeigenfuer==3) alles=true;

    for(int i=0; i<201; i++)
    {
        auszugebendesSpielfeld[i]=0;
    }
    int tmpzaehler=0;

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
    return auszugebendesSpielfeld;
}

void SPIEL::spielen(int anderreihe)
{
    if(anderreihe>1 || anderreihe<-1) return;
    if(anderreihe==-1)
    {
        anderreihe=0;
        BO_VERWALTUNG::holeInstanz()->konsoleLoeschen();
        BO_VERWALTUNG::holeInstanz()->textAusgeben("SPIELSTART\n",false);
    }

    POSITION *schussaufposition =new POSITION();
    int ergebnis=-1;

    BO_VERWALTUNG::holeInstanz()->spielfeldAusgabe(zeigeSpielfelder(2));

    BO_VERWALTUNG::holeInstanz()->spieleranderReihe(anderreihe,false);
    BO_VERWALTUNG::holeInstanz()->positionErfragen(schussaufposition,(anderreihe+1)%2);

    ergebnis=Meer[(anderreihe+1)%2]->Schuss(schussaufposition->holeX(),schussaufposition->holeY());
    if(ergebnis<-1 || ergebnis>2) return;

    //Fehler
    while(ergebnis<0)
    {
        BO_VERWALTUNG::holeInstanz()->textAusgeben("Ausführung nicht möglich! Evtl. wurde dieses Feld bereits beschossen.\n",false);
        BO_VERWALTUNG::holeInstanz()->spieleranderReihe(anderreihe,true);
        BO_VERWALTUNG::holeInstanz()->positionErfragen(schussaufposition, (anderreihe+1)%2);
        ergebnis=Meer[(anderreihe+1)%2]->Schuss(schussaufposition->holeX(),schussaufposition->holeY());
    }

    //Wasser
    if(ergebnis==0)
    {
        BO_VERWALTUNG::holeInstanz()->ausgabeWasser();
        spielen((anderreihe+1)%2);
    }

    //Schiff
    if(ergebnis>0)
    {
        BO_VERWALTUNG::holeInstanz()->ausgabeTreffer();
        if(ergebnis==2) BO_VERWALTUNG::holeInstanz()->ausgabeVersenkt();
        if(Meer[(anderreihe+1)%2]->verloren())
        {
            BO_VERWALTUNG::holeInstanz()->spielfeldAusgabe(zeigeSpielfelder(3));
            BO_VERWALTUNG::holeInstanz()->gewinnerAusgeben(anderreihe);
            delete BO_VERWALTUNG::holeInstanz();
            return;
        }
        BO_VERWALTUNG::holeInstanz()->textAusgeben("Du bist ERNEUT an der Reihe! \n",false);
        spielen(anderreihe);
    }
}
