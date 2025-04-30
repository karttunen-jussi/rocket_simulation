//---------------------------------------------------------------------------------------------------------------------
// Simulation test scheduler
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include <functional>
#include <utility>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

using SimLoopFunc_t = std::function<void(const double)>;

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class SimScheduler_t
{
  public:
    SimScheduler_t(const double time_step_s,
                   SimLoopFunc_t SimLoopFunc) : // NOLINT(*identifier-naming)
        m_time_step_s{time_step_s},
        m_SimLoopFunc{std::move(SimLoopFunc)}
    {}

    void RunSimulation(const double time_interval_s)
    {
        double time_elapsed_s = 0.0;
        while (time_elapsed_s <= time_interval_s)
        {
            m_SimLoopFunc(time_elapsed_s);
            time_elapsed_s += m_time_step_s;
        }
    }

  private:
    double m_time_step_s;
    std::function<void(const double)> m_SimLoopFunc; // NOLINT(*identifier-naming)
};
