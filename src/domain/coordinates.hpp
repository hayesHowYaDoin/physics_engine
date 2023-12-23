#ifndef DOMAIN_COORDINATES_HPP_
#define DOMAIN_COORDINATES_HPP_

#include "domain/concepts.hpp"
#include <units.h>

namespace domain
{

    template <LengthUnit Length>
    struct Coordinate2D
    {
        Length const x;
        Length const y;

        constexpr Coordinate2D operator+(const Coordinate2D& rhs) const
        {
            return Coordinate2D {x + rhs.x, y + rhs.y};
        }

        constexpr Coordinate2D operator-(const Coordinate2D& rhs) const
        {
            return Coordinate2D {x - rhs.x, y - rhs.y};
        }

    };

} // namespace domain

#endif // DOMAIN_COORDINATES_HPP_