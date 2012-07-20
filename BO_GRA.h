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
    virtual void spieleranderReihe(int, bool);
    virtual bool nachfrageGesetzteSchiffe(char*);
    virtual bool schiffsetzen(int,int,POSITION*,POSITION*);
protected:
private:
    void erneuereGraphischeOberflaeche(bool);
    void erneuereGraphischeOberflaeche(bool,SDL_Rect);
    void warten(bool);
    void fuegeBMPein(char*, SDL_Rect, bool);
    void fuegeBMPein(char const*, SDL_Rect, bool);
    SDL_Surface* fuegeBMPein(SDL_Surface*, char*, SDL_Rect, bool);
    SDL_Surface* fuegeBMPein(SDL_Surface*, char const*, SDL_Rect, bool);
    void kopiereSoweitmoeglichAufFenster(SDL_Surface*,SDL_Rect,bool);//kopiert die Surface aufs hintergrundfenster an die Rect Position, verkleinert die Surfacegröße aber entsprechend!
    void kopiereAusschnittAufFenster(SDL_Surface*,SDL_Rect,SDL_Rect,bool);
    TTF_Font* ladeSchriftart(int groesse, TTF_Font* zurueckzugebenderFont);
    void fuellemitFarbe(Uint32 farbe, SDL_Rect ort, bool zeichne);
    void fuellemitFarbe(Uint32 farbe, bool zeichne);

    //Umrechnung von Feldindizes zu Pixelkoordinaten und umgekehrt
    //Umstellen auf SDL_Rect ?!?!
    int FeldNRHoeheinPixel(int);
    int FeldNRBreiteinPixel(int,bool);
    int pixelPositionzuFeldNrX(double, bool);
    int pixelPositionzuFeldNrY(double);

    int fensterHoehe;
    int fensterBreite;
    int fensterFarbtiefe;
    double anteilSpielfeldHoehe;
    double anteilSpielfeldBreite;
    //Fenster
    SDL_Surface* hintergrundFenster;
    SDL_Surface* bildFelder;
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
    bool mausBewegt(int x_neu, int y_neu);
    Uint8 SDL_KEYempfindlichAUF;
    bool ersterwartenaufruf;

    //für Textausgabe:
    bool neumachen;
    TTF_Font* schriftart;//Font
    SDL_Rect platzfuerSchrift[3];
    SDL_Rect kompletterPlatzfuerSchrift;
    SDL_Rect ausgabeFeldOben;
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
    SDL_Rect BMP_platz;

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
