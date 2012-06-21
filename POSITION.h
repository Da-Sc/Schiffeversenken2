#ifndef POSITION_H
#define POSITION_H

class POSITION
{
public:
    POSITION();
    virtual bool setzePositionX(int);
    virtual bool setzePositionY(int);
    virtual int holePosition(int);
    virtual int holeX();
    virtual int holeY();
private:
    int x;
    int y;
};

class ERWEITERTE_POSITION:public POSITION
{
public:
    ERWEITERTE_POSITION(int);
    ~ERWEITERTE_POSITION();
    bool setzePositionX(int, int);
    bool setzePositionY(int, int);
    int holeX(int);
    int holeY(int);
    int holeLaenge();
private:
    int* x;
    int* y;
    int laenge;
};

#endif // POSITION_H
