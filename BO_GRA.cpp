#include "BO_GRA.h"
#include <cstring>
#include <cmath>
//allgemein mehr funktionen wie Gewinner ausgeben, spieler an der reihe etc., sodass die einzelnen bos besser angepasst werden können!
BO_GRA::BO_GRA()
{
    zustand=true;
    hinweisausgegeben=false;
    neumachen=false;
    gespeicherterChar=0;
    laengegespeicherterChar=0;

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
    int testSDL_init=SDL_Init(SDL_INIT_EVERYTHING);//früher SDL_INIT_VIDEO
    if (testSDL_init!=0)
    {
            std::cout << "Fehler bei Initalisieren von SDL." << std::endl;
            std::cin.get();
            exit(-1);
    }

    //Initialisiere Textausgabe
    if(TTF_Init()==-1)
    {
        std::cout << "Fehler beim Starten der Textausgabe." << std::endl;
        std::cin.get();
        exit(-1);
    }

    // Zeichenfläche erstellen
    hintergrundFenster = SDL_SetVideoMode(fensterBreite, fensterHoehe+88, fensterFarbtiefe, SDL_SWSURFACE);
    if (hintergrundFenster==0)
    {
            std::cout << "Fehler beim Erzeugen der Oberflche." << std::endl;
            std::cin.get();
            exit(-1);
    }
    // Die benötigte Farbe erstellen
    farbe_weiss = SDL_MapRGB(hintergrundFenster->format, 255, 255, 255);

    // Fülle Zeichenfläche mit Farbe
    SDL_FillRect(hintergrundFenster, 0, farbe_weiss);

    SDL_WM_SetCaption("Schiffeversenken", "Schiffeversenken");

    SDL_Surface* bildFelder=0;

    //Hintergrund einfgen
    bildFelder = SDL_LoadBMP("grafiken/schiffeversenken_2Felder.bmp");
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

    schriftart=TTF_OpenFont("grafiken/Arial_Black.ttf",24);//sollte zur Not sowohl in windows wie auch ubuntu (mscorefonts) verfügbar sein
    if (schriftart==NULL)
    {
        std::cout << "Schrift konnte nicht geladen werden." << std::endl;
        std::cin.get();
        exit(-1);
    }

    //Ort wo Schrift hinkommen soll (3 Zeilen) (liegt auf dem bmp Bild unterhalb des Spielfeldes)
    double dtmp;
    for(int i=0; i<3; i++)
    {
        dtmp=((1-(anteilObenfrei+anteilSpielfeldHoehe))*fensterHoehe+88)/3.;
        platzfuerSchrift[i].h=dtmp+1;
        platzfuerSchrift[i].w=fensterBreite;
        platzfuerSchrift[i].x=0;
        platzfuerSchrift[i].y=i*(platzfuerSchrift[i].h)+(anteilObenfrei+anteilSpielfeldHoehe)*fensterHoehe;
        //std::cout << "Hoehe: " << dtmp << " breite: " << platzfuerSchrift[i].w << " x Pos: " << platzfuerSchrift[i].x << " y Pos: " << platzfuerSchrift[i].y << std::endl;
    }
    kompletterPlatzfuerSchrift.x=0;
    kompletterPlatzfuerSchrift.y=(anteilObenfrei+anteilSpielfeldHoehe)*fensterHoehe;
    kompletterPlatzfuerSchrift.h=((1-(anteilObenfrei+anteilSpielfeldHoehe))*fensterHoehe+88);
    kompletterPlatzfuerSchrift.w=fensterBreite;

    aktuelleZeile=0;
    //Textfarbe
    textfarbe.r=0;
    textfarbe.g=0;
    textfarbe.b=0;

    eingabenPlatz.x=fensterBreite-100;
    eingabenPlatz.y=(anteilObenfrei+anteilSpielfeldHoehe)*fensterHoehe+platzfuerSchrift[0].h;
    eingabenPlatz.w=100;
    eingabenPlatz.h=60;

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
    delete[] gespeicherterChar;
    gespeicherterChar=0;

}

