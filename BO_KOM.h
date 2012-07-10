#ifndef BO_KOM_H
#define BO_KOM_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "GLOBALEFUNKTIONEN.h"
#include "POSITION.h"
#include "BO.h"

//Benutzeroberfläche Kommandozeile


class BO_KOM : public BO
{
    public:
        BO_KOM();
        virtual ~BO_KOM();
        virtual void textAusgeben(char const*, bool);//Auswahl Ausgabe an eigenen oder alle PCs (im 1PC-Spiel wird das ohne bool aufgerufen)
        virtual void zahlAusgeben(int, bool);
        virtual int intErfragen();// am besten noch überladen, fürs netzwerk wenns wichtig wird wer gefragt wird!
        virtual bool positionErfragen(POSITION*,int);
        virtual void begruessung();
        virtual void hinweis();
        virtual void konsoleLoeschen();
        virtual void spielfeldAusgabe(char*);
        virtual void gewinnerAusgeben(int);
        virtual void ausgabeWasser();
        virtual void ausgabeTreffer();
        virtual void ausgabeVersenkt();
        virtual void spieleranderReihe(int, bool);
    protected:
        //bool zustand;//true = Alles OK, false = upps Fehler
        //bool hinweisausgegeben;
    private:
        void zahlAusgeben(int);
        void textAusgeben(char const*);//Ausgabe für 1PC Spiel
        virtual bool positionErfragen(POSITION*);
};

#endif // BO_KOM_H
