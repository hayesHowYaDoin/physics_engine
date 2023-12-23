#ifndef DOMAIN_COMPONENTS_2D_HPP
#define DOMAIN_COMPONENTS_2D_HPP

#include "domain/concepts.hpp"

namespace domain
{

    template <IsMagnitudeUnit MagnitudeType>
    struct Components2D {
        MagnitudeType const x;
        MagnitudeType const y;

        template <IsMagnitudeUnit OtherMagnitudeType>
        [[nodiscard]] constexpr
        auto operator+(Components2D<OtherMagnitudeType> const& other) const
        {
            return {x + other.x, y + other.y};
        }

        template <IsMagnitudeUnit OtherMagnitudeType>
        [[nodiscard]] constexpr
        auto operator-(Components2D<OtherMagnitudeType> const& other) const
        {
            return {x - other.x, y - other.y};
        }

        [[nodiscard]] constexpr auto operator*(double scalar) const
        {
            return {x * scalar, y * scalar};
        }

        [[nodiscard]] constexpr auto operator/(double scalar) const
        {
            return {x / scalar, y / scalar};
        }
    };

} // namespace domain

#endif // DOMAIN_COMPONENTS_2D_HPP
