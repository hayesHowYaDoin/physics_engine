#ifndef DOMAIN_MOTION_HPP
#define DOMAIN_MOTION_HPP

#include "domain/core/vector.hpp"


namespace domain::motion
{

Vector2D forceGravity(float mass, float gravity)
{
    return Vector2D(mass * gravity, Angle::fromDegrees(-90.0f));
}

}

#endif // DOMAIN_MOTION_HPP