//---------------------------------------------------------------------------------------------------------------------
// Rocket
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "utility/numerical_integration.hpp"

#include <algorithm>
#include <cmath>

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC (INLINE) CONSTANT DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

inline constexpr double convert_kW_to_W = 1000.0;

// Converting power to force requires diving by speed. Speed values smaller than this limit are saturated 
// to prevent force approaching infinity near zero speeds.
inline constexpr double saturation_limit_division_near_zero = 0.1;

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

struct RocketPars_t
{
    double time_step_s;
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
        m_speed_m_s{pars.time_step_s},
        m_position_m{pars.time_step_s}
    {}

    void UpdateState(const double power_kW)
    {
        // Limit the near zero speed values to prevent force approaching infinity near zero speeds. 
        const double speed_abs_m_s     = std::abs(m_speed_m_s.GetValue());
        const double speed_bounded_m_s = std::max(speed_abs_m_s, saturation_limit_division_near_zero);

        // Force is power divided by speed. Note that bounded speed is used in divider.
        m_force_N = (power_kW * convert_kW_to_W) / speed_bounded_m_s;

        // Acceleration is force divided by mass (because F = m*a)
        m_acceleration_m_s2 = m_force_N / m_mass_rocket_kg;

        // Speed is integral of acceleration
        m_speed_m_s.UpdateIntegral(m_acceleration_m_s2);

        // Position is integral of speed
        m_position_m.UpdateIntegral(m_speed_m_s.GetValue());
    }

    double GetPosition_m() const
    {
        return m_position_m.GetValue();
    }

    double GetSpeed_m_s() const
    {
        return m_speed_m_s.GetValue();
    }

    double GetAcceleration_m_s2() const
    {
        return m_acceleration_m_s2;
    }

    double GetForce_N() const
    {
        return m_force_N;
    }

  private:
    double m_mass_rocket_kg;
    double m_force_N           = 0.0;
    double m_acceleration_m_s2 = 0.0;
    Integrator_t m_speed_m_s;
    Integrator_t m_position_m;
};
