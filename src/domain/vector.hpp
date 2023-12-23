#ifndef DOMAIN_VECTOR_HPP_
#define DOMAIN_VECTOR_HPP_

#include "domain/concepts.hpp"
#include <units.h>

namespace domain
{

    template <IsMagnitudeUnit MagnitudeType>
    class Vector2D
    {
    public:
        constexpr Vector2D(MagnitudeType x, MagnitudeType y):
            m_x {x},
            m_y {y},
            m_angle {units::atan2(y, x)},
            m_magnitude {units::sqrt(x * x + y * y)}
        {
            // Intentionally blank
        }

        template <IsAngleUnit AngleType>
        constexpr Vector2D(AngleType angle, MagnitudeType magnitude):
            m_x {magnitude * units::cos(units::angle::radians(angle))},
            m_y {magnitude * units::sin(units::angle::radians(angle))},
            m_angle {units::angle::radians(angle)},
            m_magnitude {magnitude}
        {
            // Intentionally blank
        }

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr
        std::pair<RetType, RetType> getComponents() const
        {
            return std::make_pair(RetType(m_x), RetType(m_y));
        }

        template <IsAngleUnit RetType>
        [[nodiscard]] constexpr RetType getAngle() const
        {
            return RetType(m_angle);
        }

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr RetType getMagnitude() const
        {
            return RetType(m_magnitude);
        }

    private:
        MagnitudeType m_x;
        MagnitudeType m_y;

        units::angle::radians<double> m_angle;
        MagnitudeType m_magnitude;
    };

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_