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
            m_components {.x {x}, .y {y}},
            m_angle {units::atan2(y, x)},
            m_magnitude {units::sqrt(x * x + y * y)}
        {
            // Intentionally blank
        }

        template <IsAngleUnit AngleType>
        constexpr Vector2D(AngleType angle, MagnitudeType magnitude):
            m_components {
                .x {magnitude * units::cos(units::angle::radians(angle))},
                .y {magnitude * units::sin(units::angle::radians(angle))}
            },
            m_angle {units::angle::radians(angle)},
            m_magnitude {magnitude}
        {
            // Intentionally blank
        }

        template <IsMagnitudeUnit ComponentType>
        struct Components2D
        {
            ComponentType const x;
            ComponentType const y;
        };

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getComponents() const
        {
            return Components2D<RetType> {
                .x {m_components.x},
                .y {m_components.y}
            };
        }

        template <IsAngleUnit RetType>
        [[nodiscard]] constexpr auto getAngle() const
        {
            return RetType(m_angle);
        }

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getMagnitude() const
        {
            return RetType(m_magnitude);
        }

    private:
        Components2D<MagnitudeType> m_components;
        units::angle::radians<double> m_angle;
        MagnitudeType m_magnitude;
    };

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_