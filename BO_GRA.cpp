#include "BO_GRA.h"
#include <cstring>

BO_GRA::BO_GRA()
{
    zustand=true;
    hinweisausgegeben=false;
    neumachen=false;

    fensterFarbtiefe=24;
    fensterBreite=1024;
    fensterHoehe=512;

    anteilLinksfrei=47./1024.;
    anteilRechtsfrei=21./512.;
    anteilObenfrei=44./512.;
    anteilUntenfrei=44./512.;

    anteilSpielfeldHoehe=(462.-43.)/512.;
    anteilSpielfeldBreite=(469.-47.)/1024.;

    unterstuetzendeKom = new BO_KOM();

    //Initalisiere SDL
    int testSDL_init=SDL_Init(SDL_INIT_VIDEO);
    if (testSDL_init!=0)
    {
            std::cout << "Fehler bei Initalisieren von SDL." << std::endl;
            std::cin.get();
            exit(-1);
    }

    // Zeichenfläche erstellen
    hintergrundFenster = SDL_SetVideoMode(fensterBreite, fensterHoehe, fensterFarbtiefe, SDL_SWSURFACE);
    if (hintergrundFenster==0)
    {
            std::cout << "Fehler beim Erzeugen der Oberflche." << std::endl;
            std::cin.get();
            exit(-1);
    }

    SDL_WM_SetCaption("Schiffeversenken", "Schiffeversenken");

    SDL_Surface* bildFelder=0;

    //Hintergrund einfgen
    bildFelder = SDL_LoadBMP("/home/ds/Dokumente/Schiffeversenken2/Schiffeversenken2/grafiken/schiffeversenken_2Felder.bmp");
    if (bildFelder==0)
    {
            std::cout << "Grafik nicht verfuegbar." << std::endl;
            std::cin.get();
            exit(-1);
    }
    bildFelder->h=fensterHoehe;
    bildFelder->w=fensterBreite;
    //kopiere Bild (auch surface) auf schon fertiges Fenster
    SDL_BlitSurface(bildFelder,0,hintergrundFenster,0);
    //nicht mehr benötigte Bild-surface löschen
    SDL_FreeSurface(bildFelder);

    // Bildschirm Erneuern
    SDL_UpdateRect(hintergrundFenster, 0, 0, 0, 0);


/*
    // SDL initialisieren
      SDL_Init(SDL_INIT_VIDEO);

      // Unsere Zeichenfläche erstellen
      SDL_Surface* screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);

      // Die benötigte Farbe erstellen
      Uint32 color_red = SDL_MapRGB(screen->format, 255, 0, 0);

      // Fülle Zeichenfläche mit Farbe
      SDL_FillRect(screen, NULL, color_red);

      // Bildschirm Updaten
      SDL_UpdateRect(screen, 0, 0, 0, 0);


      // Event-Container
      SDL_Event event;

      // Event loop
      bool exitLoop = false;
      while(!exitLoop){

        // auf nächstes Event warten
        SDL_WaitEvent(&event);
        // Nun steckt in "event" ein Event

        switch(event.type)
        {
          case SDL_KEYDOWN:
            std::cout << "mod: " << event.key.keysym.mod
                 << "; scancode: " << (int)event.key.keysym.scancode
                 << "; sym: " << event.key.keysym.sym
                 << "; unicode: " << event.key.keysym.unicode
                 << std::endl;
            if(event.key.keysym.sym==SDLK_ESCAPE)
              exitLoop=true;
            break;
          case SDL_QUIT:
            exitLoop = true;
            break;
          default:
            break;
        }


      }

      //cout << "Press return to exit" << endl;
      //cin.get();

      // SDL korrekt herunterfahren
      SDL_Quit();*/
}

BO_GRA::~BO_GRA()
{
    // SDL korrekt herunterfahren
    if (hintergrundFenster!=NULL)
    {
            SDL_FreeSurface(hintergrundFenster);
    }
    SDL_Quit();

    delete unterstuetzendeKom;
    unterstuetzendeKom=0;

}

void BO_GRA::textAusgeben(char* tmpchar, bool tmpbool)
{
    unterstuetzendeKom->textAusgeben(tmpchar, tmpbool);
}

void BO_GRA::zahlAusgeben(int tmpzahl, bool tmpbool)
{

    unterstuetzendeKom->zahlAusgeben(tmpzahl, tmpbool);
}

int BO_GRA::intErfragen()
{
    return unterstuetzendeKom->intErfragen();
}

bool BO_GRA::positionErfragen(POSITION* tmpposition)
{
    return unterstuetzendeKom->positionErfragen(tmpposition);
}

void BO_GRA::begruessung()
{
    unterstuetzendeKom->begruessung();
}

void BO_GRA::hinweis()
{
    unterstuetzendeKom->hinweis();
}

void BO_GRA::konsoleLoeschen()
{
    unterstuetzendeKom->konsoleLoeschen();
}

