#ifndef PHYSICS_BACKEND_UNITS_UNITS_HPP
#define PHYSICS_BACKEND_UNITS_UNITS_HPP

#include <units.h>

namespace physics::units
{

inline namespace lib { using namespace ::units; }   // Include the entire units library.

template <typename T>
concept IsUnitSystem = requires
{
    typename T::Mass;
    typename T::Length;
    typename T::Velocity;
    typename T::Acceleration;
    typename T::Force;
};

struct SI
{
    using Mass = mass::kilograms<double>;
    using Length = length::meters<double>;
    using Velocity = velocity::meters_per_second<double>;
    using Acceleration = acceleration::meters_per_second_squared<double>;
    using Force = force::newtons<double>;
};

struct Imperial
{
    using Mass = mass::pounds<double>;
    using Length = length::feet<double>;
    using Velocity = velocity::feet_per_second<double>;
    using Acceleration = acceleration::feet_per_second_squared<double>;
    using Force = force::pounds<double>;
};

template<typename UnitType>
concept IsUnit = traits::is_unit_v<UnitType>;

template<typename UnitType>
concept IsNumberType = std::is_arithmetic_v<UnitType>;

template<typename UnitType>
concept IsAreaUnit = traits::is_area_unit_v<UnitType>;

template<typename UnitType>
concept IsLengthUnit = traits::is_length_unit_v<UnitType>;

template<typename UnitType>
concept IsVolumeUnit = traits::is_volume_unit_v<UnitType>;

template<typename UnitType>
concept IsMassUnit = traits::is_mass_unit_v<UnitType>;

template<typename UnitType>
concept IsTimeUnit = traits::is_time_unit_v<UnitType>;

template<typename UnitType>
concept IsVelocityUnit = traits::is_velocity_unit_v<UnitType>;

template<typename UnitType>
concept IsAccelerationUnit = traits::is_acceleration_unit_v<UnitType>;

template<typename UnitType>
concept IsForceUnit = traits::is_force_unit_v<UnitType>;

template<typename UnitType>
concept IsAngleUnit = traits::is_angle_unit_v<UnitType>;

template<typename UnitType>
concept IsMagnitudeUnit = traits::is_length_unit_v<UnitType> ||
                          traits::is_force_unit_v<UnitType> ||
                          traits::is_velocity_unit_v<UnitType> ||
                          traits::is_acceleration_unit_v<UnitType>;

} // namespace physics::units


#endif // PHYSICS_BACKEND_UNITS_UNITS_HPP