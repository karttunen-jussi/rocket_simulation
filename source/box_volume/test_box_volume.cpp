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

    SECTION("Alternative ways to set values to struct")
    {
        constexpr BoxDimensions_t dimensions1 = {.length = 1.0, .width = 2.0, .height = 3.0};

        constexpr BoxDimensions_t dimensions2 = {1.0, 2.0, 3.0};

        BoxDimensions_t dimensions3;
        dimensions3.length = 1.0;
        dimensions3.width  = 2.0;
        dimensions3.height = 3.0;

        const double volume1 = CalcBoxVolume(dimensions1);
        const double volume2 = CalcBoxVolume(dimensions2);
        const double volume3 = CalcBoxVolume(dimensions3);

        constexpr double error_margin = 1.0e-6;
        REQUIRE_THAT(volume1, WithinAbs(volume2, error_margin));
        REQUIRE_THAT(volume2, WithinAbs(volume3, error_margin));
    }
}
