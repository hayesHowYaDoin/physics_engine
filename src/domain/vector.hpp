#ifndef DOMAIN_VECTOR_HPP_
#define DOMAIN_VECTOR_HPP_

#include "domain/concepts.hpp"
#include "domain/coordinates.hpp"
#include <units.h>

namespace domain
{

    class Vector2D
    {
    public:
        template <AngleUnit AngleType, ForceUnit MagnitudeType>
        constexpr Vector2D(AngleType angle, MagnitudeType magnitude) :
            m_angle {angle},
            m_magnitude {magnitude}
        {
            // Intentionally blank.
        }

        template <LengthUnit Coord1Type, LengthUnit Coord2Type>
        constexpr Vector2D(
            Coordinates2D<Coord1Type> start, 
            Coordinates2D<Coord2Type> end) :
            m_angle {std::atan2(end.y - start.y, end.x - start.x)},
            m_magnitude {std::hypot(end.y - start.y, end.x - start.x)}
        {
            // Intentionally blank.
        }

        template <AngleUnit AngleType>
        [[nodiscard]] constexpr AngleType getAngle() const
        {
            return m_angle;
        }

        template <ForceUnit ForceType>
        [[nodiscard]] constexpr ForceType getMagnitude() const
        {
            return m_magnitude;
        }

        template <LengthUnit CoordType>
        [[nodiscard]] constexpr Coordinates2D<CoordType> getComponents() const
        {
            auto x { m_magnitude * std::cos(m_angle) };
            auto y { m_magnitude * std::sin(m_angle) };

            return {x, y};
        }

    private:
        AngleUnit m_angle;
        ForceUnit m_magnitude;
    };

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_