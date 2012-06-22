#ifndef BO_VERWALTUNG_H
#define BO_VERWALTUNG_H

#include "BO.h"
#include "BO_KOM.h"
#include "BO_GRA.h"
//Singleton: damit genau eine Instanz von BO_VERWALTUNG existiert: http://www.oop-trainer.de/Themen/Singleton.html
//benutzen mit: BO_VERWALTUNG::holeInstanz()->

class BO_VERWALTUNG
{
public:
    static BO* holeInstanz();
    static void setzeModus(int);
private:
    BO_VERWALTUNG();
    static BO *BOinstanz;
    static BO_VERWALTUNG *VERWinstanz;
    int modus;
    bool modus_gesetzt;
};

#endif // BO_VERWALTUNG_H
