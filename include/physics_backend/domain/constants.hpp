#ifndef DOMAIN_CONSTANTS_HPP
#define DOMAIN_CONSTANTS_HPP

#include <units.h>

namespace physics::domain
{

[[nodiscard]] constexpr
auto const G {units::acceleration::meters_per_second_squared<double> {-9.81}};

} // namespace domain::constants

#endif // physics::domain