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
    constexpr double allowed_relative_error = 1.0e-4;
    return WithinRel(expected_value, allowed_relative_error);
}

//---------------------------------------------------------------------------------------------------------------------
// TEST CASE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

TEST_CASE("Rocket kinetic energy")
{
    SECTION("With constant power")
    {
        constexpr double time_step_s       = 1.0e-3;
        constexpr double time_interval_s   = 100.0;
        constexpr double mass_rocket_kg    = 1000.0;
        constexpr double power_rocket_x_kW = 10.0;
        constexpr double power_rocket_y_kW = 5.0;

        Rocket_t rocket{
            {.time_step_s    = time_step_s,
             .mass_rocket_kg = mass_rocket_kg}
        };

        // Define the simulation loop function
        auto SimLoopFunc = [&rocket](const double time_elapsed_s)
        {
            (void)time_elapsed_s;

            const XyVector_t power_kW = {.x_axis = power_rocket_x_kW,
                                         .y_axis = power_rocket_y_kW};

            rocket.UpdateState(power_kW);
        };

        // Create scheduler and run the simulation
        SimScheduler_t scheduler{time_step_s, SimLoopFunc};
        scheduler.RunSimulation(time_interval_s);

        // Expected kinetic energy of the rocket with constant power should be E = P*t
        constexpr double expected_energy_x_J = time_interval_s * power_rocket_x_kW * convert_kW_to_W;
        constexpr double expected_energy_y_J = time_interval_s * power_rocket_y_kW * convert_kW_to_W;

        // Actual kinetic energy: E = 0.5*m*v^2
        const double speed_x_m_s       = rocket.GetSpeed_m_s().x_axis;
        const double speed_y_m_s       = rocket.GetSpeed_m_s().y_axis;
        const double result_energy_x_J = 0.5 * mass_rocket_kg * std::pow(speed_x_m_s, 2.0);
        const double result_energy_y_J = 0.5 * mass_rocket_kg * std::pow(speed_y_m_s, 2.0);

        REQUIRE_THAT(result_energy_x_J, Near(expected_energy_x_J));
        REQUIRE_THAT(result_energy_y_J, Near(expected_energy_y_J));
    }
}
