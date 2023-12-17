#ifndef DOMAIN_DEGREES_HPP
#define DOMAIN_DEGREES_HPP

namespace domain
{

class AngleDegrees {
public:
    AngleDegrees(float value);

    float operator()() const;

    AngleDegrees operator+(const AngleDegrees& other) const;

    AngleDegrees operator-(const AngleDegrees& other) const;

private:
    float constrain(float value) const;

    float const m_value;
};

} // namespace domain

#endif // DOMAIN_DEGREES_HPP
