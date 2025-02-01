#include <cmath>
#include <fstream>
#include <numbers>

int main()
{
    // Parameters for the creating the sine wave data
    constexpr double time_step_s          = 1.0e-3;
    constexpr double time_data_duration_s = 3.0;
    constexpr double frequency_wave_hz    = 2.0;

    // Sine wave data points are logged into this csv file
    std::ofstream csv_file{"sine_wave_data_points.csv"};

    // Write signal name header row into the file
    csv_file << "Time[s]," << "Sine_wave" << std::endl;

    // Data point generation loop
    for (double time_elapsed_s = 0.0; time_elapsed_s <= time_data_duration_s; time_elapsed_s += time_step_s)
    {
        constexpr double angular_frequency_rad_s = 2.0f * std::numbers::pi * frequency_wave_hz;
        const double angle_rad                   = angular_frequency_rad_s * time_elapsed_s;
        const double sine_wave                   = std::sin(angle_rad);

        csv_file << time_elapsed_s << "," << sine_wave << std::endl;
    }

    // Remember to close the file handle when done
    csv_file.close();
    return 0;
}
