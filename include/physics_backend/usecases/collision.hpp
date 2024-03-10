#ifndef PHYSICS_BACKEND_USECASES_EULER_COLLISION_HPP
#define PHYSICS_BACKEND_USECASES_EULER_COLLISION_HPP

#include "physics_backend/units.hpp"
#include "physics_backend/domain/geometry.hpp"
#include "physics_backend/usecases/objects.hpp"
#include "physics_backend/domain/vector.hpp"

#include <algorithm>
#include <ranges>
#include <functional>

namespace {

template <template <typename> class Object, physics::units::IsUnitSystem Units>
auto resolveCollisionImpl(Object<Units>& first, Object<Units>& second)
{
    using Length = typename Units::Length;

    physics::domain::PositionVector2D<Length> firstCenter {first.getCenter()};
    Length firstRadius {first.getRadius()};

    physics::domain::PositionVector2D<Length> secondCenter {second.getCenter()};
    Length secondRadius {second.getRadius()};

    Length distance {physics::domain::distance(firstCenter, secondCenter)};
    Length sumRadii {firstRadius + secondRadius};

    if(distance < sumRadii)
    {
        physics::domain::PositionVector2D<Length> normal {physics::domain::normalize(firstCenter - secondCenter)};
        Length penetration {sumRadii - distance};
        physics::domain::PositionVector2D<Length> correction {normal * (penetration / Length(2.0))};

        first.setCenter(firstCenter + correction);
        second.setCenter(secondCenter - correction);
    }
}

} // namespace

namespace physics::usecases
{

template <
    template <typename...> class Container,
    template <typename> class Object,
    physics::units::IsUnitSystem Units>
auto resolveCollisions(Container<Object<Units>>& particles)
{
    for(auto first {particles.begin()}; first != particles.end(); ++first)
    {
        for(auto second {std::next(first)}; second != particles.end(); ++second)
        {
            resolveCollisionImpl(*first, *second);
        }
    }

    return particles;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_EULER_COLLISION_HPP