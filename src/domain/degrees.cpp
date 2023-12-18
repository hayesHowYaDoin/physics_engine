#include "domain/degrees.hpp"

#include <cmath>
#include <stdexcept>

namespace domain
{

AngleDegrees::AngleDegrees(float value) :
    m_value { constrain(value) }
{
    // Intentionally left blank.
}

float AngleDegrees::operator()() const
{
    return m_value;
}

AngleDegrees AngleDegrees::operator+(AngleDegrees const& other) const 
{
    return AngleDegrees{constrain(m_value + other.m_value)};
}

AngleDegrees AngleDegrees::operator-(AngleDegrees const& other) const 
{
    return AngleDegrees{constrain(m_value - other.m_value)};
}

float AngleDegrees::constrain(float value) const 
{
    value = std::fmod(value, 360.0f);

    if (value > 180.0f)
    {
        value -= 360.0f;
    }
    else if (value < -180.0f)
    {
        value += 360.0f;
    }

    return value;
}

namespace literals
{
    AngleDegrees operator"" _degrees(long double value)
    {
        return AngleDegrees{static_cast<float>(value)};
    }
}

} // namespace domain
