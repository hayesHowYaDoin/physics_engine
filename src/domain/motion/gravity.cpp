#include "gravity.hpp"

namespace domain
{

namespace motion
{
    
    PhysicsVector forceGravity(float mass, float gravity)
    {
        return PhysicsVector(mass * gravity, Angle::fromDegrees(270.0f));
    }

} // namespace motion

} // namespace domain