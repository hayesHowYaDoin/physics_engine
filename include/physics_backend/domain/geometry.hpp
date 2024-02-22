#ifndef PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP
#define PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP

#include <cmath>

#include "physics_backend/domain/vector.hpp"
#include "physics_backend/units.hpp"

namespace physics::domain
{

template <units::IsLengthUnit Length>
[[nodiscard]] constexpr
Length distance(PositionVector2D<Length> const& a, PositionVector2D<Length> const& b)
{
    return std::hypot(a.x - b.x, a.y - b.y);
}

template <units::IsLengthUnit Length>
[[nodiscard]] constexpr
double slope(PositionVector2D<Length> const& a, PositionVector2D<Length> const& b)
{
    return (b.y - a.y) / (b.x - a.x);
}


} // namespace physics::domain

#endif // PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP
