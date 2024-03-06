#ifndef PHYSICS_BACKEND_USECASES_EULER_PARTICLE_HPP
#define PHYSICS_BACKEND_USECASES_EULER_PARTICLE_HPP

#include <any>

#include "physics_backend/units.hpp"
#include "physics_backend/domain/vector.hpp"

namespace physics::euler
{

template<physics::units::IsUnitSystem Units>
struct Particle
{
    using Mass = typename Units::Mass;
    using Length = typename Units::Length;
    using Velocity = typename Units::Velocity;
    using Force = typename Units::Force;

    Mass mass;
    Length radius;
    physics::domain::PositionVector2D<Length> position;
    physics::domain::VelocityVector2D<Velocity> velocity;
    std::vector<physics::domain::ForceVector2D<Force>> forces;
    std::any metadata = nullptr;

    physics::domain::PositionVector2D<Length> getCenter() const
    {
        return position;
    }

    void setCenter(physics::domain::PositionVector2D<Length> const& center)
    {
        position = center;
    }

    Length getRadius() const
    {
        return radius;
    }
};

} // namespace physics::euler

#endif // PHYSICS_BACKEND_USECASES_EULER_PARTICLE_HPP
