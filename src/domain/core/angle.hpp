#ifndef DOMAIN_DEGREES_HPP
#define DOMAIN_DEGREES_HPP

#include "domain/core/constants.hpp"

#include <compare>
#include <string>

namespace domain
{

class Angle {
public:
    static Angle fromDegrees(float degrees);
    static Angle fromRadians(float radians);

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
    Angle(float degrees);

    static float constrain(float value);

    static constexpr float toRadians(float degrees)
    {
        return degrees * domain::constants::PI / 180.0f;
    }

    static constexpr float toDegrees(float radians)
    {
        return radians * 180.0f / domain::constants::PI;
    }

    float m_degrees;
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
