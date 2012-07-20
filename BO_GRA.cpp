#include <ctime>
#include "BO_GRA.h"
#include <cmath>
//allgemein mehr funktionen wie Gewinner ausgeben, spieler an der reihe etc., sodass die einzelnen bos besser angepasst werden können!
BO_GRA::BO_GRA()
{
    zustand=true;
    hinweisausgegeben=false;
    neumachen=false;
    gespeicherterChar=0;
    laengegespeicherterChar=0;
    schriftart=0;

    letzteSpielfeldausgabe = 0;
    altPixelX=-10;
    altPixelY=-10;
    SDL_KEYempfindlichAUF = SDL_KEYDOWN;
    ersterwartenaufruf=true;

    //zusatz Felder für Schrift, oben und unten
    int zusatzFensterOben = 35;
    int zusatzFensterUnten = 88;

    fensterFarbtiefe=24;
    fensterBreite=1024;
    fensterHoehe=512;

    BMP_platz.h=fensterHoehe;
    BMP_platz.w=fensterBreite;
    BMP_platz.x=0;
    BMP_platz.y=zusatzFensterOben;

    //neue Fenstergröße
    fensterHoehe=fensterHoehe+zusatzFensterOben+zusatzFensterUnten;

    //freie Anteile (= keine Spielfeld-felder) am angezeigten Fenster
    anteilLinksfrei=47./1024.;
    anteilRechtsfrei=21./512.;
    anteilObenfrei=(44.+zusatzFensterOben)/(512.+zusatzFensterOben+zusatzFensterUnten);
    anteilUntenfrei=(44.+zusatzFensterUnten)/(512.+zusatzFensterUnten+zusatzFensterOben);

    anteilSpielfeldHoehe=(462.-43.)/(512.+zusatzFensterOben+zusatzFensterUnten);
    anteilSpielfeldBreite=(469.-47.)/1024.;

    //Initalisiere SDL
    int testSDL_init=SDL_Init(SDL_INIT_EVERYTHING);
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
    hintergrundFenster = SDL_SetVideoMode(fensterBreite, fensterHoehe, fensterFarbtiefe, SDL_SWSURFACE);
    if (hintergrundFenster==0)
    {
            std::cout << "Fehler beim Erzeugen der Oberflche." << std::endl;
            std::cin.get();
            exit(-1);
    }
    // Die benötigte Farbe erstellen
    farbe_weiss = SDL_MapRGB(hintergrundFenster->format, 255, 255, 255);

    SDL_WM_SetCaption("Schiffeversenken", "Schiffeversenken");

    //SDL_FillRect(hintergrundFenster, 0, farbe_weiss);
    fuellemitFarbe(farbe_weiss,false);
    bildFelder = fuegeBMPein(bildFelder,"grafiken/schiffeversenken_2Felder.bmp",BMP_platz,false);
    SDL_Flip(hintergrundFenster);

    schriftart = ladeSchriftart(24,schriftart);

    //Ort wo Schrift hinkommen soll (3 Zeilen) (liegt auf dem bmp Bild unterhalb des Spielfeldes)
    double dtmp;
    for(int i=0; i<3; i++)
    {
        dtmp=((1-(anteilObenfrei+anteilSpielfeldHoehe))*fensterHoehe)/3.;
        platzfuerSchrift[i].h=dtmp+1;
        platzfuerSchrift[i].w=fensterBreite;
        platzfuerSchrift[i].x=0;
        platzfuerSchrift[i].y=i*(platzfuerSchrift[i].h)+(anteilObenfrei+anteilSpielfeldHoehe)*fensterHoehe;
    }
    kompletterPlatzfuerSchrift.x=0;
    kompletterPlatzfuerSchrift.y=(anteilObenfrei+anteilSpielfeldHoehe)*fensterHoehe;
    kompletterPlatzfuerSchrift.h=((1-(anteilObenfrei+anteilSpielfeldHoehe))*fensterHoehe);
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

    ausgabeFeldOben.x=0;
    ausgabeFeldOben.y=0;
    ausgabeFeldOben.h=zusatzFensterOben;
    ausgabeFeldOben.w=fensterBreite;

    //Figuren laden:
    char pfadWasser[]="grafiken/W.bmp";
    char pfadSchiff[]="grafiken/s.bmp";
    char pfadVersenkt[]="grafiken/V.bmp";
    char pfadTreffer[]="grafiken/X.bmp";

    SDL_Rect tmpRect;//fuegeBMP ein kopiert nur bei werten !=0 auf das Fenster
    tmpRect.x=-1; tmpRect.y=-1; tmpRect.h=-1; tmpRect.w=-1;

    einzelFeldWasser = fuegeBMPein(einzelFeldWasser,pfadWasser,tmpRect,false);
    einzelFeldSchiff = fuegeBMPein(einzelFeldSchiff,pfadSchiff,tmpRect,false);
    einzelFeldVersenkt = fuegeBMPein(einzelFeldVersenkt,pfadVersenkt,tmpRect,false);
    einzelFeldTreffer = fuegeBMPein(einzelFeldTreffer,pfadTreffer,tmpRect,false);

    int randKorrektur=2;
    einzelFeldWasser->h=anteilSpielfeldHoehe/10.*fensterHoehe-randKorrektur;
    einzelFeldWasser->w=anteilSpielfeldBreite/10.*fensterBreite-randKorrektur;
    einzelFeldSchiff->h=anteilSpielfeldHoehe/10.*fensterHoehe-randKorrektur;
    einzelFeldSchiff->w=anteilSpielfeldBreite/10.*fensterBreite-randKorrektur;
    einzelFeldVersenkt->h=anteilSpielfeldHoehe/10.*fensterHoehe-randKorrektur;
    einzelFeldVersenkt->w=anteilSpielfeldBreite/10.*fensterBreite-randKorrektur;
    einzelFeldTreffer->h=anteilSpielfeldHoehe/10.*fensterHoehe-randKorrektur;
    einzelFeldTreffer->w=anteilSpielfeldBreite/10.*fensterBreite-randKorrektur;
}

