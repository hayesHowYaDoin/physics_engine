#include "domain/angle.hpp"

#include <cmath>
#include <stdexcept>

namespace domain
{

Angle Angle::fromDegrees(float degrees)
{
    return Angle { Angle::constrain(degrees) };
}

Angle Angle::fromRadians(float radians)
{

    return Angle { Angle::constrain(Angle::toDegrees(radians)) };
}

Angle Angle::operator+(Angle const& other) const 
{
    return Angle{ constrain(this->inDegrees() + other.inDegrees()) };
}

Angle Angle::operator+(Angle const&& other) const 
{
    return Angle{ constrain(this->inDegrees() + other.inDegrees()) };
}

Angle Angle::operator-(Angle const& other) const 
{
    return Angle{ constrain(this->inDegrees() - other.inDegrees()) };
}

Angle Angle::operator-(Angle const&& other) const 
{
    return Angle{ constrain(this->inDegrees() - other.inDegrees()) };
}

bool Angle::operator==(const Angle& other) const
{
    static constexpr float PRECISION = 0.001f;

    float deltaDegrees { std::abs(this->inDegrees() - other.inDegrees()) };

    return deltaDegrees < PRECISION || (360.0f - deltaDegrees) < PRECISION;
}

Angle::Angle(float degrees) :
    m_degrees { degrees }
{
    // Intentionally left blank.
}

float Angle::constrain(float degrees) 
{
    degrees = std::fmod(degrees, 360.0f);

    if (degrees > 180.0f)
    {
        degrees -= 360.0f;
    }
    else if (degrees <= -180.0f)
    {
        degrees += 360.0f;
    }

    return degrees;
}

namespace literals
{
    Angle operator"" _deg(long double degrees)
    {
        return Angle::fromDegrees(static_cast<float>(degrees));
    }

    Angle operator"" _rad(long double radians)
    {
        return Angle::fromRadians(static_cast<float>(radians));
    }
}

} // namespace domain
