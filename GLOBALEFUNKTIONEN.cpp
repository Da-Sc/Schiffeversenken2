#include "GLOBALEFUNKTIONEN.h"

int buchstabeZuArrayposition(char buchst)
{
	int tmp=0;
	tmp = 9-(buchst-97);
	return tmp;
}

/*
int betrag(int zahl)
{
	if(zahl >= 0) return zahl;
	return zahl*(-1);
}*/

int kleineres(int a, int b)
{
	if(a<=b) return a;
	return b;
}
//zu Template!!!
int potenz(int x, int Potenz)
{
    if(Potenz==0) return 1;
    return x*potenz(x,--Potenz);
}