BO_GRA::~BO_GRA()
{
    // SDL korrekt herunterfahren
    if (hintergrundFenster!=NULL)
    {
            SDL_FreeSurface(hintergrundFenster);
    }
    if (einzelFeldWasser!=NULL)
    {
            SDL_FreeSurface(einzelFeldWasser);
    }
    if (einzelFeldSchiff!=NULL)
    {
            SDL_FreeSurface(einzelFeldSchiff);
    }
    if (einzelFeldVersenkt!=NULL)
    {
            SDL_FreeSurface(einzelFeldVersenkt);
    }
    if (einzelFeldTreffer!=NULL)
    {
            SDL_FreeSurface(einzelFeldTreffer);
    }
    if(bildFelder!=0)
    {
            SDL_FreeSurface(bildFelder);
    }
    SDL_Quit();

    delete[] gespeicherterChar;
    gespeicherterChar=0;

    if(letzteSpielfeldausgabe!=0)
    {
        delete[] letzteSpielfeldausgabe;
        letzteSpielfeldausgabe=0;
    }

}

void BO_GRA::textAusgeben(char const* tmpchar, bool tmpbool)
{
    if(neumachen)
    {
        aktuelleZeile=0;
        //SDL_FillRect(hintergrundFenster, &kompletterPlatzfuerSchrift, farbe_weiss);
        //SDL_UpdateRects(hintergrundFenster,1,&kompletterPlatzfuerSchrift);
        fuellemitFarbe(farbe_weiss,kompletterPlatzfuerSchrift,true);
    }
    else
    {
        //SDL_FillRect(hintergrundFenster, &(platzfuerSchrift[aktuelleZeile]), farbe_weiss);
        //SDL_UpdateRects(hintergrundFenster,1,&(platzfuerSchrift[aktuelleZeile]));
        fuellemitFarbe(farbe_weiss,platzfuerSchrift[aktuelleZeile],true);
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

    SDL_Surface* textoberflaeche=TTF_RenderText_Blended(schriftart,gespeicherterChar,textfarbe);

    kopiereSoweitmoeglichAufFenster(textoberflaeche,platzfuerSchrift[aktuelleZeile],true);
    /*SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&(platzfuerSchrift[aktuelleZeile]));
    SDL_UpdateRects(hintergrundFenster,1,&(platzfuerSchrift[aktuelleZeile]));*/

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
    else tmplaenge=(int)(log10((double)tmpzahl)+1);

    char *tmpchar=new char[tmplaenge+1];

    for(int i=(tmplaenge-1); i>=0; i--)
    {
        tmpchar[i]=(tmpzahl%10)+48;
        tmpzahl=tmpzahl/10;
    }
    tmpchar[tmplaenge]=0;

    this->textAusgeben(tmpchar, tmpbool);
    delete[] tmpchar;
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

        if(ereignis.type==SDL_KEYempfindlichAUF)
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
        else if(ereignis.type==SDL_QUIT)
        {
            schleifeBeenden = true;
            exit(-1);
        }
        //eingabe Feld frei machen
        //eingabenPlatz.w=100;
        //eingabenPlatz.h=60;
        //SDL_FillRect(hintergrundFenster, &eingabenPlatz, farbe_weiss);
        //SDL_UpdateRects(hintergrundFenster,1,&eingabenPlatz); unnötig
        fuellemitFarbe(farbe_weiss,eingabenPlatz,true);

        //neue Eingabe rendern und darstellen
        SDL_Surface* textoberflaeche=TTF_RenderText_Blended(schriftart,eingabenAusgabe,textfarbe);
        kopiereSoweitmoeglichAufFenster(textoberflaeche,eingabenPlatz,true);//wird hier manchmal falsch aufgerufen (bei JEDEM ereignis!!!)
        //SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&eingabenPlatz);
        //SDL_UpdateRects(hintergrundFenster,1,&eingabenPlatz);
        SDL_FreeSurface(textoberflaeche);
    }
    return tmprueckgabe;
}


bool BO_GRA::positionErfragen(POSITION* tmpposition, int tmpSpieler)
{
    bool schleifeBeenden = false;
    int tmpX,tmpY;

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
        //std::cout << "an event: " << std::clock() << " : " << (int)ereignis.type << std::endl;
        switch(ereignis.type)
        {
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            tmpX=ereignis.button.x;
            tmpY=ereignis.button.y;
            //wurde die maus seit dem letzten maustasten ereignis bewegt?
            if(ereignis.button.button == SDL_BUTTON_LEFT && mausBewegt(tmpX,tmpY)/*(betrag<double>(tmpX-altPixelX)>10 || betrag<double>(tmpY-altPixelY)>10)*/)
            {
                if(tmpposition->setzePositionX(pixelPositionzuFeldNrX(tmpX,tmpSpieler)) && tmpposition->setzePositionY(pixelPositionzuFeldNrY(tmpY)))
                {
                    schleifeBeenden=true;
                }
            }
            //altPixelX=tmpX;
            //altPixelY=tmpY;
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
}

void BO_GRA::warten(bool erneuern)
{

    //ausgabeFeldOben.w=fensterBreite;
    //SDL_FillRect(hintergrundFenster, &ausgabeFeldOben, farbe_weiss);
    //SDL_UpdateRects(hintergrundFenster,1,&ausgabeFeldOben);
    fuellemitFarbe(farbe_weiss,ausgabeFeldOben,true);

    SDL_Surface *textoberflaeche=0;
    textoberflaeche=TTF_RenderText_Blended(schriftart,"Beliebige Taste druecken...",textfarbe);
    //SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&ausgabeFeldOben);
    //SDL_UpdateRects(hintergrundFenster,1,&ausgabeFeldOben);
    kopiereSoweitmoeglichAufFenster(textoberflaeche,ausgabeFeldOben,true);
    SDL_FreeSurface(textoberflaeche);

    bool schleifeBeenden=false;
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
        if(ersterwartenaufruf)
        {
            if(ereignis.type == SDL_KEYUP)
            {
                SDL_KEYempfindlichAUF=SDL_KEYUP;
                schleifeBeenden=true;
                ersterwartenaufruf=false;
                //std::cout << "KEYUP" << std::endl;
            }
            else if(ereignis.type== SDL_KEYDOWN)
            {
                SDL_KEYempfindlichAUF=SDL_KEYDOWN;
                schleifeBeenden=true;
                ersterwartenaufruf=false;
                //std::cout << "KEYDOWN" << std::endl;
            }
        }
        else
        {
            if(ereignis.type==SDL_KEYempfindlichAUF)
            {
                schleifeBeenden=true;
            }
        }
        if(ereignis.type==SDL_MOUSEBUTTONDOWN)
        {
            schleifeBeenden=true;
        }
        else if(ereignis.type==SDL_QUIT)
        {
            schleifeBeenden = true;
            exit(-1);
        }
    }
    //SDL_FillRect(hintergrundFenster, &ausgabeFeldOben, farbe_weiss);
    //SDL_UpdateRects(hintergrundFenster,1,&ausgabeFeldOben);
    fuellemitFarbe(farbe_weiss,ausgabeFeldOben,true);

    if(erneuern) erneuereGraphischeOberflaeche(true);
}

