#include "particle.h"
#include <iostream>

Particle::Particle(coordinates cell) : cell(cell)
{
}

void Particle::draw(QPainter& painter) const
{

    painter.setBrush((color));
    painter.drawRect(getRect());
}

QRectF Particle::getRect() const
{
    return QRectF(cell.x * cellSize, cell.y * cellSize, cellSize, cellSize);
}

bool Particle::isFree(const Grid& grid, coordinates c) const
{
    return grid.inBounds(c) && grid.getCell(c) == Cell::Empty;
}

bool Particle::isSolid(const Grid& grid, coordinates c) const
{
    return !grid.inBounds(c) || grid.getCell(c) == Cell::Settled;
}

void Particle::move(const Grid& grid, std::mt19937& rng)
{
    if (settled)
    {
        return;
    }

    const coordinates below{cell.x, cell.y + 1};
    const coordinates downLeft{cell.x - 1, cell.y + 1};
    const coordinates downRight{cell.x + 1, cell.y + 1};

    if (isFree(grid, below))
    {
        cell = below;
        return;
    }

    const bool leftFree  = isFree(grid, downLeft);
    const bool rightFree = isFree(grid, downRight);

    if (leftFree && rightFree)
    {
        cell = (rng() & 1) ? downLeft : downRight;
    }
    else if (leftFree)
    {
        cell = downLeft;
    }
    else if (rightFree)
    {
        cell = downRight;
    }
    else if (isSolid(grid, below) && isSolid(grid, downLeft) &&
             isSolid(grid, downRight))
    {
        settled = true;
    }
}

coordinates Particle::getCell() const
{
    return cell;
}

bool Particle::isSettled() const
{
    return settled;
}

void Particle::setColor(int particlesCount)
{
    int r = cell.x;
    (r > 255) ? r = 255 : r = cell.x;
    int g = cell.y;
    int b = particlesCount / 256;
    (b > 255) ? b = 255 : b = particlesCount / 256;

    color    = QColor(r, g, b);
    colorSet = true;
}

bool Particle::isColorSet() const
{
    return colorSet;
}