void BO_GRA::textAusgeben(char* tmpchar, bool tmpbool)
{
    if(neumachen)
    {
        aktuelleZeile=0;
        SDL_FillRect(hintergrundFenster, &kompletterPlatzfuerSchrift, farbe_weiss);
        SDL_UpdateRects(hintergrundFenster,1,&kompletterPlatzfuerSchrift);
    }
    else
    {
        SDL_FillRect(hintergrundFenster, &(platzfuerSchrift[aktuelleZeile]), farbe_weiss);
        SDL_UpdateRects(hintergrundFenster,1,&(platzfuerSchrift[aktuelleZeile]));
    }

    neumachen=false;
    //sonst Speicherzugriffsfehler
    int laengetmpchar=(int)strlen(tmpchar);
    char *tmpchar2=new char[laengetmpchar];

    for(int q=0; q<laengetmpchar; q++)
    {
        tmpchar2[q]=tmpchar[q];
    }
    //sonst Speicherzugriffsfehler

    bool neueZeile=false;
    for(int i=0; i<laengetmpchar; i++)
    {
        if(tmpchar2[i]=='\n')
        {
            neueZeile=true;
            tmpchar2[i]=' ';//Speicherzugriffsfehler?!?
        }
    }

    //durch vektor ersetzen?
    //allgemein char -> string!!!
    laengegespeicherterChar=arrayvergroessern<char>(&gespeicherterChar, laengegespeicherterChar, tmpchar2, laengetmpchar);

    //std::cout << "gespeicherterChar: " << gespeicherterChar << std::endl;
    SDL_Surface* textoberflaeche=TTF_RenderText_Blended(schriftart,gespeicherterChar,textfarbe);
    SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&(platzfuerSchrift[aktuelleZeile]));
    SDL_UpdateRects(hintergrundFenster,1,&(platzfuerSchrift[aktuelleZeile]));
    SDL_FreeSurface(textoberflaeche);

    if(neueZeile || tmpbool)
    {
        delete[] gespeicherterChar;
        gespeicherterChar=0;
        laengegespeicherterChar=0;
        aktuelleZeile++;
    }

    if(aktuelleZeile>2 || tmpbool)
    {
        neumachen=true;
    }
    delete[] tmpchar2;
    tmpchar2=0;
}

void BO_GRA::zahlAusgeben(int tmpzahl, bool tmpbool)
{
    if(tmpzahl<0) tmpzahl*=(-1);
    int tmplaenge;
    if(tmpzahl==0) tmplaenge=1;
    else tmplaenge=(int)(log10(tmpzahl)+1);

    char *tmpchar=new char[tmplaenge+1];

    for(int i=(tmplaenge-1); i>=0; i--)
    {
        tmpchar[i]=(tmpzahl%10)+48;
        tmpzahl=tmpzahl/10;
    }
    tmpchar[tmplaenge]=0;
    //std::cout << "Test fuer zahlausgeben: " << tmpchar << std::endl;
    this->textAusgeben(tmpchar, tmpbool);
    delete[] tmpchar;
    //unterstuetzendeKom->zahlAusgeben(tmpzahl, tmpbool);
}

