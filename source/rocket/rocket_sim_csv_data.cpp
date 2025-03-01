//---------------------------------------------------------------------------------------------------------------------
// Simulate rocket movement data into csv file for plotting
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "rocket.hpp"

#include <fstream>

//---------------------------------------------------------------------------------------------------------------------
// EXECUTABLE MAIN FUNCTION DEFINITION
//---------------------------------------------------------------------------------------------------------------------

int main()
{
    // Parameters for the creating the simulation data
    constexpr double time_step_s         = 1.0e-3;
    constexpr double time_total_length_s = 100.0;
    constexpr double mass_rocket_kg      = 1000.0;

    // Rocket simulation data points are logged into this csv file
    std::ofstream csv_file{"rocket_sim_data_points.csv"};

    // Write signal name header row into the file
    csv_file << "Time[s],"
             << "Speed_x[m/s],"
             << "Speed_y[m/s],"
             << "Position_x[m],"
             << "Position_y[m]"
             << std::endl;

    // Create the instance of the rocket class
    Rocket_t rocket{
        {.time_step_s    = time_step_s,
         .mass_rocket_kg = mass_rocket_kg}
    };

    // Rocket travelling simulation loop
    double time_elapsed_s = 0.0;
    while (time_elapsed_s <= time_total_length_s)
    {
        // Update position of the rocket at every time step
        const XyVector_t power_kW = {.x_axis = 10.0,
                                     .y_axis = 5.0};

        rocket.UpdateState(power_kW);

        const XyVector_t position_m = rocket.GetPosition_m();
        const XyVector_t speed_m_s  = rocket.GetSpeed_m_s();

        // Write the data points into the csv file
        csv_file << time_elapsed_s << ","
                 << speed_m_s.x_axis << ","
                 << speed_m_s.y_axis << ","
                 << position_m.x_axis << ","
                 << position_m.y_axis << std::endl;

        // Increment elapsed time forward
        time_elapsed_s += time_step_s;
    }

    // Remember to close the file handle when done
    csv_file.close();
    return 0;
}
