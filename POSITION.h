#ifndef POSITION_H
#define POSITION_H

class POSITION
{
public:
    POSITION();
    bool setzePosition(int, int);
    bool setzePositionX(int);
    bool setzePositionY(int);
    int holePosition(int);
    int holeX();
    int holeY();
private:
    int x;
    int y;
};

#endif // POSITION_H