void BO_GRA::begruessung()
{
    SDL_Rect mittenaufFenster[5];
    for(int i=0;i<5;i++)
    {
        mittenaufFenster[i].h=50;
        mittenaufFenster[i].w=300;
        mittenaufFenster[i].x=fensterBreite/2-2.5/2.*mittenaufFenster[i].w;
        mittenaufFenster[i].y=fensterHoehe/2-mittenaufFenster[i].h/2;
    }
    mittenaufFenster[0].y-=100;
    mittenaufFenster[1].y-=50;
    mittenaufFenster[2].y+=0;
    mittenaufFenster[3].y+=50;
    mittenaufFenster[4].y+=100;

    char const *begruessung[5];
    begruessung[0]="Willkommen zu einer Partie Schiffeversenken.";
    begruessung[1]="Da diese Partie an einem PC stattfindet,";
    begruessung[2]="ist es unumgaenglich fair zu spielen";
    begruessung[3]="und waehrend der Gegner seine Schiffe setzt wegzuschauen!";
    begruessung[4]="Viel Spass!";

    TTF_Font *begrSchriftart=TTF_OpenFont("grafiken/Arial_Black.ttf",24);//sollte zur Not sowohl in windows wie auch ubuntu (mscorefonts) verfügbar sein
    if (begrSchriftart==NULL)
    {
        std::cout << "Schrift konnte nicht geladen werden." << std::endl;
        std::cin.get();
        exit(-1);
    }

    SDL_Surface* textoberflaeche=0;

    for(int i=0; i<5;i++)
    {
        textoberflaeche=TTF_RenderText_Blended(begrSchriftart,begruessung[i],textfarbe);
        SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&mittenaufFenster[i]);
    }


    SDL_UpdateRects(hintergrundFenster,5,mittenaufFenster);
    SDL_FreeSurface(textoberflaeche);

    warten(true);
}

void BO_GRA::hinweis()
{
    if(!hinweisausgegeben)
    {
        hinweisausgegeben=true;
        SDL_Rect mittenaufFenster[3];
        for(int i=0;i<3;i++)
        {
            mittenaufFenster[i].h=50;
            mittenaufFenster[i].w=300;
            mittenaufFenster[i].x=fensterBreite/2-2.7/2.*mittenaufFenster[i].w;
            mittenaufFenster[i].y=fensterHoehe/2-mittenaufFenster[i].h/2;
        }
        mittenaufFenster[0].y-=50;
        mittenaufFenster[1].y+=0;
        mittenaufFenster[2].y+=50;

        char const *begruessung[3];
        begruessung[0]="Nun koennen die Schiffe einzeln gesetzt werden.";
        begruessung[1]="Das Terminal wird nach erfolgter Eingabe eines Spielers geloescht.";
        begruessung[2]="Bitte schaut weg, wenn euer Gegner seine Schiffe setzt!";

        TTF_Font *hinwSchriftart=TTF_OpenFont("grafiken/Arial_Black.ttf",24);//sollte zur Not sowohl in windows wie auch ubuntu (mscorefonts) verfügbar sein
        if (hinwSchriftart==NULL)
        {
            std::cout << "Schrift konnte nicht geladen werden." << std::endl;
            std::cin.get();
            exit(-1);
        }

        SDL_Surface* textoberflaeche;

        for(int i=0; i<3;i++)
        {
            textoberflaeche=TTF_RenderText_Blended(hinwSchriftart,begruessung[i],textfarbe);
            SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&mittenaufFenster[i]);
        }


        SDL_UpdateRects(hintergrundFenster,3,mittenaufFenster);
        SDL_FreeSurface(textoberflaeche);

        warten(true);
    }
}

void BO_GRA::konsoleLoeschen()
{
    //eingabenPlatz.w=100;
    //eingabenPlatz.h=60;
    //SDL_FillRect(hintergrundFenster, &eingabenPlatz, farbe_weiss);
    //SDL_UpdateRects(hintergrundFenster,1,&eingabenPlatz);
    fuellemitFarbe(farbe_weiss,eingabenPlatz,true);
}

void BO_GRA::spielfeldAusgabe(char* tmpFeldchar)
{
    if(strlen(tmpFeldchar)!=200)
    {
        std::cout << "Internes Problem, Program wird beendet" << std::endl;
        std::cin.get();
        exit(-2);
    }
    if(letzteSpielfeldausgabe==0)letzteSpielfeldausgabe = new char[201];
    kopiereArray<char>(tmpFeldchar,letzteSpielfeldausgabe,200);
	letzteSpielfeldausgabe[200]=0;

    SDL_Surface *einzelFeld;
    SDL_Rect position;
    POSITION index;
    position.x=0;
    position.y=0;
    index.setzePositionX(0);
    index.setzePositionY(0);
    bool rechts=false;
    for(int i=0; i<200; i++)
    {
        position.x=FeldNRBreiteinPixel(index.holeX(),rechts)+1;
        position.y=FeldNRHoeheinPixel(index.holeY())+1;

        //entsprechendes Bild einsetzen
        if(letzteSpielfeldausgabe[i]!='-')
        {
            switch(letzteSpielfeldausgabe[i])
            {
            case 's':
                einzelFeld=einzelFeldSchiff;
                break;
            case 'V':
                einzelFeld=einzelFeldVersenkt;
                break;
            case 'W':
                einzelFeld=einzelFeldWasser;
                break;
            case 'X':
                einzelFeld=einzelFeldTreffer;
                break;
            default:
                einzelFeld=einzelFeldWasser;
                break;
            }
            position.h=einzelFeld->h;
            position.w=einzelFeld->w;
            //SDL_BlitSurface(einzelFeld,0,hintergrundFenster,&position);
            kopiereSoweitmoeglichAufFenster(einzelFeld,position,true);
            einzelFeld=0;

            //SDL_UpdateRects(hintergrundFenster,1,&position);
        }
        //position auf Feld bestimmen
        if((i+1)%10==0)
        {
            //index.setzePositionX(0);
            rechts=(rechts+1)%2;
            if((i+1)%20==0)
            {
                //index.setzePositionX(0);
                index.inkrementiereY();
            }
        }
        /*else*/ index.inkrementiereX();//setzt automatisch auf 0 wenn x > 9
    }
}

