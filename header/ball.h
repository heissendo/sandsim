#ifndef BALL_H
#define BALL_H
#include "coordinates.h"
#include <QPainter>
#include <random>
#include <unordered_set>

class Ball
{
    public:
        Ball(coordinates cell);
        void        draw(QPainter& painter) const;
        QRectF      getRect() const;
        void        move(const std::unordered_set<coordinates>& occupied,
                         int gridWidth, int gridHeight, std::mt19937& rng);
        coordinates getCell() const;
        bool        isSettled() const;

    private:
        bool isFree(const std::unordered_set<coordinates>& occupied,
                    coordinates c, int gridWidth, int gridHeight) const;

        coordinates cell;
        bool        settled = false;
};

#endif // BALL_H
