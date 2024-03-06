#ifndef PHYSICS_BACKEND_USECASES_EULER_COLLISION_HPP
#define PHYSICS_BACKEND_USECASES_EULER_COLLISION_HPP

#include "physics_backend/units.hpp"
#include "physics_backend/domain/geometry.hpp"
#include "physics_backend/usecases/objects.hpp"

#include <algorithm>
#include <ranges>
#include <functional>

namespace {

template <template <typename> class Object, physics::units::IsUnitSystem Units>
auto resolveCollisionImpl(Object<Units>& first, Object<Units>& second)
{
    auto firstCenter {first.getCenter()};
    auto firstRadius {first.getRadius()};

    auto secondCenter {second.getCenter()};
    auto secondRadius {second.getRadius()};

    auto distance {physics::domain::distance(firstCenter, secondCenter)};
    auto sumRadii {firstRadius + secondRadius};

    if(distance < sumRadii)
    {
        auto normal {physics::domain::normalize(firstCenter - secondCenter)};
        auto penetration {sumRadii - distance};
        auto correction {normal * penetration / 2.0};

        first.setCenter(firstCenter + correction);
        second.setCenter(secondCenter - correction);
    }
}

} // namespace

namespace physics::usecases
{

template <std::ranges::range Range>
auto resolveCollisions(Range&& objects)
{
    auto view = objects | std::views::transform([](auto const& p) { return std::ref(p); });

    for(auto first {view.begin()}; first != view.end(); ++first)
    {
        for(auto second {std::next(first)}; second != view.end(); ++second)
        {
            resolveCollisionImpl(*first, *second);
        }
    }

    return view;
}

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_EULER_COLLISION_HPP