#include "grid.h"

Grid::Grid(int width, int height)
    : gridWidth(width), gridHeight(height),
      cells(static_cast<std::size_t>(width * height), Cell::Empty)
{
}

int Grid::getWidth() const
{
    return gridWidth;
}

int Grid::getHeight() const
{
    return gridHeight;
}

Cell Grid::getCell(coordinates c) const
{
    return cells[static_cast<std::size_t>(c.y * gridWidth + c.x)];
}

void Grid::setCell(coordinates c, Cell state)
{
    cells[static_cast<std::size_t>(c.y * gridWidth + c.x)] = state;
}

bool Grid::inBounds(coordinates c) const
{
    return c.x >= 0 && c.x < gridWidth && c.y >= 0 && c.y < gridHeight;
}
