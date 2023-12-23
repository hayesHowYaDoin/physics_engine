#ifndef DOMAIN_VECTOR_HPP_
#define DOMAIN_VECTOR_HPP_

#include "domain/concepts.hpp"
#include <units.h>

namespace domain
{

struct Vector2D
{
    template <IsMagnitudeUnit MagnitudeType>
    class Impl
    {
    public:
        constexpr Impl(MagnitudeType x, MagnitudeType y):
            m_x {x},
            m_y {y}
        {
            // Intentionally blank.
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

    private:
        MagnitudeType m_x;
        MagnitudeType m_y;
    };

    template <IsMagnitudeUnit MagnitudeType>
    static constexpr Impl<MagnitudeType> fromComponents(
        MagnitudeType x,
        MagnitudeType y)
    {
        return Impl<MagnitudeType> {x, y};
    }

    template <IsMagnitudeUnit MagnitudeType, IsAngleUnit AngleType>
    static Impl<MagnitudeType> fromPolar(
        AngleType angle,
        MagnitudeType magnitude)
    {
        if(magnitude.template to<float>() < 0.0f)
            throw std::invalid_argument {"Magnitude must be positive."};

        auto x {magnitude * units::cos(units::angle::radians(angle))};
        auto y {magnitude * units::sin(units::angle::radians(angle))};

        return Impl<MagnitudeType> {x, y};
    }
};

template <IsMagnitudeUnit RhsType, IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr
auto operator+(
    Vector2D::Impl<LhsType> const& lhs,
    Vector2D::Impl<RhsType> const& rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() + rhs.template getX<LhsType>()};
    auto y {lhs.template getY<LhsType>() + rhs.template getY<LhsType>()};

    return Vector2D::Impl(x, y);
}

template <IsMagnitudeUnit RhsType, IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr
auto operator-(
    Vector2D::Impl<LhsType> const& lhs,
    Vector2D::Impl<RhsType> const& rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() - rhs.template getX<LhsType>()};
    auto y {lhs.template getY<LhsType>() - rhs.template getY<LhsType>()};

    return Vector2D::Impl(x, y);
}

template <IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr 
auto operator*(Vector2D::Impl<LhsType> const& lhs, long double rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() * rhs};
    auto y {lhs.template getY<LhsType>() * rhs};

    return Vector2D::Impl(x, y);
}

template <IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr
auto operator/(Vector2D::Impl<LhsType> const& lhs, long double rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() / rhs};
    auto y {lhs.template getY<LhsType>() / rhs};

    return Vector2D::Impl(x, y);
}

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_