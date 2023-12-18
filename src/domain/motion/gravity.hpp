#ifndef DOMAIN_MOTION_HPP
#define DOMAIN_MOTION_HPP

#include "domain/core/vector.hpp"


namespace domain
{

namespace motion
{
    constexpr PhysicsVector forceGravity(float mass, float gravity)
    {
        return PhysicsVector(mass * gravity, Angle::fromDegrees(270.0f));
    }
}

}

#endif // DOMAIN_MOTION_HPP