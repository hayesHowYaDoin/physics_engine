#ifndef DOMAIN_EULER_HPP
#define DOMAIN_EULER_HPP

#include "domain/vector.hpp"
#include "core/concepts.hpp"

namespace domain::euler
{

template <core::IsLengthUnit LengthType, core::IsVelocityUnit VelocityType, core::IsTimeUnit TimeType>
[[nodiscard]] constexpr
PositionVector2D<LengthType> nextPosition(
    PositionVector2D<LengthType> const& position,
    VelocityVector2D<VelocityType> const& velocity,
    TimeType const& dt)
{
    return position + velocity * dt;
}

template <core::IsVelocityUnit VelocityType, core::IsAccelerationUnit AccelerationType, core::IsTimeUnit TimeType>
[[noexcept]] constexpr
VelocityVector2D<VelocityType> nextVelocity(
    VelocityVector2D<VelocityType> const& velocity,
    AccelerationVector2D<AccelerationType> const& acceleration,
    TimeType const& dt)
{
    return velocity + acceleration * dt;
}

template <core::IsAccelerationUnit AccelerationType, core::IsForceUnit ForceType, core::IsMassUnit MassType>
[[nodiscard]] constexpr
AccelerationVector2D<AccelerationType> acceleration(
    ForceVector2D<ForceType> const& force,
    MassType const& mass)
{
    return force / mass;
}

} // namespace domain::euler

#endif // DOMAIN_EULER_HPP
