#include "ball.h"

#include <cstdlib>
#include <iostream>

Ball::Ball(int x, int y, int radius, int speedx, int speedy, int windowWidth,
           int windowHeight)
    : x(x), y(y), radius(radius), speedx(speedx), speedy(speedy),
      windowWidth(windowWidth), windowHeight(windowHeight)
{
    srand(time(NULL));
}

void Ball::draw(QPainter& painter) const
{
    painter.setBrush((Qt::red));
    painter.drawRect(getRect());
}

QRectF Ball::getRect() const
{
    return QRectF(x, y, radius, radius);
}

void Ball::move()
{
    if (hitBottom())
    {
        return;
    }
    y += speedy;
}

bool Ball::hitBottom()
{
    return (y == windowHeight - radius) ? true : false;
}

bool Ball::hitWall()
{
    return (x <= 0 || x + radius >= windowWidth) ? true : false;
}
