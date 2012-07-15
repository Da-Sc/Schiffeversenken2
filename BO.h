#ifndef BO_H
#define BO_H

#include "POSITION.h"

class BO
{
public:
    BO(){}
    virtual ~BO(){}
    virtual void textAusgeben(char const*, bool)=0;//für BO_GRA: bool=true -> nächste ausgabe löscht vorheriges; inzwischen falsch: Auswahl Ausgabe an eigenen oder alle PCs (im 1PC-Spiel wird das ohne bool aufgerufen)
    virtual void zahlAusgeben(int, bool)=0;
    virtual int intErfragen()=0;// am besten noch überladen, fürs netzwerk wenns wichtig wird wer gefragt wird!
    virtual bool positionErfragen(POSITION*,int)=0;
    virtual void begruessung()=0;
    virtual void hinweis()=0;
    virtual void konsoleLoeschen()=0;
    virtual void spielfeldAusgabe(char*)=0;
    virtual void gewinnerAusgeben(int)=0;
    virtual void ausgabeWasser()=0;
    virtual void ausgabeTreffer()=0;
    virtual void ausgabeVersenkt()=0;
    virtual void spieleranderReihe(int, bool)=0;
    virtual bool nachfrageGesetzteSchiffe(char*)=0;
    virtual bool schiffsetzen(int,POSITION*,POSITION*)=0;
protected:
    bool zustand;//true = Alles OK, false = upps Fehler
    bool hinweisausgegeben;
private:
};

#endif // BO_H
