#include "SPIEL.h"

/*
ARRAY aus POINTER richtig einsetzen:
KLASSE **test;
test = new KLASSE*[3]; -> default konstruktor muss vorhanden sein
for(i...) test[i]=new KLASSE(irgendwas, 123);
*/

//TESTS:
#include "BO_KOM.h"
#include <iostream>


int main()
{
    SPIEL *Testspiel = new SPIEL();
	

	//TESTS
	Testspiel->setzeSchiffe(0);
	/*int testar[2];

	if(BO_KOM::holeInstanz()->positionErfragen(testar, 2))
	{
		std::cout << testar[0] << " : " << testar[1] << std::endl;
	}*/
	//TESTSENDE

	system("pause");
    return 0;
}
