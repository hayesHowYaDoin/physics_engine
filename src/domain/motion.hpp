#ifndef DOMAIN_MOTION_HPP
#define DOMAIN_MOTION_HPP

#include "domain/vector.hpp"
#include "core/concepts.hpp"

namespace domain::motion
{

template <core::IsLengthUnit L, core::IsVelocityUnit V, core::IsTimeUnit T>
[[nodiscard]] constexpr
decltype(auto) nextPosition(
    PositionVector2D<L> const& position,
    VelocityVector2D<V> const& velocity,
    T const& dt) noexcept
{
    return position + velocity * dt;
}

template <core::IsVelocityUnit V, core::IsAccelerationUnit A, core::IsTimeUnit T>
[[noexcept]] constexpr
decltype(auto) nextVelocity(
    VelocityVector2D<V> const& velocity,
    AccelerationVector2D<A> const& acceleration,
    T const& dt) noexcept
{
    return velocity + acceleration * dt;
}

template <core::IsForceUnit F, core::IsMassUnit M>
[[nodiscard]] constexpr
decltype(auto) acceleration(
    ForceVector2D<F> const& force,
    M const& mass)
{
    if(mass <= M(0))
        throw std::invalid_argument("Mass must be greater than zero.");
    
    return force / mass;
}

} // namespace domain::motion

#endif // DOMAIN_MOTION_HPP
