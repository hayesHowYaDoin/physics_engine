#ifndef DOMAIN_VECTOR_HPP_
#define DOMAIN_VECTOR_HPP_

#include "domain/concepts.hpp"
#include "domain/coordinates.hpp"
#include <units.h>

namespace domain
{

    template <AngleUnit AngleType, MagnitudeUnit MagnitudeType>
    class Vector2D
    {
        static constexpr Vector2D fromComponents(Coordinates2D<MagnitudeType> const& components)
        {
            auto x = components.x;
            auto y = components.y;

            auto angle = units::atan(y / x);
            auto magnitude = units::sqrt(x * x + y * y);

            return Vector2D {angle, magnitude};
        }

        [[nodiscard]] constexpr Coordinates2D<LengthUnit auto> toComponents() const
        {
            auto x = units::unit_cast<double>(m_magnitude) * units::cos(m_angle);
            auto y = m_magnitude * units::sin(m_angle);

            return Coordinates2D {x, y};
        }

    private:
        AngleType m_angle;
        MagnitudeType m_magnitude;
    };

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_