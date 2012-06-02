#ifndef SCHIFFLEIN_H
#define SCHIFFLEIN_H

#include "EINZELNES_FELD.h"
#include "SCHIFF.h"

class SCHIFF;

class SCHIFFLEIN : public EINZELNES_FELD
{
    public:
        SCHIFFLEIN();
        SCHIFFLEIN(SCHIFF*);
        virtual ~SCHIFFLEIN();
        virtual bool istSchiff();
        virtual bool istVersenkt();
        virtual bool beschossen();
    protected:
    private:
        SCHIFF* oberSchiff;
};

#endif // SCHIFFLEIN_H
