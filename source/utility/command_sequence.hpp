//---------------------------------------------------------------------------------------------------------------------
// Command sequence generator
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include <cmath>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

struct CommandPoint_t
{
    double time_s;
    double value;
};

using CommandSequence_t = std::vector<CommandPoint_t>;

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class CommandGenerator_t
{
  public:
    CommandGenerator_t(const CommandSequence_t& command_sequence) :
        m_command_sequence{command_sequence}
    {
        const CommandPoint_t last_command_point = command_sequence.back();
        m_time_last_command_point_s             = last_command_point.time_s;
    }

    // Will return the latest command sequence value when called in addition to updating the command sequence with the elapsed time
    double GetCommand(const double time_elapsed_s)
    {
        // Wrap time back to zero if the simulation is longer than the defined load command sequence's end point time.
        // This makes the command sequence to loop in repeat from the start when elapsed time exceeds command sequence's total length of time.
        const double time_elapsed_wrapped_s = fmod(time_elapsed_s, m_time_last_command_point_s);

        // The value that is applied is the last point in the command sequence where the elapsed time is greater than time instant of the point.
        // If the load command sequence does not start from zero time, zero value is returned until elapsed time reaches the first time point.
        CommandPoint_t present_command_point{};
        for (const auto& loop_point : m_command_sequence)
        {
            if (time_elapsed_wrapped_s >= loop_point.time_s)
            {
                present_command_point = loop_point;
            }
            else
            {
                break;
            }
        }

        return present_command_point.value;
    }

  private:
    double m_time_last_command_point_s;
    CommandSequence_t m_command_sequence;
};
