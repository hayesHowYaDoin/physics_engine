#ifndef DOMAIN_COORDINATES_HPP_
#define DOMAIN_COORDINATES_HPP_

#include "domain/concepts.hpp"
#include <units.h>

namespace domain
{

    template<LengthUnit Length>
    struct Coordinates2D
    {
        LengthUnit x;
        LengthUnit y;
    };

} // namespace domain

#endif // DOMAIN_COORDINATES_HPP_