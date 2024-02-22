#ifndef PHYSICS_BACKEND_DOMAIN_EDGE_HPP
#define PHYSICS_BACKEND_DOMAIN_EDGE_HPP

#include <cmath>
#include <optional>

#include "physics_backend/units.hpp"

namespace physics::usecases
{

template <physics::units::IsLengthUnit Length>
using Edge2D = std::pair<physics::domain::PositionVector2D<Length>, physics::domain::PositionVector2D<Length>>;

template <physics::units::IsLengthUnit Length>
[[nodiscard]] constexpr
std::optional<Length> findEdgeXAtY(
    Length const& y,
    Edge2D<Length> const& edge,
    float const& epsilon = 1e-6)
{
    auto x1 {edge.first.template getX<Length>()};
    auto y1 {edge.first.template getY<Length>()};

    auto x2 {edge.second.template getX<Length>()};
    auto y2 {edge.second.template getY<Length>()};

    // Vertical edge
    if(x1 == x2)
    {
        if(y <= y1 && y >= y2 || y >= y1 && y <= y2)
            return x1;

        return std::nullopt;
    }

    // Horizontal edge
    if(y1 == y2)
    {
        if(y == y1)
            return x1;

        return std::nullopt;
    }

    auto m {(y2 - y1) / (x2 - x1)};
    auto b {y1 - m * x1};
    auto x {(y - b) / m};

    std::cout << x << " vs. " << x1 << " -> " << x2 << std::endl;

    auto retVal {x >= x1 && x < x2 ? std::make_optional(x) : std::nullopt};

    std::cout << retVal.value_or(Length(-1)) << std::endl;

    return retVal;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_DOMAIN_EDGE_HPP
