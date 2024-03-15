#ifndef PHYSICS_BACKEND_DOMAIN_EDGE_HPP
#define PHYSICS_BACKEND_DOMAIN_EDGE_HPP

#include <cmath>
#include <optional>

#include "physics_engine/units.hpp"

namespace physics::usecases
{

template <physics::units::IsLengthUnit Length>
using Edge2D = std::pair<physics::domain::PositionVector2D<Length>, physics::domain::PositionVector2D<Length>>;

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_DOMAIN_EDGE_HPP
