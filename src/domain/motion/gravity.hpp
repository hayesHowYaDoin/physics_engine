#ifndef DOMAIN_MOTION_HPP
#define DOMAIN_MOTION_HPP

#include "domain/core/vector.hpp"


namespace domain::motion
{

PhysicsVector forceGravity(float mass, float gravity)
{
    return PhysicsVector(mass * gravity, Angle::fromDegrees(-90.0f));
}

}

#endif // DOMAIN_MOTION_HPP