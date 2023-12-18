#include "domain/magnitude.hpp"

#include <gtest/gtest.h>

TEST(MagnitudeTest, ConstructorPositiveValue)
{
    float value = 5.0f;
    domain::Magnitude magnitude(5.0f);

    EXPECT_FLOAT_EQ(magnitude(), value);
}

TEST(MagnitudeTest, ConstructorNegativeValue)
{
    float value = -5.0f;
    EXPECT_THROW(domain::Magnitude magnitude(value), std::invalid_argument);
}

TEST(MagnitudeTest, AdditionOperator)
{
    domain::Magnitude magnitude1(5.0f);
    domain::Magnitude magnitude2(3.0f);
    domain::Magnitude result = magnitude1 + magnitude2;

    EXPECT_FLOAT_EQ(result(), 8.0f);
}

TEST(MagnitudeTest, SubtractionOperator)
{
    domain::Magnitude magnitude1(5.0f);
    domain::Magnitude magnitude2(3.0f);
    domain::Magnitude result = magnitude1 - magnitude2;

    EXPECT_FLOAT_EQ(result(), 2.0f);
}

TEST(MagnitudeTest, MultiplicationOperator)
{
    domain::Magnitude magnitude1(5.0f);
    domain::Magnitude magnitude2(3.0f);
    domain::Magnitude result = magnitude1 * magnitude2;

    EXPECT_FLOAT_EQ(result(), 15.0f);
}

TEST(MagnitudeTest, DivisionOperator)
{
    domain::Magnitude magnitude1(6.0f);
    domain::Magnitude magnitude2(2.0f);
    domain::Magnitude result = magnitude1 / magnitude2;

    EXPECT_FLOAT_EQ(result(), 3.0f);
}

TEST(MagnitudeTest, UserDefinedLiteral)
{
    using namespace domain::literals;
    
    domain::Magnitude magnitude = 5.0_mag;
    EXPECT_FLOAT_EQ(magnitude(), 5.0f);
}
