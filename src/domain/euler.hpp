#ifndef DOMAIN_EULER_HPP
#define DOMAIN_EULER_HPP

#include "domain/vector.hpp"
#include "core/concepts.hpp"

namespace domain::euler
{

template <core::IsLengthUnit L, core::IsVelocityUnit V, core::IsTimeUnit T>
[[nodiscard]] constexpr
PositionVector2D<L> nextPosition(
    PositionVector2D<L> const& position,
    VelocityVector2D<V> const& velocity,
    T const& dt) noexcept
{
    return position + velocity * dt;
}

template <core::IsVelocityUnit V, core::IsAccelerationUnit A, core::IsTimeUnit T>
[[noexcept]] constexpr
VelocityVector2D<V> nextVelocity(
    VelocityVector2D<V> const& velocity,
    AccelerationVector2D<A> const& acceleration,
    T const& dt) noexcept
{
    return velocity + acceleration * dt;
}

template <core::IsAccelerationUnit A, core::IsForceUnit F, core::IsMassUnit M>
[[nodiscard]] constexpr
AccelerationVector2D<A> acceleration(
    ForceVector2D<F> const& force,
    M const& mass)
{
    if(mass <= M(0))
        throw std::invalid_argument("Mass must be greater than zero.");
    
    return force / mass;
}

} // namespace domain::euler

#endif // DOMAIN_EULER_HPP