void BO_GRA::spielfeldAusgabe(char* tmpFeldchar)
{
    //std::cout << "Hier sollte eine Ausgabe auftauchen: " << strlen(tmpFeldchar) << std::endl;
    if(strlen(tmpFeldchar)!=200)
    {
        std::cout << "Internes Problem, Program wird beendet" << std::endl;
        std::cin.get();
        exit(-1);
    }

    /*TEST der Feldgröße
    SDL_Rect Feldbereich;
    Feldbereich.h=anteilSpielfeldHoehe*fensterHoehe;
    Feldbereich.w=anteilSpielfeldBreite*fensterBreite;
    Feldbereich.x=anteilLinksfrei*fensterBreite;
    Feldbereich.y=anteilObenfrei*fensterHoehe;
    SDL_Rect Feldbereich2;
    Feldbereich2.h=anteilSpielfeldHoehe*fensterHoehe;
    Feldbereich2.w=anteilSpielfeldBreite*fensterBreite;
    Feldbereich2.x=(2*anteilLinksfrei+anteilRechtsfrei+anteilSpielfeldBreite)*fensterBreite;
    Feldbereich2.y=anteilObenfrei*fensterHoehe;
    Uint32 color_red = SDL_MapRGB(hintergrundFenster->format, 255, 0, 0);
    SDL_FillRect(hintergrundFenster, &Feldbereich, color_red);
    SDL_FillRect(hintergrundFenster, &Feldbereich2, color_red);
    ENDE TEST der Feldgröße*/

    /*TEST der einzelnen Felder
    SDL_Rect einzelFeldbereich;
    einzelFeldbereich.h=anteilSpielfeldHoehe/10.*fensterHoehe;
    einzelFeldbereich.w=anteilSpielfeldBreite/10.*fensterBreite;

    Uint32 color_red = SDL_MapRGB(hintergrundFenster->format, 255, 0, 0);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            einzelFeldbereich.x=FeldNRBreiteinPixel(i,false);
            einzelFeldbereich.y=FeldNRHoeheinPixel(j);
            SDL_FillRect(hintergrundFenster, &einzelFeldbereich, color_red);

            einzelFeldbereich.x=FeldNRBreiteinPixel(i,true);
            einzelFeldbereich.y=FeldNRHoeheinPixel(j);
            SDL_FillRect(hintergrundFenster, &einzelFeldbereich, color_red);
        }
    }
    TEST ende*/

    char pfad[]="/home/ds/Dokumente/Schiffeversenken2/Schiffeversenken2/grafiken/W.bmp";

    SDL_Rect position,index;
    position.x=0;
    position.y=0;
    index.x=0;
    index.y=0;
    bool rechts=false;
    for(int i=0; i<200; i++)
    {
        position.x=FeldNRBreiteinPixel(index.x,rechts)+1;
        position.y=FeldNRHoeheinPixel(index.y)+1;

        //entsprechendes Bild einsetzen
        if(tmpFeldchar[i]!='-')
        {
            pfad[64]=tmpFeldchar[i];

            SDL_Surface *einzelFeld = SDL_LoadBMP(pfad);
            if (einzelFeld==0)
            {
                    std::cout << "Grafik nicht verfuegbar." << std::endl;
                    std::cout << pfad << std::endl;
                    std::cin.get();
                    exit(-1);
            }
            einzelFeld->h=anteilSpielfeldHoehe/10.*fensterHoehe-2;
            einzelFeld->w=anteilSpielfeldBreite/10.*fensterBreite-2;
            position.h=einzelFeld->h;
            position.w=einzelFeld->w;
            SDL_BlitSurface(einzelFeld,0,hintergrundFenster,&position);
            SDL_FreeSurface(einzelFeld);

            //SDL_Flip(hintergrundFenster);
            SDL_UpdateRect(hintergrundFenster, 0, 0, 0, 0);
        }
        //position auf Feld bestimmen
        if((i+1)%10==0)
        {
            index.x=0;
            rechts=(rechts+1)%2;
            if((i+1)%20==0)
            {
                index.x=0;
                index.y++;
            }
        }
        else index.x++;
    }


    SDL_UpdateRect(hintergrundFenster, 0, 0, 0, 0);
    //unterstuetzendeKom->spielfeldAusgabe(tmpFeldchar);
}

//feldnr von 0 bis 9!
int BO_GRA::FeldNRBreiteinPixel(int feldnr, bool rechts)
{
    double feldgroesseB=anteilSpielfeldBreite/10.;

    if(rechts)
    {
        return (2*anteilLinksfrei+anteilRechtsfrei+anteilSpielfeldBreite+feldnr*feldgroesseB)*fensterBreite;
    }
    return (anteilLinksfrei+feldnr*feldgroesseB)*fensterBreite;
}

int BO_GRA::FeldNRHoeheinPixel(int feldnr)
{
    double feldgroesseH=anteilSpielfeldHoehe/10.;

    return (anteilObenfrei+feldnr*feldgroesseH)*fensterHoehe;
}