int BO_GRA::intErfragen()
{
    bool schleifeBeenden = false;
    int tmprueckgabe=0;

    char eingabenAusgabe[10+1];
    int eingabeZiffer;

    for(int i=0; i<10+1; i++)
    {
        eingabenAusgabe[i]=0;
    }
    eingabeZiffer=0;

    SDL_Event ereignis; //event Container

    while(!schleifeBeenden){
        // auf nächstes Event warten
        SDL_WaitEvent(&ereignis);
        if(0 == SDL_WaitEvent(&ereignis))
        {
            std::cerr << "Fehler beim Warten auf Benutzerinteraktion." << std::endl;
            schleifeBeenden = true;
            tmprueckgabe=-1;
            break;
        }
        if(eingabeZiffer>10) eingabeZiffer=0;//segFault verhindern (unschön, sollte aber reichen)
        // Nun steckt in "ereignis" ein Event
        switch(ereignis.type)
        {
        case SDL_KEYDOWN:
        {
            int gedrueckteTaste=ereignis.key.keysym.sym;
            if(gedrueckteTaste>=SDLK_0 && gedrueckteTaste<=SDLK_9)
            {
                tmprueckgabe=tmprueckgabe*10+(gedrueckteTaste - 48);
                eingabenAusgabe[eingabeZiffer]=gedrueckteTaste;
                eingabeZiffer++;
            }
            else if(gedrueckteTaste>=SDLK_KP0 && gedrueckteTaste<=SDLK_KP9)
            {
                tmprueckgabe=tmprueckgabe*10+(gedrueckteTaste - 256);
                eingabenAusgabe[eingabeZiffer]=gedrueckteTaste-(256-48);
                eingabeZiffer++;
            }
            else if(gedrueckteTaste==SDLK_ESCAPE)
            {
                schleifeBeenden=true;
                tmprueckgabe=-1;
            }
            else if(gedrueckteTaste==SDLK_BACKSPACE)
            {
                if(eingabeZiffer>0)
                {
                    eingabeZiffer--;
                    eingabenAusgabe[eingabeZiffer]=0;
                    tmprueckgabe=tmprueckgabe/10;
                }
            }
            else if(gedrueckteTaste==SDLK_RETURN || gedrueckteTaste==SDLK_KP_ENTER)
            {
                schleifeBeenden=true;
            }
        }
            break;
        case SDL_QUIT:
            schleifeBeenden = true;
            exit(-1);
            break;
        default:
            break;
        }
        //eingabe Feld frei machen
        eingabenPlatz.w=100;
        eingabenPlatz.h=60;
        SDL_FillRect(hintergrundFenster, &eingabenPlatz, farbe_weiss);
        SDL_UpdateRects(hintergrundFenster,1,&eingabenPlatz);

        //neue Eingabe rendern und darstellen
        SDL_Surface* textoberflaeche=TTF_RenderText_Blended(schriftart,eingabenAusgabe,textfarbe);
        SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&eingabenPlatz);
        SDL_UpdateRects(hintergrundFenster,1,&eingabenPlatz);
        SDL_FreeSurface(textoberflaeche);
    }
    return tmprueckgabe;
}


