#ifndef BO_H
#define BO_H

#include "POSITION.h"

class BO
{
public:
    BO(){};
    virtual ~BO(){};
    virtual void textAusgeben(char*, bool)=0;//Auswahl Ausgabe an eigenen oder alle PCs (im 1PC-Spiel wird das ohne bool aufgerufen)
    virtual void zahlAusgeben(int, bool)=0;
    virtual int intErfragen()=0;// am besten noch überladen, fürs netzwerk wenns wichtig wird wer gefragt wird!
    virtual bool positionErfragen(POSITION*)=0;
    virtual void begruessung()=0;
    virtual void hinweis()=0;
    virtual void konsoleLoeschen()=0;
    virtual void spielfeldAusgabe(char*)=0;
protected:
    bool zustand;//true = Alles OK, false = upps Fehler
    bool hinweisausgegeben;
private:
};

#endif // BO_H
