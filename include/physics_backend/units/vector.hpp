#ifndef PHYSICS_BACKEND_UNITS_VECTOR_HPP
#define PHYSICS_BACKEND_UNITS_VECTOR_HPP

#include "physics_backend/units/units.hpp"

namespace physics::units
{

struct Vector2D
{
    template <IsMagnitudeUnit MagnitudeType>
    class Impl
    {
    public:
        constexpr Impl(MagnitudeType x, MagnitudeType y) noexcept:
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
            return RetType(atan2(m_x, m_y));
        }

        template <IsMagnitudeUnit RetType>
        [[nodiscard]] constexpr auto getMagnitude() const
        {
            return RetType(sqrt(m_x * m_x + m_y * m_y));
        }

        template <IsMagnitudeUnit RhsType>
        [[nodiscard]] constexpr auto dot(Impl<RhsType> const& rhs) const
        {
            return (m_x * rhs.template getX<RhsType>() + 
                    m_y * rhs.template getY<RhsType>());
        }

        template <IsMagnitudeUnit RhsType>
        [[nodiscard]] constexpr auto cross(Impl<RhsType> const& rhs) const
        {
            return (m_x * rhs.template getY<RhsType>() - 
                    m_y * rhs.template getX<RhsType>());
        }

    private:
        MagnitudeType m_x;
        MagnitudeType m_y;
    };

    template <IsMagnitudeUnit MagnitudeType>
    static constexpr Impl<MagnitudeType> fromComponents(
        MagnitudeType x,
        MagnitudeType y) noexcept
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

        auto x {magnitude * cos(angle::radians(angle))};
        auto y {magnitude * sin(angle::radians(angle))};

        return Impl<MagnitudeType> {x, y};
    }

    template <IsMagnitudeUnit MagnitudeType>
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

template <IsMagnitudeUnit LhsType, typename RhsType>
[[nodiscard]] constexpr 
auto operator*(Vector2D::Impl<LhsType> const& lhs, RhsType rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() * rhs};
    auto y {lhs.template getY<LhsType>() * rhs};

    return Vector2D::Impl(x, y);
}

template <IsMagnitudeUnit LhsType, typename RhsType>
[[nodiscard]] constexpr
auto operator/(Vector2D::Impl<LhsType> const& lhs, RhsType rhs) noexcept
{
    auto x {lhs.template getX<LhsType>() / rhs};
    auto y {lhs.template getY<LhsType>() / rhs};

    return Vector2D::Impl(x, y);
}

template <IsLengthUnit LengthType>
using PositionVector2D = Vector2D::Impl<LengthType>;

template <typename T>
concept IsPositionVector2D = std::is_same_v<T, PositionVector2D<typename T::MagnitudeType>>;

template <IsVelocityUnit VelocityType>
using VelocityVector2D = Vector2D::Impl<VelocityType>;

template <typename T>
concept IsVelocityVector2D = std::is_same_v<T, VelocityVector2D<typename T::MagnitudeType>>;

template <IsAccelerationUnit AccelerationType>
using AccelerationVector2D = Vector2D::Impl<AccelerationType>;

template <typename T>
concept IsAccelerationVector2D = std::is_same_v<T, AccelerationVector2D<typename T::MagnitudeType>>;

template <IsForceUnit ForceType>
using ForceVector2D = Vector2D::Impl<ForceType>;

template <typename T>
concept IsForceVector2D = std::is_same_v<T, ForceVector2D<typename T::MagnitudeType>>;


} // namespace physics::units

#endif // PHYSICS_BACKEND_UNITS_VECTOR_HPP
