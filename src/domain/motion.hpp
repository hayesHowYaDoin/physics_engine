#ifndef DOMAIN_MOTION_HPP
#define DOMAIN_MOTION_HPP

#include "domain/vector.hpp"
#include "core/concepts.hpp"

namespace domain::motion
{

template <core::IsLengthUnit Length, core::IsVelocityUnit Velocity, core::IsTimeUnit Time>
[[nodiscard]] constexpr
PositionVector2D<Length> nextPosition(
    PositionVector2D<Length> const& position,
    VelocityVector2D<Velocity> const& velocity,
    Time const& dt) noexcept
{
    return position + velocity * dt;
}

template <core::IsVelocityUnit Velocity, core::IsAccelerationUnit Acceleration, core::IsTimeUnit Time>
[[noexcept]] constexpr
VelocityVector2D<Velocity> nextVelocity(
    VelocityVector2D<Velocity> const& velocity,
    AccelerationVector2D<Acceleration> const& acceleration,
    Time const& dt) noexcept
{
    return velocity + acceleration * dt;
}

template <core::IsForceUnit Force, core::IsMassUnit Mass>
[[nodiscard]] constexpr
auto acceleration(
    ForceVector2D<Force> const& force,
    Mass const& mass) -> decltype(force / mass)
{
    if(mass <= Mass(0))
        throw std::invalid_argument("Mass must be greater than zero.");
    
    return force / mass;
}

} // namespace domain::motion

#endif // DOMAIN_MOTION_HPP
