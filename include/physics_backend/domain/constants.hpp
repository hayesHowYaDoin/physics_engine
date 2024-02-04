#ifndef PHYSICS_BACKEND_DOMAIN_CONSTANTS_HPP
#define PHYSICS_BACKEND_DOMAIN_CONSTANTS_HPP

#include "physics_backend/units/units.hpp"

namespace physics::domain
{

[[nodiscard]] constexpr
auto const G {units::acceleration::meters_per_second_squared<double> {-9.81}};

} // namespace physics::domain

#endif // PHYSICS_BACKEND_DOMAIN_CONSTANTS_HPP
