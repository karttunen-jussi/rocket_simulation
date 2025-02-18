//---------------------------------------------------------------------------------------------------------------------
// Rocket class test cases
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "rocket.hpp"

#include <catch2/catch_all.hpp>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE (STATIC) FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

using namespace Catch::Matchers;

static auto Near(const double expected_value)
{
    constexpr double allowed_error_tolerance = 1.0e-3;
    return WithinAbs(expected_value, allowed_error_tolerance);
}

//---------------------------------------------------------------------------------------------------------------------
// TEST CASE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

TEST_CASE("Rocket traveled distance")
{
    SECTION("With constant speed")
    {
        constexpr double time_step_simulation_s = 1.0e-3;
        constexpr double time_total_length_s    = 100.0;

        constexpr double speed_rocket_m_s = 10.0;

        Rocket_t rocket{
            {.time_step_simulation_s = time_step_simulation_s,
             .mass_rocket_kg         = 1000.0}
        };

        rocket.SetSpeed_m_s(speed_rocket_m_s);

        // Rocket travelling simulation loop
        double time_elapsed_s = 0.0;
        while (time_elapsed_s <= time_total_length_s)
        {
            rocket.UpdateDistance_m();
            time_elapsed_s += time_step_simulation_s;
        }

        constexpr double expected_distance_m = time_total_length_s * speed_rocket_m_s;
        REQUIRE_THAT(rocket.GetDistance_m(), Near(expected_distance_m));
    }
}
