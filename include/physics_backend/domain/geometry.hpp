#ifndef PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP
#define PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP

#include <cmath>

#include "physics_backend/domain/vector.hpp"
#include "physics_backend/units.hpp"

namespace physics::domain
{

template <units::IsLengthUnit Length>
[[nodiscard]] constexpr
auto distance(PositionVector2D<Length> const& a, PositionVector2D<Length> const& b)
{
    auto difference {b - a};
    return difference.template getMagnitude<Length>();
}

} // namespace physics::domain

#endif // PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP
