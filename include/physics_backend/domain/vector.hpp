#ifndef PHYSICS_BACKEND_UNITS_VECTOR_HPP
#define PHYSICS_BACKEND_UNITS_VECTOR_HPP

#include "physics_backend/units/units.hpp"

namespace physics::domain
{

struct Vector2D
{
    template <physics::units::IsMagnitudeUnit MagnitudeType>
    class Impl
    {
    public:
        constexpr Impl(MagnitudeType const& x, MagnitudeType const& y) noexcept:
            m_x {x},
            m_y {y}
        {
            // Intentionally blank.
        }

        template <physics::units::IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getX() const
        {
            return RetType(m_x);
        }

        template <physics::units::IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getY() const
        {
            return RetType(m_y);
        }

        template <physics::units::IsAngleUnit RetType>
        [[nodiscard]] auto getAngle() const
        {
            return RetType(atan2(m_x, m_y));
        }

        template <physics::units::IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getMagnitude() const
        {
            return RetType(sqrt(m_x * m_x + m_y * m_y));
        }

        template <physics::units::IsMagnitudeUnit RhsType>
        [[nodiscard]] constexpr auto dot(Impl<RhsType> const& rhs) const;

        template <physics::units::IsMagnitudeUnit RhsType>
        [[nodiscard]] constexpr auto cross(Impl<RhsType> const& rhs) const;

    private:
        MagnitudeType m_x;
        MagnitudeType m_y;
    };

    template <physics::units::IsMagnitudeUnit MagnitudeType>
    static constexpr Impl<MagnitudeType> fromComponents(
        MagnitudeType const& x,
        MagnitudeType const& y) noexcept
    {
        return Impl<MagnitudeType> {x, y};
    }

    template <physics::units::IsMagnitudeUnit MagnitudeType, physics::units::IsAngleUnit AngleType>
    static Impl<MagnitudeType> fromPolar(
        AngleType const& angle,
        MagnitudeType const& magnitude)
    {
        if(magnitude.template to<float>() < 0.0f)
            throw std::invalid_argument {"Magnitude must be positive."};

        auto x {magnitude * cos(physics::units::angle::radians(angle))};
        auto y {magnitude * sin(physics::units::angle::radians(angle))};

        return Impl<MagnitudeType> {x, y};
    }

    template <physics::units::IsMagnitudeUnit MagnitudeType>
    static constexpr bool compare(
        Impl<MagnitudeType> const& lhs,
        Impl<MagnitudeType> const& rhs,
        double epsilon) noexcept
    {
        auto xDiff {lhs.template getX<MagnitudeType>() - rhs.template getX<MagnitudeType>()};
        auto yDiff {lhs.template getY<MagnitudeType>() - rhs.template getY<MagnitudeType>()};
        MagnitudeType epsilonMagnitude {MagnitudeType(epsilon)};

        return xDiff < epsilonMagnitude && yDiff < epsilonMagnitude;
    }
};

template <physics::units::IsMagnitudeUnit RhsType, physics::units::IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr
auto operator+(
    Vector2D::Impl<LhsType> const& lhs,
    Vector2D::Impl<RhsType> const& rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() + rhs.template getX<LhsType>()};
    auto y {lhs.template getY<LhsType>() + rhs.template getY<LhsType>()};

    return Vector2D::Impl(x, y);
}

template <physics::units::IsMagnitudeUnit RhsType, physics::units::IsMagnitudeUnit LhsType>
[[nodiscard]] constexpr
auto operator-(
    Vector2D::Impl<LhsType> const& lhs,
    Vector2D::Impl<RhsType> const& rhs)
{
    auto x {lhs.template getX<LhsType>() - rhs.template getX<LhsType>()};
    auto y {lhs.template getY<LhsType>() - rhs.template getY<LhsType>()};

    return Vector2D::Impl(x, y);
}

template <physics::units::IsMagnitudeUnit LhsType, typename RhsType>
[[nodiscard]] constexpr 
auto operator*(Vector2D::Impl<LhsType> const& lhs, RhsType rhs)
{
    auto x {lhs.template getX<LhsType>() * rhs};
    auto y {lhs.template getY<LhsType>() * rhs};

    return Vector2D::Impl(x, y);
}

template <physics::units::IsMagnitudeUnit LhsType, typename RhsType>
[[nodiscard]] constexpr
auto operator/(Vector2D::Impl<LhsType> const& lhs, RhsType rhs)
{
    auto x {lhs.template getX<LhsType>() / rhs};
    auto y {lhs.template getY<LhsType>() / rhs};

    return Vector2D::Impl(x, y);
}

template <physics::units::IsMagnitudeUnit LhsType>
template <physics::units::IsMagnitudeUnit RhsType>
[[nodiscard]] constexpr
auto Vector2D::Impl<LhsType>::dot(Vector2D::Impl<RhsType> const& rhs) const
{
    return (m_x * rhs.template getX<RhsType>() + 
            m_y * rhs.template getY<RhsType>());
}

template <physics::units::IsMagnitudeUnit LhsType>
template <physics::units::IsMagnitudeUnit RhsType>
[[nodiscard]] constexpr
auto Vector2D::Impl<LhsType>::cross(Vector2D::Impl<RhsType> const& rhs) const
{
    return (m_x * rhs.template getY<RhsType>() - 
            m_y * rhs.template getX<RhsType>());
}

template <physics::units::IsLengthUnit MagnitudeType>
using PositionVector2D = Vector2D::Impl<MagnitudeType>;

template <typename T>
concept IsPositionVector2D = requires(T t)
{
    []<typename X>(PositionVector2D<X>&){}(t);
};

template <physics::units::IsVelocityUnit MagnitudeType>
using VelocityVector2D = Vector2D::Impl<MagnitudeType>;

template <typename T>
concept IsVelocityVector2D = requires(T t)
{
    []<typename X>(VelocityVector2D<X>&){}(t);
};

template <physics::units::IsAccelerationUnit MagnitudeType>
using AccelerationVector2D = Vector2D::Impl<MagnitudeType>;

template <typename T>
concept IsAccelerationVector2D = requires(T t)
{
    []<typename X>(AccelerationVector2D<X>&){}(t);
};

template <physics::units::IsForceUnit MagnitudeType>
using ForceVector2D = Vector2D::Impl<MagnitudeType>;

template <typename T>
concept IsForceVector2D = requires(T t)
{
    []<typename X>(ForceVector2D<X>&){}(t);
};

} // namespace physics::units

#endif // PHYSICS_BACKEND_UNITS_VECTOR_HPP
