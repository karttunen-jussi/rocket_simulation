//---------------------------------------------------------------------------------------------------------------------
// Simulate rocket travelling into CSV data file for plotting
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
    constexpr double time_step_simulation_s = 1.0e-3;
    constexpr double time_total_length_s    = 100.0;

    // Rocket simulation data points are logged into this csv file
    std::ofstream csv_file{"rocket_sim_data_points.csv"};
    // Write signal name header row into the file
    csv_file << "Time[s]," << "Speed[m/s]," << "Distance[m]" << std::endl;

    // Create the instance of the rocket class
    Rocket_t rocket{
        {.time_step_simulation_s = 1.0e-3,
         .mass_rocket_kg         = 1000.0}
    };

    // Set the value for speed used in the simulation
    constexpr double speed_rocket_m_s = 10.0;
    rocket.SetSpeed_m_s(speed_rocket_m_s);

    // Rocket travelling simulation loop
    double time_elapsed_s = 0.0;
    while (time_elapsed_s <= time_total_length_s)
    {
        // Update travelled distance of the rocket at every time step
        rocket.UpdateDistance_m();

        // Write the data points into the file
        csv_file << time_elapsed_s << "," << speed_rocket_m_s << "," << rocket.GetDistance_m() << std::endl;

        // Increment elapsed time forward
        time_elapsed_s += time_step_simulation_s;
    }

    // Remember to close the file handle when done
    csv_file.close();
    return 0;
}
