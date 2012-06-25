#include "BO_GRA.h"

BO_GRA::BO_GRA()
{
    zustand=true;
    hinweisausgegeben=false;
    fensterFarbtiefe=24;
    fensterBreite=1024;
    fensterHoehe=512;

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
    //kopiere Bild (auch surface) auf schon fertiges Fenster
    SDL_BlitSurface(bildFelder,0,hintergrundFenster,0);
    //nicht mehr benötigte Bild-surface löschen
    SDL_FreeSurface(bildFelder);


    /*
    // Die benötigte Farbe erstellen
    hintergrundFarbe = SDL_MapRGB(hintergrundFenster->format, 0, 0, 255);

    // Fülle Zeichenfläche mit Farbe
    SDL_FillRect(hintergrundFenster, 0, hintergrundFarbe);
    */

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
    std::cout << "Hier sollte eine Ausgabe auftauchen" << std::endl;
    SDL_UpdateRect(hintergrundFenster, 0, 0, 0, 0);
    //unterstuetzendeKom->spielfeldAusgabe(tmpFeldchar);
}
