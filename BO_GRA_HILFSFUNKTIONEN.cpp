#include "BO_GRA.h"

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

//void BO_GRA::kopiereSoweitmoeglichAufFenster(SDL_Surface* tmpzukopieren,SDL_Rect tmpPosition,bool teilerneuern)
SDL_Surface BO_GRA::kopiereSoweitmoeglichAufFenster(SDL_Surface* tmpzukopieren,SDL_Surface* altesOberflaechenteil,SDL_Rect tmpPosition,bool teilerneuern)
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

        altesOberflaechenteil = erstelleLeereOberflaeche(tmpPosition.w,tmpPosition.h);
        SDL_BlitSurface(hintergrundFenster,&tmpPosition,altesOberflaechenteil,0);

        SDL_BlitSurface(tmpzukopieren,0,hintergrundFenster,&tmpPosition);//falls tmpPosition nicht im Fenster wirds entsprechend verkleinert -> damit kein Absturz in UpdateRects!
        if(teilerneuern) SDL_UpdateRects(hintergrundFenster,1,&tmpPosition);
    }
    else
    {
        altesOberflaechenteil = erstelleLeereOberflaeche(1,1);
        SDL_FillRect(altesOberflaechenteil, 0, farbe_weiss);
    }
    return *altesOberflaechenteil;
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

bool BO_GRA::rechteckgetroffen(SDL_Rect rechteck,int x,int y)
{
    return (x>=rechteck.x && x<=(rechteck.x+rechteck.w)) && (y>=rechteck.y && y<=(rechteck.y+rechteck.h));
}

SDL_Surface* BO_GRA::erstelleLeereOberflaeche(int breite,int hoehe)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& pixelFormat = *(hintergrundFenster->format);
  return SDL_CreateRGBSurface(SDL_SWSURFACE,breite,hoehe,pixelFormat.BitsPerPixel,pixelFormat.Rmask,pixelFormat.Gmask,pixelFormat.Bmask,pixelFormat.Amask );
}

void BO_GRA::ladePfade()
{
    char pfadWasser[]="grafiken/W.bmp";
    char pfadSchiff[]="grafiken/s.bmp";
    char pfadVersenkt[]="grafiken/V.bmp";
    char pfadTreffer[]="grafiken/X.bmp";
    char pfadTeile[36]="grafiken/schiffe/einzelFelder/x.bmp";
    pfadTeile[35]=0;

    SDL_Rect tmpRect;//fuegeBMP ein kopiert nur bei werten !=0 auf das Fenster
    tmpRect.x=-1; tmpRect.y=-1; tmpRect.h=-1; tmpRect.w=-1;

    einzelFeldWasser = fuegeBMPein(einzelFeldWasser,pfadWasser,tmpRect,false);
    einzelFeldSchiff = fuegeBMPein(einzelFeldSchiff,pfadSchiff,tmpRect,false);
    einzelFeldVersenkt = fuegeBMPein(einzelFeldVersenkt,pfadVersenkt,tmpRect,false);
    einzelFeldTreffer = fuegeBMPein(einzelFeldTreffer,pfadTreffer,tmpRect,false);

    int tmp=65;
    //waagrecht
    for(int i=0; i<28; i++)
    {
        if(i==14) tmp=97-14;
        pfadTeile[30]=char(tmp+i);
        einzelFeldSchiffteile[i] = fuegeBMPein(einzelFeldSchiffteile[i],pfadTeile,tmpRect,false);
    }
}
