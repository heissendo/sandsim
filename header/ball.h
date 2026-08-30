#ifndef BALL_H
#define BALL_H
#include <QPainter>
#include <stdlib.h>
#include <time.h>

class Ball
{
    public:
        Ball(int x, int y, int radius, int speedx, int speedy, int windowWidth,
             int windowHeight);
        void   draw(QPainter& painter) const;
        QRectF getRect() const;
        void   move();
        bool   hitWall();
        bool   hitBottom();

    private:
        int  x, y, radius, speedx, speedy, windowWidth, windowHeight;
        bool dirLeft = true;
};

#endif // BALL_H
