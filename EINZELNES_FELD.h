#ifndef EINZELNES_FELD_H
#define EINZELNES_FELD_H


class EINZELNES_FELD
{
    public:
        EINZELNES_FELD();
        virtual ~EINZELNES_FELD();
        virtual bool beschossen();//Schuss auf das einzelnen Feld ruft das auf-> überprüft ob schon mal darauf geschossen wurde
        virtual bool istSchiff();
        virtual bool istVersenkt();
        bool istGetroffen();
        char holeTyp();
    protected:
        bool getroffen;
        char typ;
    private:
};

#endif // EINZELNES_FELD_H
