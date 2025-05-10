//---------------------------------------------------------------------------------------------------------------------
// Rocket class test cases
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "../rocket.hpp"
#include "utility/sim_scheduler.hpp"

#include <catch2/catch_all.hpp>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE (STATIC) FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

using namespace Catch::Matchers;

static auto Near(const double expected_value)
{
    constexpr double allowed_relative_error = 1.0e-3;
    return WithinRel(expected_value, allowed_relative_error);
}

// NOLINTNEXTLINE(*easily-swappable-parameters)
static constexpr double CalcEnergyWithConstPower_J(const double time_interval_s, const double power_kw)
{
    const double power_W = power_kw * convert_kW_to_W;
    return time_interval_s * power_W;
}

// NOLINTNEXTLINE(*easily-swappable-parameters)
static constexpr double CalcKineticEnergy_J(const double mass_kg, const double speed_m_s)
{
    return 0.5 * mass_kg * std::pow(speed_m_s, 2.0);
}

// NOLINTNEXTLINE(*easily-swappable-parameters)
static double CalcSpeedWithConstPower_m_s(const double time_interval_s, const double power_kw, const double mass_kg)
{
    const double power_W = power_kw * convert_kW_to_W;
    return std::sqrt((2.0 * power_W * time_interval_s) / mass_kg);
}

// NOLINTNEXTLINE(*easily-swappable-parameters)
static double CalcPositionWithConstPower_m(const double time_interval_s, const double power_kw, const double mass_kg)
{
    const double power_W = power_kw * convert_kW_to_W;
    return std::sqrt((8.0 * power_W * std::pow(time_interval_s, 3.0)) / (9.0 * mass_kg));
}

//---------------------------------------------------------------------------------------------------------------------
// TEST CASE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

TEST_CASE("Accelerating rocket with constant power")
{
    constexpr double time_step_s       = 1.0e-3;
    constexpr double time_interval_s   = 10.0;
    constexpr double mass_rocket_kg    = 1000.0;
    constexpr double power_rocket_x_kW = 10.0;
    constexpr double power_rocket_y_kW = 5.0;
    constexpr double position_limit_m  = 1.0e6;

    SECTION("Kinetic energy")
    {
        Rocket_t rocket{
            {.time_step_s      = time_step_s,
             .mass_rocket_kg   = mass_rocket_kg,
             .position_limit_m = position_limit_m}
        };

        // Define the simulation loop function
        auto SimLoopFunc = [&rocket](const double time_elapsed_s) // NOLINT(*identifier-naming)
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
        constexpr double expected_energy_x_J = CalcEnergyWithConstPower_J(time_interval_s, power_rocket_x_kW);
        constexpr double expected_energy_y_J = CalcEnergyWithConstPower_J(time_interval_s, power_rocket_y_kW);

        // Actual kinetic energy: E = 0.5*m*v^2
        const double speed_x_m_s       = rocket.GetSpeed_m_s().x_axis;
        const double speed_y_m_s       = rocket.GetSpeed_m_s().y_axis;
        const double result_energy_x_J = CalcKineticEnergy_J(mass_rocket_kg, speed_x_m_s);
        const double result_energy_y_J = CalcKineticEnergy_J(mass_rocket_kg, speed_y_m_s);

        REQUIRE_THAT(result_energy_x_J, Near(expected_energy_x_J));
        REQUIRE_THAT(result_energy_y_J, Near(expected_energy_y_J));
    }

    SECTION("Speed")
    {
        Rocket_t rocket{
            {.time_step_s      = time_step_s,
             .mass_rocket_kg   = mass_rocket_kg,
             .position_limit_m = position_limit_m}
        };

        // Define the simulation loop function
        auto SimLoopFunc = [&rocket](const double time_elapsed_s) // NOLINT(*identifier-naming)
        {
            (void)time_elapsed_s;

            const XyVector_t power_kW = {.x_axis = power_rocket_x_kW,
                                         .y_axis = power_rocket_y_kW};

            rocket.UpdateState(power_kW);
        };

        // Create scheduler and run the simulation
        SimScheduler_t scheduler{time_step_s, SimLoopFunc};

        // Repeat the test in 10 steps forward checking result at each step
        for (int i = 0; i < 10; i++)
        {
            scheduler.RunSimulation(time_interval_s);

            // Actual speed of the rocket
            const double result_speed_x_m_s = rocket.GetSpeed_m_s().x_axis;
            const double result_speed_y_m_s = rocket.GetSpeed_m_s().y_axis;

            // Expected speed of the rocket
            const double time_elapsed_s       = time_interval_s * static_cast<double>(i + 1);
            const double expected_speed_x_m_s = CalcSpeedWithConstPower_m_s(time_elapsed_s, power_rocket_x_kW, mass_rocket_kg);
            const double expected_speed_y_m_s = CalcSpeedWithConstPower_m_s(time_elapsed_s, power_rocket_y_kW, mass_rocket_kg);

            REQUIRE_THAT(result_speed_x_m_s, Near(expected_speed_x_m_s));
            REQUIRE_THAT(result_speed_y_m_s, Near(expected_speed_y_m_s));
        }
    }

    SECTION("Position")
    {
        Rocket_t rocket{
            {.time_step_s      = time_step_s,
             .mass_rocket_kg   = mass_rocket_kg,
             .position_limit_m = position_limit_m}
        };

        // Define the simulation loop function
        auto SimLoopFunc = [&rocket](const double time_elapsed_s) // NOLINT(*identifier-naming)
        {
            (void)time_elapsed_s;

            const XyVector_t power_kW = {.x_axis = power_rocket_x_kW,
                                         .y_axis = power_rocket_y_kW};

            rocket.UpdateState(power_kW);
        };

        // Create scheduler and run the simulation
        SimScheduler_t scheduler{time_step_s, SimLoopFunc};

        // Repeat the test in 10 steps forward checking result at each step
        for (int i = 0; i < 10; i++)
        {
            scheduler.RunSimulation(time_interval_s);

            // Actual position of the rocket
            const double result_position_x_m = rocket.GetPosition_m().x_axis;
            const double result_position_y_m = rocket.GetPosition_m().y_axis;

            // Expected position of the rocket
            const double time_elapsed_s        = time_interval_s * static_cast<double>(i + 1);
            const double expected_position_x_m = CalcPositionWithConstPower_m(time_elapsed_s, power_rocket_x_kW, mass_rocket_kg);
            const double expected_position_y_m = CalcPositionWithConstPower_m(time_elapsed_s, power_rocket_y_kW, mass_rocket_kg);

            REQUIRE_THAT(result_position_x_m, Near(expected_position_x_m));
            REQUIRE_THAT(result_position_y_m, Near(expected_position_y_m));
        }
    }
}
