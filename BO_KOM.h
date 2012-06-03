#ifndef BO_KOM_H
#define BO_KOM_H

#include <iostream>

//Benutzeroberfläche Kommandozeile
//benutzen mit: BO_KOM::holeInstanz()->

class BO_KOM
{
    public:
        static BO_KOM* holeInstanz();
        virtual ~BO_KOM();
        virtual void textAusgeben(char*, bool);//Auswahl Ausgabe an eigenen oder alle PCs (im 1PC-Spiel wird das ohne bool aufgerufen)
        virtual void zahlAusgeben(int, bool);
        int intErfragen();
        //void positionErfragen(int*);
    protected://private auch in vererbten aber trotzdem verfügbar
        BO_KOM();//damit genau eine Instanz von BO_KOM existiert: http://www.oop-trainer.de/Themen/Singleton.html
    private:
        void zahlAusgeben(int);
        void textAusgeben(char*);//Ausgabe für 1PC Spiel
        static BO_KOM *instanz;
        bool zustand;//true = Alles OK, false = upps Fehler
};

#endif // BO_KOM_H
