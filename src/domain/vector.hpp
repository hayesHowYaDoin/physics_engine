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

        // constexpr Vector2D(Coordinates2D components) :
        //     m_angle {units::atan(components.getY() / components.getX())},
        //     m_magnitude {units::sqrt(units::pow(components.getX(), 2) + units::pow(components.getY(), 2))}
        // {
        //     // Intentionally blank.
        // }

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

        // [[nodiscard]] constexpr Coordinates2D getComponents() const
        // {
        //     units::meters<double> x = units::unit_cast<double>(m_magnitude) * units::cos(m_angle);
        //     units::meters<double> y = m_magnitude * units::sin(m_angle);

        //     return Coordinates2D(x, y);
        //     return Coordinates2D()
        // }

    private:
        units::degrees<double> m_angle;
        units::newtons<double> m_magnitude;
    };

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_