//feldnr von 0 bis 9!
int BO_GRA::FeldNRBreiteinPixel(int feldnr, bool rechts)
{
    double feldgroesseB=anteilSpielfeldBreite/10.;

    if(rechts)
    {
        return (int)((2*anteilLinksfrei+anteilRechtsfrei+anteilSpielfeldBreite+feldnr*feldgroesseB)*fensterBreite);
    }
    return (int)((anteilLinksfrei+feldnr*feldgroesseB)*fensterBreite);
}

int BO_GRA::FeldNRHoeheinPixel(int feldnr)
{
    double feldgroesseH=anteilSpielfeldHoehe/10.;

    return (int)((anteilObenfrei+feldnr*feldgroesseH)*fensterHoehe);
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

    warten(false);
}

void BO_GRA::erneuereGraphischeOberflaeche(bool auchletzterStatus)
{
    // Fülle Zeichenfläche mit Farbe
    //SDL_FillRect(hintergrundFenster, 0, farbe_weiss);
    fuellemitFarbe(farbe_weiss,false);

    //bildFelder->h=BMP_platz.h;
    //bildFelder->w=BMP_platz.w;
    //kopiere Bild (auch surface) auf schon fertiges Fenster
    //SDL_BlitSurface(bildFelder,0,hintergrundFenster,&BMP_platz);
    kopiereSoweitmoeglichAufFenster(bildFelder,BMP_platz,false);

    if(letzteSpielfeldausgabe!=0 && auchletzterStatus) spielfeldAusgabe(letzteSpielfeldausgabe);
    aktuelleZeile=0;

    SDL_UpdateRect(hintergrundFenster,0,0,0,0);
}

void BO_GRA::erneuereGraphischeOberflaeche(bool, SDL_Rect tmpRect)
{
    //hier können natürlich noch positionen ausserhalb des eigentlichen bmp bereichs anfallen, SDL scheint das aber gut zu verwalten!
    //einzelne rechtecke erneuern, teil des spielfeldes neu ausgeben
    /*tmpRect.h=tmpRect.h+10;
    tmpRect.w=tmpRect.w+10;
    tmpRect.x=tmpRect.x-5;
    tmpRect.y=tmpRect.y-5;*/

    if(tmpRect.x<0)
    {
        tmpRect.w=tmpRect.w+tmpRect.x;
        tmpRect.x=0;
    }
    if(tmpRect.y<0)
    {
        tmpRect.h=tmpRect.h+tmpRect.y;
        tmpRect.y=0;
    }

    SDL_FillRect(hintergrundFenster, &tmpRect, farbe_weiss);
    //->eventuell aus dem Fenster herausragendes wird entfernt! -> tmpRect geändert!
    //hier ist es noetig dass eine Referenz,Pointer? übergeben wird, da sonst beim erneuern eines Teiles der ausserhalb des Fensters liegt das Programm abstürzt

    //kopieren des IM (sonst bei updaterects absturz) Fenster liegenden Bereichs, da tmpRect verkleinert wird wenn nicht der ganze Bereich im BMP-Feld liegt!
    //SDL_Rect tmpRect_sicherung = tmpRect;

    if(tmpRect.x+tmpRect.w>BMP_platz.x && tmpRect.y+tmpRect.h>BMP_platz.y && tmpRect.x<BMP_platz.x+BMP_platz.w && tmpRect.y<BMP_platz.y+BMP_platz.h)
    {
        SDL_Rect tmpRect_BMP;
        tmpRect_BMP.h=tmpRect.h;
        tmpRect_BMP.w=tmpRect.w;
        tmpRect_BMP.x=tmpRect.x-BMP_platz.x;
        tmpRect_BMP.y=tmpRect.y-BMP_platz.y;

        kopiereAusschnittAufFenster(bildFelder,tmpRect_BMP,tmpRect,true);
        aktuelleZeile=0;


        //bildFelder->h=BMP_platz.h;
        //bildFelder->w=BMP_platz.w;
        //kopiere Bild (auch surface) auf schon fertiges Fenster
        //SDL_BlitSurface(bildFelder,&tmpRect_BMP,hintergrundFenster,&tmpRect);
    }
    else SDL_UpdateRects(hintergrundFenster,1,&tmpRect);
    //tmpRect wurde erneut geändert!, eventuell aus dem BMP herausragendes wurde entfernt

    /*da jetzt sicherstellung dass alles aktualisiert wird -> unnötig
     *if(tmpRect.y<=BMP_platz.y)
    {
        std::cout << "erneuere Oben" << std::endl;
        SDL_Rect tmpOben;
        tmpOben.x=0;
        tmpOben.y=0;
        tmpOben.h=BMP_platz.y;
        tmpOben.w=fensterBreite;
        SDL_FillRect(hintergrundFenster, &tmpOben, farbe_weiss);
        SDL_UpdateRects(hintergrundFenster,1,&tmpOben);
    }
    if((tmpRect.y+tmpRect.h)>=BMP_platz.y+BMP_platz.h)
    {
        std::cout << "erneuere Unten" << std::endl;
        SDL_Rect tmpUnten;
        tmpUnten.x=0;
        tmpUnten.y=BMP_platz.y+BMP_platz.h;
        tmpUnten.h=fensterHoehe-(BMP_platz.y+BMP_platz.h);
        tmpUnten.w=fensterBreite;
        SDL_FillRect(hintergrundFenster, &tmpUnten, farbe_weiss);
        SDL_UpdateRects(hintergrundFenster,1,&tmpUnten);
    }*/

    //SDL_UpdateRects(hintergrundFenster,1,&tmpRect_sicherung);
}

