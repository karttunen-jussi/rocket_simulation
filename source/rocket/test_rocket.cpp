//---------------------------------------------------------------------------------------------------------------------
// Rocket class test cases
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "rocket.hpp"
#include "utility/sim_scheduler.hpp"
#include <catch2/catch_all.hpp>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE (STATIC) FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

using namespace Catch::Matchers;

static auto Near(const double expected_value)
{
    constexpr double allowed_error_tolerance = 1.0e-2;
    return WithinAbs(expected_value, allowed_error_tolerance);
}

//---------------------------------------------------------------------------------------------------------------------
// TEST CASE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

TEST_CASE("Rocket traveled distance")
{
    SECTION("With constant speed")
    {
        constexpr double time_step_s     = 1.0e-3;
        constexpr double time_interval_s = 100.0;

        constexpr double speed_rocket_m_s = 10.0;

        Rocket_t rocket{
            {.time_step_simulation_s = time_step_s,
             .mass_rocket_kg         = 1000.0}
        };

        rocket.SetSpeed_m_s(speed_rocket_m_s);

        SimScheduler_t scheduler{time_step_s, std::bind(&Rocket_t::UpdateDistance_m, &rocket)};

        scheduler.RunSimulation(time_interval_s);

        constexpr double expected_distance_m = time_interval_s * speed_rocket_m_s;
        REQUIRE_THAT(rocket.GetDistance_m(), Near(expected_distance_m));
    }
}
