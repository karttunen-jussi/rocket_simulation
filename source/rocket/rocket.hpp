//---------------------------------------------------------------------------------------------------------------------
// Rocket
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

struct RocketPars_t
{
    double time_step_simulation_s = 0.0;
    double mass_rocket_kg         = 0.0;
};

struct RocketState_t
{
    double distance_m        = 0.0;
    double speed_m_s         = 0.0;
    double acceleration_m_s2 = 0.0;
};

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class Rocket_t
{
  public:
    Rocket_t(const RocketPars_t& pars) :
        m_pars{pars}
    {}

    void SetSpeed_m_s(const double speed_m_s)
    {
        m_state.speed_m_s = speed_m_s;
    }

    double UpdateDistance_m()
    {
        // Distance is integral of speed (s = ∫vdt)
        m_state.distance_m += m_state.speed_m_s * m_pars.time_step_simulation_s;
        return m_state.distance_m;
    }

    double GetDistance_m() const
    {
        return m_state.distance_m;
    }

  private:
    RocketPars_t m_pars;
    RocketState_t m_state = {};
};
