#ifndef DOMAIN_MOTION_HPP
#define DOMAIN_MOTION_HPP

#include "domain/core/vector.hpp"


namespace domain
{

namespace motion
{
    PhysicsVector forceGravity(float mass, float gravity);
}

}

#endif // DOMAIN_MOTION_HPP