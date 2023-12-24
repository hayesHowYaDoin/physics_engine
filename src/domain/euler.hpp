#ifndef DOMAIN_EULER_HPP
#define DOMAIN_EULER_HPP

#include "domain/vector.hpp"
#include "core/concepts.hpp"

namespace domain::euler
{

    template <core::IsLengthUnit LengthType, core::IsVelocityUnit VelocityType, core::IsTimeUnit TimeType>
    PositionVector2D<LengthType> nextPosition(
        PositionVector2D<LengthType> const& position,
        VelocityVector2D<VelocityType> const& velocity,
        TimeType const& dt)
    {
        return Vector2D::fromComponents(
            position.getX<LengthType>() + velocity.getX<VelocityType>() * dt,
            position.getY<LengthType>() + velocity.getY<VelocityType>() * dt);
    }

} // namespace domain::euler

#endif // DOMAIN_EULER_HPP
