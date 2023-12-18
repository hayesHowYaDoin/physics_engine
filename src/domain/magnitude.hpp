#ifndef DOMAIN_MAGNITUDE_HPP
#define DOMAIN_MAGNITUDE_HPP

#include <compare>
#include <stdexcept>

namespace domain
{

class Magnitude {
public:
    Magnitude(float value);

    float operator()() const;

    Magnitude operator+(Magnitude const& other) const;

    Magnitude operator-(Magnitude const& other) const;

    Magnitude operator*(Magnitude const& other) const;

    Magnitude operator/(Magnitude const& other) const;

    auto operator<=>(Magnitude const&) const = default;

private:
    float m_value;
};

namespace literals
{

    Magnitude operator"" _mag(long double value);
    
} // namespace literals

} // namespace domain

#endif // DOMAIN_MAGNITUDE_HPP
