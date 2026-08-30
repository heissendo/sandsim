#include "ball.h"

Ball::Ball(coordinates cell) : cell(cell)
{
}

void Ball::draw(QPainter& painter) const
{
    painter.setBrush((Qt::red));
    painter.drawRect(getRect());
}

QRectF Ball::getRect() const
{
    return QRectF(cell.x * cellSize, cell.y * cellSize, cellSize, cellSize);
}

bool Ball::isFree(const std::unordered_set<coordinates>& occupied,
                  coordinates c, int gridWidth, int gridHeight) const
{
    if (c.x < 0 || c.x >= gridWidth || c.y < 0 || c.y >= gridHeight)
    {
        return false;
    }

    return !occupied.contains(c);
}

void Ball::move(const std::unordered_set<coordinates>& occupied, int gridWidth,
                int gridHeight, std::mt19937& rng)
{
    const coordinates below{cell.x, cell.y + 1};
    const coordinates downLeft{cell.x - 1, cell.y + 1};
    const coordinates downRight{cell.x + 1, cell.y + 1};

    if (isFree(occupied, below, gridWidth, gridHeight))
    {
        cell    = below;
        settled = false;
        return;
    }

    const bool leftFree  = isFree(occupied, downLeft, gridWidth, gridHeight);
    const bool rightFree = isFree(occupied, downRight, gridWidth, gridHeight);

    if (leftFree && rightFree)
    {
        cell = std::bernoulli_distribution(0.5)(rng) ? downLeft : downRight;
    }
    else if (leftFree)
    {
        cell = downLeft;
    }
    else if (rightFree)
    {
        cell = downRight;
    }
    else
    {
        settled = true;
        return;
    }

    settled = false;
}

coordinates Ball::getCell() const
{
    return cell;
}

bool Ball::isSettled() const
{
    return settled;
}
