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
             << "Force[N],"
             << "Acceleration[m/s2],"
             << "Speed[m/s],"
             << "Position[m]"
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
        constexpr double power_kW = 10.0;
        rocket.UpdateState(power_kW);

        // Write the data points into the csv file
        csv_file << time_elapsed_s << ","
                 << rocket.GetForce_N() << ","
                 << rocket.GetAcceleration_m_s2() << ","
                 << rocket.GetSpeed_m_s() << ","
                 << rocket.GetPosition_m() << std::endl;

        // Increment elapsed time forward
        time_elapsed_s += time_step_s;
    }

    // Remember to close the file handle when done
    csv_file.close();
    return 0;
}
