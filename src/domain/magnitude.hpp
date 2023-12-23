#ifndef DOMAIN_MAGNITUDE_HPP_
#define DOMAIN_MAGNITUDE_HPP_

#include "domain/concepts.hpp"

#include <concepts>

namespace domain
{

    template <MagnitudeUnit Magnitude>
    struct Magnitude
    {
        Magnitude const value;

        constexpr Magnitude operator+(const Magnitude& rhs) const
        {
            return Magnitude {value + rhs.value};
        }

        constexpr Magnitude operator-(const Magnitude& rhs) const
        {
            return Magnitude {value - rhs.value};
        }

        template <std::integral Scalar>
        constexpr Magnitude operator*(const Magnitude& rhs) const
        {
            return Magnitude {value * rhs.value};
        }
    };

} // namespace domain

#endif // DOMAIN_MAGNITUDE_HPP_