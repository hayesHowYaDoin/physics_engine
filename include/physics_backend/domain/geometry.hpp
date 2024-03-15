#ifndef PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP
#define PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP

#include <cmath>

#include "physics_backend/domain/vector.hpp"
#include "physics_backend/units.hpp"

namespace physics::domain
{

template <physics::units::IsLengthUnit Length>
[[nodiscard]] constexpr
auto distance(PositionVector2D<Length> const& a, PositionVector2D<Length> const& b)
{
    auto difference {b - a};
    return difference.template getMagnitude<Length>();
}

template <physics::units::IsVelocityUnit Velocity, physics::units::IsAngleUnit Angle>
[[nodiscard]] constexpr
auto reflect(VelocityVector2D<Velocity> const& velocity, Angle const& normalAngle)
{
    using namespace physics::units::literals;
    
    auto angleOfIncidence {velocity.template getAngle<Angle>()};
    Angle angleDifference {angleOfIncidence - normalAngle};

    Angle angleOfReflected {angleOfIncidence - 2 * angleDifference + 180.0_deg};

    return Vector2D::fromPolar(angleOfReflected, velocity.template getMagnitude<Velocity>());
}

template <template <typename> class Vector, physics::units::IsMagnitudeUnit Magnitude>
[[nodiscard]] constexpr
auto normalize(Vector<Magnitude> const& vector)
{
    auto magnitude {vector.template getMagnitude<Magnitude>() / Magnitude(1.0f)};
    Magnitude x {vector.template getX<Magnitude>() / magnitude};
    Magnitude y {vector.template getY<Magnitude>() / magnitude};

    return Vector2D::fromComponents(x, y);
}

} // namespace physics::domain

#endif // PHYSICS_BACKEND_DOMAIN_GEOMETRY_HPP