void BO_GRA::ausgabeVersenkt()
{
	SDL_Rect mittenaufFenster;
    mittenaufFenster.h=150;
    mittenaufFenster.w=300;
    mittenaufFenster.x=fensterBreite/2-mittenaufFenster.w;
    mittenaufFenster.y=fensterHoehe/2-mittenaufFenster.h/2;

    char versenktChar[]="Schiff Versenkt!";

    SDL_Color farbe_dunkelrot;
    farbe_dunkelrot.r=200;
    farbe_dunkelrot.b=0;
    farbe_dunkelrot.g=0;

    TTF_Font *gewinnerSchriftart=TTF_OpenFont("grafiken/Arial_Black.ttf",36);//sollte zur Not sowohl in windows wie auch ubuntu (mscorefonts) verfügbar sein
    if (gewinnerSchriftart==NULL)
    {
        std::cout << "Schrift konnte nicht geladen werden." << std::endl;
        std::cin.get();
        exit(-1);
    }

    SDL_Surface* textoberflaeche=TTF_RenderText_Blended(gewinnerSchriftart,versenktChar,farbe_dunkelrot);
    SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&mittenaufFenster);
    SDL_UpdateRects(hintergrundFenster,1,&mittenaufFenster);
    SDL_FreeSurface(textoberflaeche);

    warten(true);
}

void BO_GRA::spieleranderReihe(int tmpSpieler, bool wiederholung)
{
    //ausgabeFeldOben.w=fensterBreite;
    //SDL_FillRect(hintergrundFenster, &ausgabeFeldOben, farbe_weiss);
    //SDL_UpdateRects(hintergrundFenster,1,&ausgabeFeldOben);
    fuellemitFarbe(farbe_weiss,ausgabeFeldOben,true);

    char tmpChar1[] = "Schuss von SPIELER 0 auf:";
    char tmpChar2[] = "SPIELER 0 bitte wiederholen:";
    char *tmpChar = new char[28+1];

    if(!wiederholung)
    {
        for(int i=0; i<25; i++)
        {
            tmpChar[i]=tmpChar1[i];
        }
        tmpChar[19]=tmpSpieler+1+48;
        tmpChar[25]=0;
    }
    else
    {
        for(int i=0; i<28; i++)
        {
            tmpChar[i]=tmpChar2[i];
        }
        tmpChar[8]=tmpSpieler+1+48;
        tmpChar[28]=0;
    }

    if(tmpSpieler==0) ausgabeFeldOben.x+=fensterBreite/2;
    SDL_Surface* textoberflaeche=TTF_RenderText_Blended(schriftart,tmpChar,textfarbe);
    //SDL_BlitSurface(textoberflaeche,0,hintergrundFenster,&ausgabeFeldOben);
    //SDL_UpdateRects(hintergrundFenster,1,&ausgabeFeldOben);
    kopiereSoweitmoeglichAufFenster(textoberflaeche,ausgabeFeldOben,true);
    SDL_FreeSurface(textoberflaeche);
    ausgabeFeldOben.x=0;
}

bool BO_GRA::nachfrageGesetzteSchiffe(char* tmpSpielfeld)
{
    if(strlen(tmpSpielfeld)!=200)
    {
        std::cout << "Interner Fehler, Programm wird beendet!" << std::endl;
        exit(-2);
    }
    else
    {
        if(letzteSpielfeldausgabe==0)letzteSpielfeldausgabe = new char[201];
        kopiereArray<char>(tmpSpielfeld,letzteSpielfeldausgabe,200);
        letzteSpielfeldausgabe[200]=0;
    }
    erneuereGraphischeOberflaeche(true);

    textAusgeben("Wollen sie die Orte ihrer Schiffe korrigieren? (j,n)",true);
    bool korrigieren=false;
    bool schleifeBeenden=false;
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
        if(ereignis.type==SDL_KEYDOWN || ereignis.type==SDL_KEYUP)
        {
            if(ereignis.key.keysym.sym==SDLK_j)
            {
                korrigieren=true;
                schleifeBeenden=true;
            }
            else if(ereignis.key.keysym.sym==SDLK_n)
            {
                //korrigieren=false;
                schleifeBeenden=true;
            }
        }
        else if(ereignis.type==SDL_QUIT)
        {
            schleifeBeenden = true;
            exit(-1);
        }
    }
    erneuereGraphischeOberflaeche(false);
    return korrigieren;
}

