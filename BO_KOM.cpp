#ifdef __unix__
  #define KONSOLELOESCHEN "clear"
#elif _WIN32
  #define KONSOLELOESCHEN "cls"
#else
  #define KONSOLELOESCHEN "cls"
#endif


#include "BO_KOM.h"
#include <cstring>

BO_KOM::BO_KOM()
{
    //ctor
    zustand=true;
    hinweisausgegeben=false;
}

BO_KOM::~BO_KOM()
{
    //dtor
}
/*
BO_KOM *BO_KOM::instanz=NULL;

BO_KOM* BO_KOM::holeInstanz()
{
    if(instanz == NULL)//überprüft ob einer Instanz schon angelegt wurde
      instanz=new BO_KOM();

    return instanz;
}*/

void BO_KOM::textAusgeben(char* text)
{
    std::cout << text << std::flush;
}

void BO_KOM::textAusgeben(char* text, bool)
{
    textAusgeben(text);
}

void BO_KOM::zahlAusgeben(int zahl)
{
    std::cout << zahl << std::flush;
}

void BO_KOM::zahlAusgeben(int zahl, bool)
{
    zahlAusgeben(zahl);
}

int BO_KOM::intErfragen()
{
    int tmp=0;
    std::cin >> tmp;

    while(std::cin.bad() || std::cin.fail())
    {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            tmp=0;
            textAusgeben("Falsche Eingabe, bitte Wiederholen: ");
            std::cin >> tmp;
            zustand=false;
	}
	zustand=true;
	std::cout << std::endl;

    return tmp;
}

bool BO_KOM::positionErfragen(POSITION* position)
{
        char tmpc[4];
        for(int i=0;i<4;i++)tmpc[i]=0;
        zustand=true;

        std::cin >> std::setw(4) >> tmpc;

        //überprüfen auf cin Fehler
        if(std::cin.bad() || std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            zustand=false;
            return false;
        }

        //überprüfen ob zahlen oder buchstaben a-j eingegeben wurden
        for(int i=0; i<2; i++)
        {
                if( tmpc[i]<49 || (tmpc[i]>57 && tmpc[i]<65) || (tmpc[i]>74 && tmpc[i]<97) || tmpc[i]>107 )
                {
                        std::cin.ignore(100, '\n');
                        zustand=false;
                        return false;
                }
        }

        //erstes Zeichen (Buchstabe) A -> 9 ... J -> 0
        if(tmpc[0]<97) tmpc[0]+=32;
        if( !(tmpc[0]>96 && tmpc[0]<107) || !(position->setzePositionY(buchstabeZuArrayposition(tmpc[0]))) ) return false;

        //zweites und drittes Zeichen
        if(tmpc[2]==0)
        {
                if(tmpc[1]>57 || tmpc[1]<49 || !(position->setzePositionX((int)((tmpc[1]-49)))) ) return false;
        }
        else
        {
                if(tmpc[1]!=49 || tmpc[2]!=48) return false;
                position->setzePositionX(9);
        }

        return true;
}

void BO_KOM::begruessung()
{
    std::cout << "Willkommen zu einer Partie Schiffeversenken." << std::endl;
    std::cout << "Da diese Partie an einem PC stattfindet, ist es unumgänglich fair zu spielen und während der Gegner seine Schiffe setzt wegzuschauen!" << std::endl;
    std::cout << "Viel Spaß" << std:: endl;
}

void BO_KOM::hinweis()
{
    if(!hinweisausgegeben)
    {
        hinweisausgegeben=true;
        std::cout << std::endl << "Nun können die Schiffe einzeln gesetzt werden. Das Terminal wird nach erfolgter Eingabe eines Spielers gelöscht." << std::endl;
        std::cout << "Bitte schaut weg, wenn euer Gegner seine Schiffe setzt!" << std::endl << std::endl;
    }
}

void BO_KOM::konsoleLoeschen()
{
    system(KONSOLELOESCHEN);
}

void BO_KOM::spielfeldAusgabe(char* grundlageninfos)
{

    if(std::strlen(grundlageninfos)!=200) return;//strln durch abschliessendes 0 bestimmt!!!

    char auszugebendesSpielfeld[750];
    for(int i=0; i<750; i++)
    {
        auszugebendesSpielfeld[i]=0;
    }

    int tmpzaehler=0;
    int buchstabenzaehler=0;
    char spielerchar[37]={'S','p','i','e','l','e','r',' ','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S','p','i','e','l','e','r',' ','2','\n'};
    char zahlen[52]={' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','7',' ','8',' ','9',' ','1','0',' ',' ',' ',' ',' ',' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','7',' ','8',' ','9',' ','1','0','\n','A',' '};

    for(int i=0; i<37; i++)
    {
        auszugebendesSpielfeld[tmpzaehler]=spielerchar[i];
        tmpzaehler++;
    }
    for(int i=0; i<52; i++)
    {
        auszugebendesSpielfeld[tmpzaehler]=zahlen[i];
        tmpzaehler++;
    }

    for(int i=0; i<200; i++)
    {
        auszugebendesSpielfeld[tmpzaehler]=grundlageninfos[i];
        tmpzaehler++;
        auszugebendesSpielfeld[tmpzaehler]=' ';
        tmpzaehler++;
        if((i+1)%10==0)
        {
            if((i+1)%20==0)
            {
                auszugebendesSpielfeld[tmpzaehler]='\n';
                tmpzaehler++;
                if(i<199)
                {
                    auszugebendesSpielfeld[tmpzaehler]=65+buchstabenzaehler;
                    tmpzaehler++;
                    auszugebendesSpielfeld[tmpzaehler]=' ';
                    tmpzaehler++;
                }

            }
            else
            {
                for(int j=0; j<5; j++)
                {
                    auszugebendesSpielfeld[tmpzaehler]=' ';
                    tmpzaehler++;
                }
                auszugebendesSpielfeld[tmpzaehler]=65+buchstabenzaehler;
                tmpzaehler++;
                buchstabenzaehler++;
                auszugebendesSpielfeld[tmpzaehler]=' ';
                tmpzaehler++;
            }
        }
    }

    textAusgeben(auszugebendesSpielfeld,true);
}
