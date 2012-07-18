#ifndef POSITION_H
#define POSITION_H

class POSITION
{
public:
    POSITION();
    bool setzePositionX(int);
    bool setzePositionY(int);
    int holePosition(int);
    int holeX();
    int holeY();
    void inkrementiereX();
    void inkrementiereY();
private:
    int x;
    int y;
};

class ERWEITERTE_POSITION:public POSITION
{
public:
    ERWEITERTE_POSITION(int);
    ERWEITERTE_POSITION(ERWEITERTE_POSITION*);
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