bool BO_GRA::schiffsetzen(int tmpSpieler, int tmpLaenge, POSITION *tmpAnfang, POSITION *tmpEnde)
{
    SDL_Rect rectSchiffvertikal,rectSchiffhorizontal;
    rectSchiffvertikal=kompletterPlatzfuerSchrift;
    rectSchiffhorizontal=kompletterPlatzfuerSchrift;

    rectSchiffvertikal.x+=fensterBreite/3.;
    rectSchiffhorizontal.x+=fensterBreite*(1./3.+anteilSpielfeldBreite/10.);

    rectSchiffvertikal.h=(fensterHoehe*(anteilSpielfeldHoehe/10.)-1)*tmpLaenge;
    rectSchiffvertikal.w=fensterBreite*(anteilSpielfeldBreite/10.)-1;
    rectSchiffhorizontal.h=fensterHoehe*(anteilSpielfeldHoehe/10.)-1;
    rectSchiffhorizontal.w=(fensterBreite*(anteilSpielfeldBreite/10.)-1)*tmpLaenge;

    char tmpChar_pfad[] = "grafiken/schiffe/";
    char tmpChar_horizontal[] = "horizontal.bmp";
    char tmpChar_vertikal[] = "vertikal.bmp";
    char tmpChar_laenge = tmpLaenge+48;

    char tmpChar_pfad_vertikal[30+1];
    char tmpChar_pfad_horizontal[32+1];

    for(int i=0; i<17; i++)
    {
        tmpChar_pfad_horizontal[i]=tmpChar_pfad[i];
        tmpChar_pfad_vertikal[i]=tmpChar_pfad[i];
    }
    tmpChar_pfad_horizontal[17]=tmpChar_laenge;
    tmpChar_pfad_vertikal[17]=tmpChar_laenge;
    for(int i=18; i<32; i++)
    {
        tmpChar_pfad_horizontal[i]=tmpChar_horizontal[i-18];
        if(i<30)tmpChar_pfad_vertikal[i]=tmpChar_vertikal[i-18];
    }
    tmpChar_pfad_horizontal[32]=0;
    tmpChar_pfad_vertikal[30]=0;

    SDL_Surface* BMPschiffhorizontal=0;
    SDL_Surface* BMPschiffvertikal=0;

    /*Uint32 farbe_blau = SDL_MapRGB(hintergrundFenster->format, 0, 0, 255);
    Uint32 farbe_gruen = SDL_MapRGB(hintergrundFenster->format, 0, 255, 0);
    SDL_FillRect(hintergrundFenster, &rectSchiffvertikal, farbe_blau);
    SDL_UpdateRects(hintergrundFenster,1,&rectSchiffvertikal);
    SDL_FillRect(hintergrundFenster, &rectSchiffhorizontal, farbe_gruen);
    SDL_UpdateRects(hintergrundFenster,1,&rectSchiffhorizontal);*/

    bool grosseSchleifeBeenden=false;
    bool schleifeBeenden = false;
    bool aufSchiffhorizontal,aufSchiffvertikal;
    bool anfangrichtig,enderichtig;
    int tmpX,tmpY;

    while(!grosseSchleifeBeenden)
    {
        schleifeBeenden=false;
        BMPschiffhorizontal = fuegeBMPein(BMPschiffhorizontal,tmpChar_pfad_horizontal,rectSchiffhorizontal,true);
        BMPschiffvertikal = fuegeBMPein(BMPschiffvertikal,tmpChar_pfad_vertikal,rectSchiffvertikal,true);

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
            //std::cout << "an event: " << std::clock() << " : " << (int)ereignis.type << std::endl;
            switch(ereignis.type)
            {
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                tmpX=ereignis.button.x;
                tmpY=ereignis.button.y;
                //in methode schreiben
                aufSchiffhorizontal = (tmpX>=rectSchiffhorizontal.x && tmpX<=(rectSchiffhorizontal.x+rectSchiffhorizontal.w)) && (tmpY>=rectSchiffhorizontal.y && tmpY<=(rectSchiffhorizontal.y+rectSchiffhorizontal.h));
                aufSchiffvertikal = (tmpX>=rectSchiffvertikal.x && tmpX<=(rectSchiffvertikal.x+rectSchiffvertikal.w)) && (tmpY>=rectSchiffvertikal.y && tmpY<=(rectSchiffvertikal.y+rectSchiffvertikal.h));
                //wurde die maus seit dem letzten maustasten ereignis bewegt?
                if(ereignis.button.button == SDL_BUTTON_LEFT && mausBewegt(tmpX,tmpY)/*(betrag<double>(tmpX-altPixelX)>10 || betrag<double>(tmpY-altPixelY)>10)*/)
                {
                    //if(tmpposition->setzePositionX(pixelPositionzuFeldNrX(tmpX,tmpSpieler)) && tmpposition->setzePositionY(pixelPositionzuFeldNrY(tmpY)))
                    if(aufSchiffhorizontal)
                    {
                        //Schiffhorizontal
                        schleifeBeenden=true;
                        //std::cout << "horizontales Schiff" << std::endl;
                    }
                    else if(aufSchiffvertikal)
                    {
                        //Schiffvertikal
                        schleifeBeenden=true;
                        //std::cout << "vertikales Schiff" << std::endl;
                    }
                }
                //altPixelX=tmpX;
                //altPixelY=tmpY;
                break;
            case SDL_QUIT:
                schleifeBeenden = true;
                exit(-1);
                break;
            default:
                break;
            }
        }

        erneuereGraphischeOberflaeche(true,rectSchiffhorizontal);
        erneuereGraphischeOberflaeche(true,rectSchiffvertikal);

        schleifeBeenden=false;
        while(!schleifeBeenden)
        {
            if(0 == SDL_WaitEvent(&ereignis))
            {
                std::cerr << "Fehler beim Warten auf Benutzerinteraktion." << std::endl;
                schleifeBeenden = true;
                break;
            }
            switch(ereignis.type)
            {
            case SDL_MOUSEMOTION:
                if(aufSchiffhorizontal)
                {
                    erneuereGraphischeOberflaeche(true, rectSchiffhorizontal);
                    if(tmpLaenge%2!=0)
                    {
                        rectSchiffhorizontal.x = ereignis.motion.x-(rectSchiffhorizontal.w/2.);
                        rectSchiffhorizontal.y = ereignis.motion.y-(rectSchiffhorizontal.h/2.);
                    }
                    else if(tmpLaenge==4)
                    {
                        rectSchiffhorizontal.x = ereignis.motion.x-(rectSchiffhorizontal.w*(1./4.+1./8.));
                        rectSchiffhorizontal.y = ereignis.motion.y-(rectSchiffhorizontal.h/2.);
                    }
                    else
                    {
                        rectSchiffhorizontal.x = ereignis.motion.x-(rectSchiffhorizontal.w*(1./4.));
                        rectSchiffhorizontal.y = ereignis.motion.y-(rectSchiffhorizontal.h/2.);
                    }
                    kopiereSoweitmoeglichAufFenster(BMPschiffhorizontal,rectSchiffhorizontal,true);
                }
                else
                {
                    erneuereGraphischeOberflaeche(true, rectSchiffvertikal);
                    if(tmpLaenge%2!=0)
                    {
                        rectSchiffvertikal.x = ereignis.motion.x-(rectSchiffvertikal.w/2.);
                        rectSchiffvertikal.y = ereignis.motion.y-(rectSchiffvertikal.h/2.);
                    }
                    else if(tmpLaenge==4)
                    {
                        rectSchiffvertikal.x = ereignis.motion.x-(rectSchiffvertikal.w/2.);
                        rectSchiffvertikal.y = ereignis.motion.y-(rectSchiffvertikal.h*(1./4.+1./8.));
                    }
                    else
                    {
                        rectSchiffvertikal.x = ereignis.motion.x-(rectSchiffvertikal.w/2.);
                        rectSchiffvertikal.y = ereignis.motion.y-(rectSchiffvertikal.h*(1./4.));
                    }
                    kopiereSoweitmoeglichAufFenster(BMPschiffvertikal,rectSchiffvertikal,true);
                }
                break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                tmpX=ereignis.button.x;
                tmpY=ereignis.button.y;
                //wurde die maus seit dem letzten maustasten ereignis bewegt?
                if(ereignis.button.button == SDL_BUTTON_LEFT && (betrag<double>(tmpX-altPixelX)>10 || betrag<double>(tmpY-altPixelY)>10))
                {
                    //std::cout << "X: " << pixelPositionzuFeldNrX(tmpX,tmpSpieler) << " Y: " << pixelPositionzuFeldNrY(tmpY) << std::endl;
                    if(tmpAnfang->setzePositionX(pixelPositionzuFeldNrX(tmpX,tmpSpieler)) && tmpAnfang->setzePositionY(pixelPositionzuFeldNrY(tmpY)))
                    {
                        //zumindest die Mausposition passt
                        if(tmpLaenge%2!=0)
                        {
                            if(aufSchiffhorizontal)
                            {
                                anfangrichtig = (tmpAnfang->setzePositionX( (pixelPositionzuFeldNrX(tmpX,tmpSpieler)-(int)(tmpLaenge/2)) ) && tmpAnfang->setzePositionY( pixelPositionzuFeldNrY(tmpY)));
                                enderichtig = ( tmpEnde->setzePositionX((pixelPositionzuFeldNrX(tmpX,tmpSpieler)+(int)(tmpLaenge/2))) && tmpEnde->setzePositionY( pixelPositionzuFeldNrY(tmpY)) );
                                if( anfangrichtig && enderichtig )
                                {
                                    schleifeBeenden=true;
                                    grosseSchleifeBeenden=true;
                                }
                            }
                            else //aufSchiffvertikal
                            {
                                anfangrichtig = (tmpAnfang->setzePositionX( (pixelPositionzuFeldNrX(tmpX,tmpSpieler)) ) && tmpAnfang->setzePositionY( pixelPositionzuFeldNrY(tmpY)-(int)(tmpLaenge/2)));
                                enderichtig = ( tmpEnde->setzePositionX((pixelPositionzuFeldNrX(tmpX,tmpSpieler))) && tmpEnde->setzePositionY( pixelPositionzuFeldNrY(tmpY)+(int)(tmpLaenge/2)) );
                                if(anfangrichtig && enderichtig)
                                {
                                    schleifeBeenden=true;
                                    grosseSchleifeBeenden=true;
                                }
                            }
                        }
                        else if(tmpLaenge==4)
                        {
                            if(aufSchiffhorizontal)
                            {
                                anfangrichtig = (tmpAnfang->setzePositionX( (pixelPositionzuFeldNrX(tmpX,tmpSpieler)-1) ) && tmpAnfang->setzePositionY( pixelPositionzuFeldNrY(tmpY)));
                                enderichtig = ( tmpEnde->setzePositionX((pixelPositionzuFeldNrX(tmpX,tmpSpieler)+2)) && tmpEnde->setzePositionY( pixelPositionzuFeldNrY(tmpY)) );
                                if( anfangrichtig && enderichtig )
                                {
                                    schleifeBeenden=true;
                                    grosseSchleifeBeenden=true;
                                }
                            }
                            else //aufSchiffvertikal
                            {
                                anfangrichtig = (tmpAnfang->setzePositionX( (pixelPositionzuFeldNrX(tmpX,tmpSpieler)) ) && tmpAnfang->setzePositionY( pixelPositionzuFeldNrY(tmpY)-2));
                                enderichtig = ( tmpEnde->setzePositionX((pixelPositionzuFeldNrX(tmpX,tmpSpieler))) && tmpEnde->setzePositionY( pixelPositionzuFeldNrY(tmpY)+1) );
                                if(anfangrichtig && enderichtig)
                                {
                                    schleifeBeenden=true;
                                    grosseSchleifeBeenden=true;
                                }
                            }
                        }
                        else if(tmpLaenge==2)
                        {
                            if(aufSchiffhorizontal)
                            {
                                anfangrichtig = (tmpAnfang->setzePositionX( (pixelPositionzuFeldNrX(tmpX,tmpSpieler)) ) && tmpAnfang->setzePositionY( pixelPositionzuFeldNrY(tmpY)));
                                enderichtig = ( tmpEnde->setzePositionX((pixelPositionzuFeldNrX(tmpX,tmpSpieler)+1)) && tmpEnde->setzePositionY( pixelPositionzuFeldNrY(tmpY)) );
                                if( anfangrichtig && enderichtig )
                                {
                                    schleifeBeenden=true;
                                    grosseSchleifeBeenden=true;
                                }
                            }
                            else //aufSchiffvertikal
                            {
                                anfangrichtig = (tmpAnfang->setzePositionX( (pixelPositionzuFeldNrX(tmpX,tmpSpieler)) ) && tmpAnfang->setzePositionY( pixelPositionzuFeldNrY(tmpY)-1));
                                enderichtig = ( tmpEnde->setzePositionX((pixelPositionzuFeldNrX(tmpX,tmpSpieler))) && tmpEnde->setzePositionY( pixelPositionzuFeldNrY(tmpY)) );
                                if(anfangrichtig && enderichtig)
                                {
                                    schleifeBeenden=true;
                                    grosseSchleifeBeenden=true;
                                }
                            }
                        }
                        else return false;
                    }
                    else
                    {
                        schleifeBeenden=true;
                    }
                }
                altPixelX=tmpX;
                altPixelY=tmpY;
                break;
            case SDL_QUIT:
                schleifeBeenden = true;
                exit(0);
                break;
            default:
                break;
            } // switch(event.type)
        } // while(!schleifeBeenden)
        //das ganze nach oben -> nur einmal machen
        if(aufSchiffhorizontal)
        {
            erneuereGraphischeOberflaeche(true, rectSchiffhorizontal);
        }
        else if(aufSchiffvertikal)
        {
            erneuereGraphischeOberflaeche(true, rectSchiffvertikal);
        }
        if(!grosseSchleifeBeenden)
        {
            rectSchiffhorizontal=kompletterPlatzfuerSchrift;
            rectSchiffhorizontal.x+=fensterBreite*(1./3.+anteilSpielfeldBreite/10.);
            rectSchiffhorizontal.h=fensterHoehe*(anteilSpielfeldHoehe/10.)-1;
            rectSchiffhorizontal.w=(fensterBreite*(anteilSpielfeldBreite/10.)-1)*tmpLaenge;

            rectSchiffvertikal=kompletterPlatzfuerSchrift;
            rectSchiffvertikal.x+=fensterBreite/3.;
            rectSchiffvertikal.h=(fensterHoehe*(anteilSpielfeldHoehe/10.)-1)*tmpLaenge;
            rectSchiffvertikal.w=fensterBreite*(anteilSpielfeldBreite/10.)-1;

            kopiereSoweitmoeglichAufFenster(BMPschiffhorizontal,rectSchiffhorizontal,true);
            kopiereSoweitmoeglichAufFenster(BMPschiffvertikal,rectSchiffvertikal,true);
        }
        //erneuern der schiffpositionen!
    }//while(!grosseSchleifeBeenden)

    //warten(false);

    //std::cout << "Anfang x: " << tmpAnfang->holeX() << " y: " << tmpAnfang->holeY() << " Ende x: " << tmpEnde->holeX() << " y: " << tmpEnde->holeY() << std::endl;
    return true;
}