bool BO_GRA::positionErfragen(POSITION* tmpposition, int tmpSpieler)
{
    bool schleifeBeenden = false;
    //int tmpx=0,tmpy=0;

    SDL_Event ereignis; //event Container
    while(!schleifeBeenden)
    {
        SDL_WaitEvent(&ereignis);
        if(0 == SDL_WaitEvent(&ereignis))
        {
            std::cerr << "Fehler beim Warten auf Benutzerinteraktion." << std::endl;
            schleifeBeenden = true;
            break;
        }
        //std::cout << "Ereignis!!!" << std::flush;
        switch(ereignis.type)
        {
        /*case SDL_MOUSEBUTTONUP:
            std::cout << std::endl << "Button: " << ereignis.button.button << " Maustaste Oben!!!" << std::endl;
            //break;*/
        case SDL_MOUSEBUTTONDOWN:
            //std::cout << std::endl << "Button: " << ereignis.button.button << " Maustaste Unten!!!" << std::endl;
            if(ereignis.button.button == SDL_BUTTON_LEFT)
            {
                //std::cout << "[ " << ereignis.button.x << " | " << ereignis.button.y << " ]" << std::endl;
                //std::cout << "[ " << pixelPositionzuFeldNrX(ereignis.button.x) << " | " << pixelPositionzuFeldNrY(ereignis.button.y) << " ]" << std::endl;
                //SDL_GetMouseState(&tmpx,&tmpy);
            if(tmpposition->setzePositionX(pixelPositionzuFeldNrX(ereignis.button.x,tmpSpieler)) && tmpposition->setzePositionY(pixelPositionzuFeldNrY(ereignis.button.y)))
            //if(tmpposition->setzePositionX(pixelPositionzuFeldNrX(tmpx,tmpSpieler)) && tmpposition->setzePositionY(pixelPositionzuFeldNrY(tmpy)))
            {
                schleifeBeenden=true;
                //std::cout << "Schleife sollte beendet werden!" << std::endl;
            }
            //else std::cout << "Problem :( " << std::endl;
            }
            break;
        case SDL_QUIT:
            schleifeBeenden = true;
            exit(-1);
            break;
        default:
            break;
        }
    }
    return true;
    //return unterstuetzendeKom->positionErfragen(tmpposition);
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

    char pfad[]="grafiken/W.bmp";

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
            pfad[9]=tmpFeldchar[i];

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

int BO_GRA::pixelPositionzuFeldNrX(double pixelX, bool rechts)
{
    double tmprueckgabe=-1;
    if(rechts) tmprueckgabe=((pixelX/fensterBreite)-(2*anteilLinksfrei+anteilRechtsfrei+anteilSpielfeldBreite))*10./anteilSpielfeldBreite;
    else tmprueckgabe=(pixelX/fensterBreite-anteilLinksfrei)*10./anteilSpielfeldBreite;
    if(tmprueckgabe>10 || tmprueckgabe<0) return -1;
    return (int)(tmprueckgabe);
}
int BO_GRA::pixelPositionzuFeldNrY(double pixelY)
{
    double tmprueckgabe=(pixelY/fensterHoehe-anteilObenfrei)*10./anteilSpielfeldHoehe;
    if(tmprueckgabe>10 || tmprueckgabe<0) return -1;
    return 9-(int)(tmprueckgabe);
}

void BO_GRA::gewinnerAusgeben(int tmpGewinner)
{
    if(tmpGewinner>1 || tmpGewinner<0) return;
    SDL_Rect mittenaufFenster;
    mittenaufFenster.h=150;
    mittenaufFenster.w=300;
    mittenaufFenster.x=fensterBreite/2-mittenaufFenster.w;
    mittenaufFenster.y=fensterHoehe/2-mittenaufFenster.h/2;

    char gewinnerChar1[]="Spieler ";
    int l1=8;//ohne 0, der wird später eingefügt;
    int l3=14;
    char gewinnerChar3[]=" hat Gewonnen!";
    char *gewinnerChar=new char[23+1];

    for(int i=0; i<l1; i++)
    {
        gewinnerChar[i]=gewinnerChar1[i];
    }
    gewinnerChar[l1]=tmpGewinner+1+48;
    for(int i=0; i<l3; i++)
    {
        gewinnerChar[i+l1+1]=gewinnerChar3[i];
    }
    gewinnerChar[l1+1+l3]=0;

    SDL_Color farbe_rot;
    farbe_rot.r=255;
    farbe_rot.b=0;
    farbe_rot.g=0;

    TTF_Font *gewinnerSchriftart=TTF_OpenFont("grafiken/Arial_Black.ttf",48);//sollte zur Not sowohl in windows wie auch ubuntu (mscorefonts) verfügbar sein
    if (gewinnerSchriftart==NULL)
    {
        std::cout << "Schrift konnte nicht geladen werden." << std::endl;
        std::cin.get();
        exit(-1);
    }

    SDL_Surface* textoberflaeche=TTF_RenderText_Blended(gewinnerSchriftart,gewinnerChar,farbe_rot);
    SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&mittenaufFenster);
    SDL_UpdateRects(hintergrundFenster,1,&mittenaufFenster);
    SDL_FreeSurface(textoberflaeche);

    delete[] gewinnerChar;
}
