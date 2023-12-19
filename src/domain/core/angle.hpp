#ifndef DOMAIN_CORE_DEGREES_HPP
#define DOMAIN_CORE_DEGREES_HPP

#include "domain/core/constants.hpp"
#include "domain/core/units.hpp"

#include <compare>
#include <string>

namespace domain
{

class Angle {
public:
    static Angle fromDegrees(units::Degrees degrees);
    static Angle fromRadians(units::Radians radians);

    constexpr float inDegrees() const
    {
        return m_degrees;
    }

    constexpr float inRadians() const
    {
        return toRadians(m_degrees);
    }

    Angle operator+(const Angle& other) const;
    Angle operator+(const Angle&& other) const;

    Angle operator-(const Angle& other) const;
    Angle operator-(const Angle&& other) const;

    bool operator==(const Angle& other) const;

private:
    Angle(units::Degrees degrees);

    static float constrain(units::Degrees value);

    static constexpr units::Radians toRadians(units::Degrees degrees)
    {
        return degrees * domain::constants::PI / 180.0f;
    }

    static constexpr units::Degrees toDegrees(units::Radians radians)
    {
        return radians * 180.0f / domain::constants::PI;
    }

    units::Degrees m_degrees;
};

namespace math
{

    constexpr float cos(Angle const& angle)
    {
        return std::cos(angle.inRadians());
    }

    constexpr float sin(Angle const& angle)
    {
        return std::sin(angle.inRadians());
    }

    constexpr float tan(Angle const& angle)
    {
        return std::tan(angle.inRadians());
    }

} // namespace math

namespace literals
{

    Angle operator"" _deg(long double value);

    Angle operator"" _rad(long double value);

} // namespace literals

} // namespace domain

#endif // DOMAIN_DEGREES_HPP
