#ifndef GRID_H
#define GRID_H
#include "coordinates.h"
#include <cstdint>
#include <vector>

enum class Cell : std::uint8_t
{
    Empty   = 0,
    Falling = 1,
    Settled = 2
};

class Grid
{
    public:
        Grid(int width, int height);

        int  getWidth() const;
        int  getHeight() const;
        Cell getCell(coordinates c) const;
        void setCell(coordinates c, Cell state);
        bool inBounds(coordinates c) const;

    private:
        int               gridWidth;
        int               gridHeight;
        std::vector<Cell> cells;
};

#endif // GRID_H
