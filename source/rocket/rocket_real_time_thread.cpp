//---------------------------------------------------------------------------------------------------------------------
// Execute rocket movement simulation in real-time thread
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "rocket.hpp"

#include <chrono>
#include <thread>

//---------------------------------------------------------------------------------------------------------------------
// EXECUTABLE MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    constexpr double time_step_s    = 1.0e-3;
    constexpr double mass_rocket_kg = 1000.0;

    // Create the instance of the rocket class
    Rocket_t rocket{
        {.time_step_s    = time_step_s,
         .mass_rocket_kg = mass_rocket_kg}
    };

    // Define the execution loop function
    auto PeriodicThreadFunc = [&]() // NOLINT(*identifier-naming)
    {
        // Update position of the rocket at every time step
        const XyVector_t power_kW = {.x_axis = 10.0,
                                     .y_axis = 10.0};

        rocket.UpdateState(power_kW);

        const XyVector_t position_m = rocket.GetPosition_m();
        (void)position_m;
    };

    // Infinite loop for the periodic task (20ms period)
    auto time_point_next_period = std::chrono::steady_clock::now();
    while (true)
    {
        PeriodicThreadFunc();

        // Send latest position using Web Socket

        // Yield execution of this thread until the next periodic time point.
        // The method below will eliminate thread's own execution time affecting
        // the period, thus allowing more accurate interval for the periodic task.
        using std::chrono::operator""ms;
        time_point_next_period += 20ms;
        std::this_thread::sleep_until(time_point_next_period);
    }
}
