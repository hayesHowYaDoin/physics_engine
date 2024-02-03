// #ifndef EULER_H_
// #define EULER_H_

// #include <string>
// #include <units.h>

// namespace physics_backend::euler::si
// {
//     struct EulerParticle;

//     using Mass = units::mass::kilograms<double>;
//     using Position = units::length::meters<double>;
//     using Velocity = units::velocity::meters_per_second<double>;
//     using Force = units::force::newtons<double>;

//     using Particle = EulerParticle<Mass, Position, Velocity, Force>;

//     Particle buildParticle(float mass, float x, float y, float vx, float vy)
//     {
//         return Particle(Mass(mass), Position(x), Position(y), Velocity(vx), Velocity(vy));
//     }

// } // namespace physics_backend::euler::si

// #endif // EULER_H_