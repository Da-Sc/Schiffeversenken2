#include "BO_KOM.h"

BO_KOM::BO_KOM()
{
    //ctor
    zustand=true;
}

BO_KOM::~BO_KOM()
{
    //dtor
}

BO_KOM *BO_KOM::instanz=NULL;

BO_KOM* BO_KOM::holeInstanz()
{
    if(instanz == NULL)//überprüft ob einer Instanz schon angelegt wurde
      instanz=new BO_KOM();

    return instanz;
}

void BO_KOM::textAusgeben(char* text)
{
    std::cout << text << std::flush;
}

void BO_KOM::textAusgeben(char* text, bool anAlle)
{
    textAusgeben(text);
}

void BO_KOM::zahlAusgeben(int zahl)
{
    std::cout << zahl << std::flush;
}

void BO_KOM::zahlAusgeben(int zahl, bool anAlle)
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
