#ifndef PHYSICS_BACKEND_USECASES_STEP_HPP
#define PHYSICS_BACKEND_USECASES_STEP_HPP

#include <ranges>

#include "physics_backend/units.hpp"
#include "physics_backend/usecases/collision.hpp"
#include "physics_backend/usecases/constrain.hpp"
#include "physics_backend/usecases/polygon.hpp"
#include "physics_backend/usecases/detail/fmaps.hpp"
#include "physics_backend/usecases/motion.hpp"
#include "physics_backend/usecases/particle.hpp"

namespace physics::usecases
{

template<
    template <typename...> class Container,
    physics::units::IsUnitSystem Units,
    physics::units::IsTimeUnit Time>
auto step(
    Container<Particle<Units>> const& particles,
    Polygon2D<typename Units::Length> const& constraint,
    Time time,
    uint32_t substeps = 1)
{
    if(substeps == 0)
    {
        std::cerr << "Substeps cannot be 0. Setting substeps to default value (1)." << '\n';
        substeps = 1;
    }

    Time subTime {time / substeps};
    auto wrappedParticles {particles};

    for(size_t substep {0}; substep < substeps; ++substep)
    {
        auto motion = [&time](auto const& particle){ return resolveMotion(particle, time); };
        auto constrain = [&constraint](auto const& particle){ return resolveConstraint(particle, constraint); };

        auto updatedParticles {physics::detail::fmaps(wrappedParticles, motion, constrain)};
        wrappedParticles = Container<Particle<Units>>(updatedParticles.begin(), updatedParticles.end());

        resolveCollisions(wrappedParticles);
    }

    return wrappedParticles;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_STEP_HPP