void BO_GRA::fuegeBMPein(char* tmpPfad, SDL_Rect tmpPosition, bool erneuern)
{
    SDL_Surface *tmpBMP = SDL_LoadBMP(tmpPfad);
    if (tmpBMP==0)
    {
            std::cout << "Grafik in " << tmpPfad << " nicht verfuegbar." << std::endl;
            std::cin.get();
            exit(-1);
    }

    tmpBMP->w=tmpPosition.w;
    tmpBMP->h=tmpPosition.h;

    SDL_BlitSurface(tmpBMP,0,hintergrundFenster,&tmpPosition);

    if(erneuern) SDL_UpdateRects(hintergrundFenster,1,&tmpPosition);

    if(tmpBMP!=0)
    {
            SDL_FreeSurface(tmpBMP);
    }
}

void BO_GRA::fuegeBMPein(char const* tmpPfad, SDL_Rect tmpPosition, bool erneuern)
{
    SDL_Surface *tmpBMP = SDL_LoadBMP(tmpPfad);
    if (tmpBMP==0)
    {
            std::cout << "Grafik in " << tmpPfad << " nicht verfuegbar." << std::endl;
            std::cin.get();
            exit(-1);
    }

    tmpBMP->w=tmpPosition.w;
    tmpBMP->h=tmpPosition.h;

    SDL_BlitSurface(tmpBMP,0,hintergrundFenster,&tmpPosition);

    if(erneuern) SDL_UpdateRects(hintergrundFenster,1,&tmpPosition);

    if(tmpBMP!=0)
    {
            SDL_FreeSurface(tmpBMP);
    }
}

