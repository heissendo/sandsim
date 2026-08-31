#ifndef BALL_H
#define BALL_H
#include "coordinates.h"
#include "grid.h"
#include <QPainter>
#include <random>

class Ball
{
    public:
        Ball(coordinates cell);
        void        draw(QPainter& painter) const;
        QRectF      getRect() const;
        void        move(const Grid& grid, std::mt19937& rng);
        coordinates getCell() const;
        bool        isSettled() const;
        bool        isColorSet() const;
        void        setColor(int particlesCount);

    private:
        bool isFree(const Grid& grid, coordinates c) const;
        bool isSolid(const Grid& grid, coordinates c) const;

        coordinates cell;
        bool        settled  = false;
        bool        colorSet = false;
        QColor      color    = Qt::red;
};

#endif // BALL_H
