#ifndef BO_GRA_H
#define BO_GRA_H

#include "BO.h"
#include "BO_KOM.h"
#include <SDL/SDL.h>
//#include <SDL.h>
#include <SDL/SDL_ttf.h>
//#include <SDL/SDL_image.h>
#include <iostream>
#include "GLOBALEFUNKTIONEN.h"

class BO_GRA : public BO
{
public:
    BO_GRA();
    virtual ~BO_GRA();
    virtual void textAusgeben(char const*, bool);//Auswahl Ausgabe an eigenen oder alle PCs (im 1PC-Spiel wird das ohne bool aufgerufen)
    virtual void zahlAusgeben(int, bool);
    virtual int intErfragen();// am besten noch überladen, fürs netzwerk wenns wichtig wird wer gefragt wird!
    virtual bool positionErfragen(POSITION*, int);
    virtual void begruessung();
    virtual void hinweis();
    virtual void konsoleLoeschen();
    virtual void spielfeldAusgabe(char*);
    virtual void gewinnerAusgeben(int);
    virtual void ausgabeWasser(){}
    virtual void ausgabeTreffer(){}
    virtual void ausgabeVersenkt();
protected:
private:
    void erneuereGraphischeOberflaeche();
    void warten(bool);

    //Umrechnung von Feldindizes zu Pixelkoordinaten und umgekehrt
    int FeldNRHoeheinPixel(int);
    int FeldNRBreiteinPixel(int,bool);
    int pixelPositionzuFeldNrX(double, bool);
    int pixelPositionzuFeldNrY(double);

    int fensterHoehe;
    int fensterBreite;
    int fensterFarbtiefe;
    double anteilSpielfeldHoehe;
    double anteilSpielfeldBreite;
    SDL_Surface* hintergrundFenster; //Fenster
    Uint32 farbe_weiss;
    //einzelne Felder
    SDL_Surface *einzelFeldWasser;
    SDL_Surface *einzelFeldSchiff;
    SDL_Surface *einzelFeldVersenkt;
    SDL_Surface *einzelFeldTreffer;

    //zum erneuern der oberflaeche
    char *letzteSpielfeldausgabe;
    //abfangen von doppelten ereignissen, da muastaste gedrückt und hoch dasselbe auslösen (->nur so aktzeptable sensitivität)
    int altPixelX,altPixelY;

    //für Textausgabe:
    bool neumachen;
    TTF_Font* schriftart;//Font
    SDL_Rect platzfuerSchrift[3];
    SDL_Rect kompletterPlatzfuerSchrift;
    SDL_Rect eingabenPlatz;
    int aktuelleZeile;
    SDL_Color textfarbe;//Textfarbe
    char *gespeicherterChar;
    int laengegespeicherterChar;

    //zum umrechnen
    double anteilLinksfrei;
    double anteilRechtsfrei;
    double anteilObenfrei;
    double anteilUntenfrei;

    //sonstiges
    template <typename T>
    int arrayvergroessern(T** pbasisarray, int laengebasis, T* zusatzarray, int laengezusatz)//gibt neue Länge zurück
    {
        T* basisarray;
        basisarray=*pbasisarray;
        laengebasis+=laengezusatz;
        T *tmpbasisarray = new T[laengebasis+1];
        if(basisarray!=0 && laengebasis!=0)
        {
            for(int i=0; i<(laengebasis-laengezusatz); i++)
            {
                tmpbasisarray[i]=basisarray[i];
            }
            delete[] basisarray;
            basisarray=0;
        }
        int j=0;
        for(int i=(laengebasis-laengezusatz); i<laengebasis; i++)
        {
            j=i-(laengebasis-laengezusatz);
            tmpbasisarray[i]=zusatzarray[j];
        }
        tmpbasisarray[laengebasis]='\0';
        *pbasisarray=tmpbasisarray;
        return laengebasis;
    }
};

#endif // BO_GRA_H
