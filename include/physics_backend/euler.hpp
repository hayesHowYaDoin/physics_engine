#ifndef PHYSICS_BACKEND_EULER_H_
#define PHYSICS_BACKEND_EULER_H_

#include <units.h>

#include "physics_backend/units.hpp"

namespace physics_backend::euler
{

template<physics_backend::IsUnitSystem T>
struct EulerParticle;

template<std::ranges::range Range>
auto step(Range&& particle, uint32_t seconds);

} // namespace physics_backend::euler

#endif // PHYSICS_BACKEND_EULER_H_