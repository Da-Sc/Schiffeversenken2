#pragma once

int buchstabeZuArrayposition(char);//funktioniert nur für passende chars (klein a-j)
//int betrag(int);
int kleineres(int, int);
int potenz(int,int);

template <typename T>
T betrag(T zahl)
{
    if(zahl >= 0) return zahl;
    return zahl*(-1);
}

template <typename C>
void kopiereArray(C *arrayvon, C *arrayzu, int laenge)
{
    for(int i=0; i<laenge; i++) arrayzu[i]=arrayvon[i];
}
