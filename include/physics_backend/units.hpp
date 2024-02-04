#ifndef PHYSICS_BACKEND_UNITS_H_
#define PHYSICS_BACKEND_UNITS_H_

#include <type_traits>

#include <units.h>

namespace physics_backend
{

template <typename T>
concept IsUnitSystem = requires {
    typename T::Mass;
    typename T::Length;
    typename T::Velocity;
    typename T::Acceleration;
    typename T::Force;
};

struct SI
{
    using Mass = units::mass::kilograms<double>;
    using Length = units::length::meters<double>;
    using Velocity = units::velocity::meters_per_second<double>;
    using Acceleration = units::acceleration::meters_per_second_squared<double>;
    using Force = units::force::newtons<double>;
};

struct Imperial
{
    using Mass = units::mass::pounds<double>;
    using Length = units::length::feet<double>;
    using Velocity = units::velocity::feet_per_second<double>;
    using Acceleration = units::acceleration::feet_per_second_squared<double>;
    using Force = units::force::pounds<double>;
};

} // namespace physics_backend

#endif // PHYSICS_BACKEND_UNITS_H_