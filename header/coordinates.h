#ifndef COORDINATES_H
#define COORDINATES_H
#include <cstddef>
#include <functional>

constexpr int cellSize = 5;

struct coordinates
{
        int  x;
        int  y;
        bool operator==(const coordinates& o) const
        {
            return x == o.x && y == o.y;
        }
};

template <> struct std::hash<coordinates>
{
        std::size_t operator()(const coordinates& c) const noexcept
        {
            return std::hash<unsigned long long>{}(
                (static_cast<unsigned long long>(static_cast<unsigned int>(c.x))
                 << 32) |
                static_cast<unsigned int>(c.y));
        }
};

#endif // COORDINATES_H
