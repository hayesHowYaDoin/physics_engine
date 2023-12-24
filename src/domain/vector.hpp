#ifndef DOMAIN_VECTOR_HPP_
#define DOMAIN_VECTOR_HPP_

#include "core/concepts.hpp"
#include <units.h>

namespace domain
{

struct Vector2D
{
    template <core::IsMagnitudeUnit MagnitudeType>
    class Impl
    {
    public:
        constexpr Impl(MagnitudeType x, MagnitudeType y) noexcept:
            m_x {x},
            m_y {y}
        {
            // Intentionally blank.
        }

        template <core::IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getX() const
        {
            return RetType(m_x);
        }

        template <core::IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getY() const
        {
            return RetType(m_y);
        }

        template <core::IsAngleUnit RetType>
        [[nodiscard]] auto getAngle() const
        {
            return RetType(units::atan2(m_x, m_y));
        }

        template <core::IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getMagnitude() const
        {
            return RetType(units::sqrt(m_x * m_x + m_y * m_y));
        }

        template <core::IsMagnitudeUnit RhsType>
        [[nodiscard]] constexpr auto dot(Impl<RhsType> const& rhs) const
        {
            return (m_x * rhs.template getX<RhsType>() + 
                    m_y * rhs.template getY<RhsType>());
        }

        template <core::IsMagnitudeUnit RhsType>
        [[nodiscard]] constexpr auto cross(Impl<RhsType> const& rhs) const
        {
            return (m_x * rhs.template getY<RhsType>() - 
                    m_y * rhs.template getX<RhsType>());
        }

    private:
        MagnitudeType m_x;
        MagnitudeType m_y;
    };

    template <core::IsMagnitudeUnit MagnitudeType>
    static constexpr Impl<MagnitudeType> fromComponents(
        MagnitudeType x,
        MagnitudeType y) noexcept
    {
        return Impl<MagnitudeType> {x, y};
    }

    template <core::IsMagnitudeUnit MagnitudeType, core::IsAngleUnit AngleType>
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

template <core::IsMagnitudeUnit RhsType, core::IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr
auto operator+(
    Vector2D::Impl<LhsType> const& lhs,
    Vector2D::Impl<RhsType> const& rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() + rhs.template getX<LhsType>()};
    auto y {lhs.template getY<LhsType>() + rhs.template getY<LhsType>()};

    return Vector2D::Impl(x, y);
}

template <core::IsMagnitudeUnit RhsType, core::IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr
auto operator-(
    Vector2D::Impl<LhsType> const& lhs,
    Vector2D::Impl<RhsType> const& rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() - rhs.template getX<LhsType>()};
    auto y {lhs.template getY<LhsType>() - rhs.template getY<LhsType>()};

    return Vector2D::Impl(x, y);
}

template <core::IsMagnitudeUnit LhsType, typename RhsType>
[[nodiscard]] constexpr 
auto operator*(Vector2D::Impl<LhsType> const& lhs, RhsType rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() * rhs};
    auto y {lhs.template getY<LhsType>() * rhs};

    return Vector2D::Impl(x, y);
}

template <core::IsMagnitudeUnit LhsType, typename RhsType>
[[nodiscard]] constexpr
auto operator/(Vector2D::Impl<LhsType> const& lhs, RhsType rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() / rhs};
    auto y {lhs.template getY<LhsType>() / rhs};

    return Vector2D::Impl(x, y);
}

template <core::IsLengthUnit LengthType>
using PositionVector2D = Vector2D::Impl<LengthType>;

template <core::IsVelocityUnit VelocityType>
using VelocityVector2D = Vector2D::Impl<VelocityType>;

template <core::IsAccelerationUnit AccelerationType>
using AccelerationVector2D = Vector2D::Impl<AccelerationType>;

template <core::IsForceUnit ForceType>
using ForceVector2D = Vector2D::Impl<ForceType>;

} // namespace domain

#endif // DOMAIN_VECTOR_HPP_