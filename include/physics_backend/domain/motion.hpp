#ifndef PHYSICS_BACKEND_DOMAIN_MOTION_HPP
#define PHYSICS_BACKEND_DOMAIN_MOTION_HPP

#include "physics_backend/units.hpp"

namespace physics::domain
{

using namespace physics::units;

template <IsLengthUnit Length, IsVelocityUnit Velocity, IsTimeUnit Time>
[[nodiscard]] constexpr
PositionVector2D<Length> nextPosition(
    PositionVector2D<Length> const& position,
    VelocityVector2D<Velocity> const& velocity,
    Time const& dt)
{
    return position + velocity * dt;
}

template <IsVelocityUnit Velocity, IsAccelerationUnit Acceleration, IsTimeUnit Time>
[[nodiscard]] constexpr
VelocityVector2D<Velocity> nextVelocity(
    VelocityVector2D<Velocity> const& velocity,
    AccelerationVector2D<Acceleration> const& acceleration,
    Time const& dt)
{
    return velocity + acceleration * dt;
}

template <IsForceUnit Force, IsMassUnit Mass>
[[nodiscard]] constexpr
auto acceleration(
    ForceVector2D<Force> const& force,
    Mass const& mass) -> decltype(force / mass)
{
    if(mass <= Mass(0))
        throw std::invalid_argument("Mass must be greater than zero.");
    
    return force / mass;
}

} // namespace physics::domain

#endif // PHYSICS_BACKEND_DOMAIN_MOTION_HPP