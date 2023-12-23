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
            m_y {y}
        {
            // Intentionally blank
        }

        template <IsAngleUnit AngleType>
        static Vector2D<MagnitudeType> fromPolar(
            AngleType angle,
            MagnitudeType magnitude)
        {
            auto x {magnitude * units::cos(units::angle::radians(angle))};
            auto y {magnitude * units::sin(units::angle::radians(angle))};

            return Vector2D(x, y);
        }

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getX() const
        {
            return RetType(m_x);
        }

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getY() const
        {
            return RetType(m_y);
        }

        template <IsAngleUnit RetType>
        [[nodiscard]] auto getAngle() const
        {
            return RetType(units::atan2(m_x, m_y));
        }

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getMagnitude() const
        {
            return RetType(units::sqrt(m_x * m_x + m_y * m_y));
        }

        template <IsMagnitudeUnit OtherMagnitudeType>
        [[nodiscard]] constexpr
        auto operator+(Vector2D<OtherMagnitudeType> const& other) const
        {
            constexpr auto x {m_x + other.getX()};
            constexpr auto y {m_y + other.getY()};

            return Vector2D(x, y);
        }

        template <IsMagnitudeUnit OtherMagnitudeType>
        [[nodiscard]] constexpr
        auto operator-(Vector2D<OtherMagnitudeType> const& other) const
        {
            constexpr auto x {m_x - other.getX()};
            constexpr auto y {m_y - other.getY()};

            return Vector2D(x, y);
        }

        [[nodiscard]] constexpr auto operator*(long double scalar) const
        {
            constexpr auto x {m_x * scalar};
            constexpr auto y {m_y * scalar};

            return Vector2D(x, y);
        }

        [[nodiscard]] constexpr auto operator/(long double scalar) const
        {
            constexpr auto x {m_x / scalar};
            constexpr auto y {m_y / scalar};

            return Vector2D(x, y);
        }

    private:
        MagnitudeType m_x;
        MagnitudeType m_y;
    };

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_