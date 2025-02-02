#include <catch2/catch_all.hpp>

#include "box_volume.hpp"

using namespace Catch::Matchers;

TEST_CASE("Box volume calculation")
{
    SECTION("Recommended approach using Designated Initializers feature to give function arguments")
    {
        constexpr double length = 1.0;
        constexpr double width  = 2.0;
        constexpr double height = 3.0;

        const double volume = CalcBoxVolume({.length = length,
                                             .width  = width,
                                             .height = height});

        constexpr double expected_volume = length * width * height;
        constexpr double error_margin    = 1.0e-6;

        REQUIRE_THAT(volume, WithinAbs(expected_volume, error_margin));
    }

    SECTION("Standard approach to give function arguments")
    {
        constexpr double length = 1.0;
        constexpr double width  = 2.0;
        constexpr double height = 3.0;

        const double volume = CalcBoxVolume(length, width, height);

        constexpr double expected_volume = length * width * height;
        constexpr double error_margin    = 1.0e-6;

        REQUIRE_THAT(volume, WithinAbs(expected_volume, error_margin));
    }

    SECTION("NOT recommended magic number approach")
    {
        const double volume = CalcBoxVolume(1.0, 2.0, 3.0);

        constexpr double expected_volume = 6.0;
        constexpr double error_margin    = 1.0e-6;

        REQUIRE_THAT(volume, WithinAbs(expected_volume, error_margin));
    }
}
