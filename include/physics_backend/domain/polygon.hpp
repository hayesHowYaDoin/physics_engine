#ifndef PHYSICS_BACKEND_DOMAIN_POLYGON_HPP
#define PHYSICS_BACKEND_DOMAIN_POLYGON_HPP

#include <vector>

#include "physics_backend/units.hpp"

namespace physics::domain
{

    template <physics::units::IsLengthUnit Length>
    struct Polygon2D
    {
        std::vector<physics::units::Vector2D<Length>> vertices;
    };

}

#endif // PHYSICS_BACKEND_DOMAIN_POLYGON_HPP
