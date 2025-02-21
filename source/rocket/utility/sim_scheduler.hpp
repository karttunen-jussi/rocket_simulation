//---------------------------------------------------------------------------------------------------------------------
// Simulation test scheduler
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include <functional>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC (INLINE) FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

inline void RunSimulation(const double time_step_s,
                          const double time_interval_s,
                          const std::function<void()>& loop_function)
{
    double time_elapsed_s = 0.0;
    while (time_elapsed_s <= time_interval_s)
    {
        loop_function();
        time_elapsed_s += time_step_s;
    }
}

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class SimScheduler_t
{
  public:
    SimScheduler_t(const double time_step_s,
                   const std::function<void()>& loop_function) :
        m_time_step_s{time_step_s},
        m_loop_function{loop_function}
    {}

    void RunSimulation(const double time_interval_s)
    {
        double time_elapsed_s = 0.0;
        while (time_elapsed_s <= time_interval_s)
        {
            m_loop_function();
            time_elapsed_s += m_time_step_s;
        }
    }

  private:
    double m_time_step_s;
    std::function<void()> m_loop_function;
};
