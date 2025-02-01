#include <catch2/catch_all.hpp>

using namespace Catch::Matchers;

TEST_CASE("Test case name")
{
    SECTION("Section name 1")
    {
        // Example how to check int and boolen values
        constexpr int result_int   = 1;
        constexpr int expected_int = 1;
        REQUIRE(result_int == expected_int);

        constexpr bool result_bool = true;
        REQUIRE(result_bool);

        constexpr bool result_bool_false = false;
        REQUIRE_FALSE(result_bool_false);
    }

    SECTION("Section name 2")
    {
        // Example how to check float and double values
        constexpr float result_float   = 1.0f;
        constexpr float expected_float = 1.0f;
        constexpr float error_margin   = 0.001f;
        REQUIRE_THAT(result_float, WithinAbs(expected_float, error_margin));
    }
}
