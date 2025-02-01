#include <cmath>
#include <fstream>
#include <numbers>

int main()
{
    // Parameters for the creating the sine wave data
    constexpr double time_step_s         = 1.0e-3;
    constexpr double time_total_length_s = 3.0;
    constexpr double frequency_wave_hz   = 2.0;

    // Sine wave data points are logged into this csv file
    std::ofstream csv_file{"sine_wave_data_points.csv"};

    // Write signal name header row into the file
    csv_file << "Time[s]," << "Sine_wave" << std::endl;

    // Data point generation loop
    double time_elapsed_s = 0.0;
    while (time_elapsed_s <= time_total_length_s)
    {
        constexpr double angular_frequency_rad_s = 2.0 * std::numbers::pi * frequency_wave_hz;
        const double angle_rad                   = angular_frequency_rad_s * time_elapsed_s;
        const double sine_wave                   = std::sin(angle_rad);

        // Write the data points into the file
        csv_file << time_elapsed_s << "," << sine_wave << std::endl;

        // Increment the elapsed time as a last action in the loop instead of first,
        // to not skip the initial time is zero (=0.0) step
        time_elapsed_s += time_step_s;
    }

    // Remember to close the file handle when done
    csv_file.close();
    return 0;
}
