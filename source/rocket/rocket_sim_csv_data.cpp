//---------------------------------------------------------------------------------------------------------------------
// Simulate rocket movement data into csv file for plotting
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "rocket.hpp"

#include "utility/command_sequence.hpp"
#include "utility/sim_scheduler.hpp"

#include <fstream>

//---------------------------------------------------------------------------------------------------------------------
// EXECUTABLE MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    // Parameters for the creating the simulation data
    constexpr double time_step_s         = 1.0e-3;
    constexpr double time_total_length_s = 160.0;
    constexpr double mass_rocket_kg      = 1000.0;
    constexpr double position_limit_m    = 1.0e6;

    // Rocket simulation data points are logged into this csv file
    std::ofstream csv_file{"rocket_sim_data_points.csv"};

    // Write signal name header row into the file
    csv_file << "Time[s],"
             << "Speed_x[m/s],"
             << "Speed_y[m/s],"
             << "Position_x[m],"
             << "Position_y[m]\n";

    // Define power input command sequence for the rocket
    CommandGenerator_t power_sequence_x_axis_kw{
        {{.time_s = 0.00, .value = 10.0},
         {.time_s = 10.0, .value = -10.0},
         {.time_s = 20.0, .value = 0.0},
         {.time_s = 40.0, .value = -10.0},
         {.time_s = 50.0, .value = 10.0},
         {.time_s = 60.0, .value = 0.0},
         {.time_s = 80.0, .value = 0.0}}
    };

    CommandGenerator_t power_sequence_y_axis_kw{
        {{.time_s = 0.00, .value = 0.0},
         {.time_s = 20.0, .value = 10.0},
         {.time_s = 30.0, .value = -10.0},
         {.time_s = 40.0, .value = 0.0},
         {.time_s = 60.0, .value = -10.0},
         {.time_s = 70.0, .value = 10.0},
         {.time_s = 80.0, .value = 0.0}}
    };

    // Create the instance of the rocket class
    Rocket_t rocket{
        {.time_step_s      = time_step_s,
         .mass_rocket_kg   = mass_rocket_kg,
         .position_limit_m = position_limit_m}
    };

    // Define the simulation loop function
    auto SimLoopFunc = [&](const double time_elapsed_s) // NOLINT(*identifier-naming)
    {
        // Update position of the rocket at every time step
        const XyVector_t power_kW = {.x_axis = power_sequence_x_axis_kw.GetCommand(time_elapsed_s),
                                     .y_axis = power_sequence_y_axis_kw.GetCommand(time_elapsed_s)};

        rocket.UpdateState(power_kW);

        const XyVector_t position_m = rocket.GetPosition_m();
        const XyVector_t speed_m_s  = rocket.GetSpeed_m_s();

        // Write the data points into the csv file
        csv_file << time_elapsed_s << ","
                 << speed_m_s.x_axis << ","
                 << speed_m_s.y_axis << ","
                 << position_m.x_axis << ","
                 << position_m.y_axis << "\n";
    };

    // Create scheduler and run the simulation
    SimScheduler_t scheduler{time_step_s, SimLoopFunc};
    scheduler.RunSimulation(time_total_length_s);

    // Remember to close the file handle when done
    csv_file.close();
    return 0;
}
