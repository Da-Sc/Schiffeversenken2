#include "SPIEL.h"

/*
ARRAY aus POINTER richtig einsetzen:
KLASSE **test;
test = new KLASSE*[3]; -> default konstruktor muss vorhanden sein
for(i...) test[i]=new KLASSE(irgendwas, 123);
*/


int main()
{
    SPIEL *Testspiel = new SPIEL();
    return 0;
}
