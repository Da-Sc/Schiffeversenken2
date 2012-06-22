#ifndef BO_GRA_H
#define BO_GRA_H

#include "BO.h"
#include "BO_KOM.h"
#include <SDL/SDL.h>
#include <iostream>

class BO_GRA : public BO
{
public:
    BO_GRA();
    virtual ~BO_GRA();
    virtual void textAusgeben(char*, bool);//Auswahl Ausgabe an eigenen oder alle PCs (im 1PC-Spiel wird das ohne bool aufgerufen)
    virtual void zahlAusgeben(int, bool);
    virtual int intErfragen();// am besten noch überladen, fürs netzwerk wenns wichtig wird wer gefragt wird!
    virtual bool positionErfragen(POSITION*);
    virtual void begruessung();
    virtual void hinweis();
    virtual void konsoleLoeschen();
    virtual void spielfeldAusgabe(char*);
protected:
private:
    //void zahlAusgeben(int);
    //void textAusgeben(char*);//Ausgabe für 1PC Spiel
    int fensterHoehe;
    int fensterBreite;
    int fensterFarbtiefe;
    SDL_Surface* hintergrundFenster; //Fenster
    Uint32 hintergrundFarbe; //Farbe
    SDL_Event ereignis; //event Container
    BO_KOM *unterstuetzendeKom;
};

#endif // BO_GRA_H
