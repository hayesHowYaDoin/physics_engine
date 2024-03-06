#ifndef PHYSICS_BACKEND_USECASES_OBJECTS_HPP
#define PHYSICS_BACKEND_USECASES_OBJECTS_HPP

namespace physics::usecases
{

template <typename T>
concept IsCircular = requires(T t)
{
    {t.getRadius()};
    {t.getCenter()};
};

} // namespace physics::usecases

#endif // PHYSICS_BACKEND_USECASES_OBJECTS_HPP