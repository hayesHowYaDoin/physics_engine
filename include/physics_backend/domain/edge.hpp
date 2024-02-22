#ifndef PHYSICS_BACKEND_DOMAIN_EDGE_HPP
#define PHYSICS_BACKEND_DOMAIN_EDGE_HPP

#include "physics_backend/units.hpp"

namespace physics::domain
{

    template <physics::units::IsLengthUnit Length>
    using Edge2D = std::pair<physics::units::Vector2D<Length>, physics::units::Vector2D<Length>>;

} // namespace physics::domain

#endif // PHYSICS_BACKEND_DOMAIN_EDGE_HPP
