#ifndef BO_KOM_H
#define BO_KOM_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "GLOBALEFUNKTIONEN.h"
#include "POSITION.h"

//Benutzeroberfläche Kommandozeile
//benutzen mit: BO_KOM::holeInstanz()->

class BO_KOM
{
    public:
        static BO_KOM* holeInstanz();
        virtual ~BO_KOM();
        virtual void textAusgeben(char*, bool);//Auswahl Ausgabe an eigenen oder alle PCs (im 1PC-Spiel wird das ohne bool aufgerufen)
        virtual void zahlAusgeben(int, bool);
        virtual int intErfragen();// am besten noch überladen, fürs netzwerk wenns wichtig wird wer gefragt wird!
        virtual bool positionErfragen(POSITION*);
        virtual void begruessung();
        virtual void hinweis();
        virtual void konsoleLoeschen();
        virtual void spielfeldAusgabe(char*);
    protected://private auch in vererbten aber trotzdem verfügbar
        BO_KOM();//damit genau eine Instanz von BO_KOM existiert: http://www.oop-trainer.de/Themen/Singleton.html
        static BO_KOM *instanz;
        bool zustand;//true = Alles OK, false = upps Fehler
        bool hinweisausgegeben;
    private:
        void zahlAusgeben(int);
        void textAusgeben(char*);//Ausgabe für 1PC Spiel
};

#endif // BO_KOM_H
