//---------------------------------------------------------------------------------------------------------------------
// Rocket
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "utility/numerical_integration.hpp"

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

struct RocketPars_t
{
    double time_step_simulation_s;
    double mass_rocket_kg;
};

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class Rocket_t
{
  public:
    Rocket_t(const RocketPars_t& pars) :
        m_mass_rocket_kg{pars.mass_rocket_kg},
        m_distance_m{pars.time_step_simulation_s}
    {}

    void SetSpeed_m_s(const double speed_m_s)
    {
        m_speed_m_s = speed_m_s;
    }

    double UpdateDistance_m()
    {
        // Distance is integral of speed
        m_distance_m.UpdateIntegral(m_speed_m_s);
        return m_distance_m.GetValue();
    }

    double GetDistance_m() const
    {
        return m_distance_m.GetValue();
    }

  private:
    double m_mass_rocket_kg;
    double m_acceleration_m_s2 = 0.0;
    double m_speed_m_s         = 0.0;
    Integrator_t m_distance_m;
};
