#include "SPIEL.h"

/*
ARRAY aus POINTER richtig einsetzen:
KLASSE **test;
test = new KLASSE*[3]; -> default konstruktor muss vorhanden sein? laut christian nicht...
for(i...) test[i]=new KLASSE(irgendwas, 123);
*/

//TESTS:
#include "BO_KOM.h"
#include <iostream>


int main()
{
    SPIEL *EinPC_Spiel = new SPIEL();

        EinPC_Spiel->setzeSchiffe(0);
        EinPC_Spiel->setzeSchiffe(1);

        //EinPC_Spiel->zeigeSpielfelder(3);

        EinPC_Spiel->spielen(-1);

    return 0;
}
