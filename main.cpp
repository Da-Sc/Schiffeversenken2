#include "SPIEL.h"
#include "BO_VERWALTUNG.h"

/*
ARRAY aus POINTER richtig einsetzen:
KLASSE **test;
test = new KLASSE*[3]; -> default konstruktor muss vorhanden sein? laut christian nicht...
for(i...) test[i]=new KLASSE(irgendwas, 123);
*/

//netzwerk eventuell über SDL_net: http://content.gpwiki.org/index.php/SDL:Tutorial:Using_SDL_net


int main(int argc, char* argv[])
{
    BO_VERWALTUNG::setzeModus(1);

    //TESTS
    //BO_GRA test();
    //TESTS

    SPIEL *EinPC_Spiel = new SPIEL();

    EinPC_Spiel->setzeSchiffe(0);
    EinPC_Spiel->setzeSchiffe(1);

        //EinPC_Spiel->zeigeSpielfelder(3);

    EinPC_Spiel->spielen(-1);

    delete EinPC_Spiel;
    return 0;
}
