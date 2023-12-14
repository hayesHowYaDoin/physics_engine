
#include "example/example.hpp"

#include <gtest/gtest.h>

TEST(ToggleTest, ToggleTrueToFalse)
{
    example::Toggler toggler { true };

    EXPECT_FALSE(toggler.toggle());
}

TEST(ToggleTest, ToggleFalseToTrue)
{
    example::Toggler toggler { false };

    EXPECT_TRUE(toggler.toggle());
}
