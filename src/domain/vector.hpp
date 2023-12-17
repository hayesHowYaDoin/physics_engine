#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "domain/degrees.hpp"
#include "domain/magnitude.hpp"

struct PhysicsVector {
    Magnitude magnitude;
    AngleDegrees direction;

    operator +(const PhysicsVector<T>& other) const {
        return PhysicsVector<T>{magnitude + other.magnitude, direction};
    }
};

#endif // VECTOR_HPP