SDL_Surface* BO_GRA::fuegeBMPein(SDL_Surface* zurueckzugebendesBild, char* tmpPfad, SDL_Rect tmpPosition, bool erneuern)
{
    zurueckzugebendesBild = SDL_LoadBMP(tmpPfad);
    if (zurueckzugebendesBild==0)
    {
        std::cout << "Grafik in " << tmpPfad << " nicht verfuegbar." << std::endl;
        std::cin.get();
        exit(-1);
    }

    if(tmpPosition.x>=0)
    {
        zurueckzugebendesBild->w=tmpPosition.w;
        zurueckzugebendesBild->h=tmpPosition.h;

        SDL_BlitSurface(zurueckzugebendesBild,0,hintergrundFenster,&tmpPosition);

        if(erneuern) SDL_UpdateRects(hintergrundFenster,1,&tmpPosition);
    }
    return zurueckzugebendesBild;
}

SDL_Surface* BO_GRA::fuegeBMPein(SDL_Surface* zurueckzugebendesBild, char const* tmpPfad, SDL_Rect tmpPosition, bool erneuern)
{
    zurueckzugebendesBild = SDL_LoadBMP(tmpPfad);
    if (zurueckzugebendesBild==0)
    {
        std::cout << "Grafik in " << tmpPfad << " nicht verfuegbar." << std::endl;
        std::cin.get();
        exit(-1);
    }

    if(tmpPosition.x>=0)
    {
        zurueckzugebendesBild->w=tmpPosition.w;
        zurueckzugebendesBild->h=tmpPosition.h;

        SDL_BlitSurface(zurueckzugebendesBild,0,hintergrundFenster,&tmpPosition);

        if(erneuern) SDL_UpdateRects(hintergrundFenster,1,&tmpPosition);
    }
    return zurueckzugebendesBild;
}

void BO_GRA::kopiereSoweitmoeglichAufFenster(SDL_Surface* tmpzukopieren,SDL_Rect tmpPosition,bool teilerneuern)
{
    if(tmpzukopieren!=0)
    {
        if(tmpzukopieren->w >= tmpPosition.w)
        {
            tmpzukopieren->w=tmpPosition.w;
        }
        else
        {
            tmpPosition.w = tmpzukopieren->w;
        }
        if(tmpzukopieren->h >= tmpPosition.h)
        {
            tmpzukopieren->h=tmpPosition.h;
        }
        else
        {
            tmpPosition.h = tmpzukopieren->h;
        }

        SDL_BlitSurface(tmpzukopieren,0,hintergrundFenster,&tmpPosition);//falls tmpPosition nicht im Fenster wirds entsprechend verkleinert -> damit kein Absturz in UpdateRects!
        if(teilerneuern) SDL_UpdateRects(hintergrundFenster,1,&tmpPosition);
    }
}

void BO_GRA::kopiereAusschnittAufFenster(SDL_Surface* tmpzukopieren,SDL_Rect tmpPositionVon,SDL_Rect tmpPositionNach,bool teilerneuern)
{
    SDL_Rect tmpPositionNach_sicherung=tmpPositionNach;
    SDL_BlitSurface(tmpzukopieren,&tmpPositionVon,hintergrundFenster,&tmpPositionNach);
    if(teilerneuern) SDL_UpdateRects(hintergrundFenster,1,&tmpPositionNach_sicherung);
}

TTF_Font* BO_GRA::ladeSchriftart(int groesse, TTF_Font* zurueckzugebenderFont)
{
    zurueckzugebenderFont = TTF_OpenFont("grafiken/Arial_Black.ttf",groesse);//sollte zur Not sowohl in windows wie auch ubuntu (mscorefonts) verfügbar sein
    if (zurueckzugebenderFont==NULL)
    {
        std::cout << "Schrift konnte nicht geladen werden." << std::endl;
        std::cin.get();
        exit(-1);
    }
    return zurueckzugebenderFont;
}

void BO_GRA::fuellemitFarbe(Uint32 farbe, SDL_Rect ort, bool zeichne)
{
    SDL_FillRect(hintergrundFenster, &ort, farbe);
    if(zeichne) SDL_UpdateRects(hintergrundFenster,1,&ort);
}

void BO_GRA::fuellemitFarbe(Uint32 farbe, bool zeichne)
{
    SDL_FillRect(hintergrundFenster, 0, farbe);
    if(zeichne) SDL_Flip(hintergrundFenster);
}

bool BO_GRA::mausBewegt(int x_neu, int y_neu)
{
    if(betrag<double>(x_neu-altPixelX)>5 || betrag<double>(y_neu-altPixelY)>5)
    {
        altPixelX=x_neu;
        altPixelY=y_neu;
        return true;
    }
    else return false;

}

