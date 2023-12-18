#include "magnitude.hpp"

namespace domain
{

Magnitude::Magnitude(float value) :
    m_value { value }
{
    if (value < 0.0f) {
        throw std::invalid_argument("Magnitude value must be positive");
    }
    m_value = value;
}

float Magnitude::operator()() const 
{
    return m_value;
}

Magnitude Magnitude::operator+(Magnitude const& other) const
{
    return Magnitude(m_value + other.m_value);
}

Magnitude Magnitude::operator-(Magnitude const& other) const
{
    return Magnitude(m_value - other.m_value);
}

Magnitude Magnitude::operator*(Magnitude const& other) const
{
    return Magnitude(m_value * other.m_value);
}

Magnitude Magnitude::operator/(Magnitude const& other) const
{
    return Magnitude(m_value / other.m_value);
}

namespace literals
{

    Magnitude operator"" _mag(long double value)
    {
        return Magnitude(static_cast<float>(value));
    }
    
} // namespace literals

} // namespace domain
