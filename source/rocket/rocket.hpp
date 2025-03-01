//---------------------------------------------------------------------------------------------------------------------
// Rocket
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "utility/numerical_integration.hpp"

#include <algorithm>
#include <array>
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

struct XyVector_t
{
    double x_axis;
    double y_axis;
};

using DoubleArray_t     = std::array<double, 2>;
using IntegratorArray_t = std::array<Integrator_t, 2>;

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class Rocket_t
{
  public:
    Rocket_t(const RocketPars_t& pars) :
        m_mass_rocket_kg{pars.mass_rocket_kg},
        m_speed_m_s{{{pars.time_step_s}, {pars.time_step_s}}},
        m_position_m{{{pars.time_step_s}, {pars.time_step_s}}}
    {}

    void UpdateState(const XyVector_t& power_kW)
    {
        const DoubleArray_t power_array_kW = {power_kW.x_axis, power_kW.y_axis};

        for (unsigned int i = 0u; i < 2u; i++)
        {
            // Limit the near zero speed values to prevent force approaching infinity near zero speeds.
            const double speed_abs_m_s     = std::abs(m_speed_m_s[i].GetValue());
            const double speed_bounded_m_s = std::max(speed_abs_m_s, saturation_limit_division_near_zero);

            // Force is power divided by speed. Note that bounded speed is used in divider.
            const double force_N = (power_array_kW[i] * convert_kW_to_W) / speed_bounded_m_s;

            // Acceleration is force divided by mass (because F = m*a)
            const double acceleration_m_s2 = force_N / m_mass_rocket_kg;

            // Speed is integral of acceleration
            m_speed_m_s[i].UpdateIntegral(acceleration_m_s2);

            // Position is integral of speed
            m_position_m[i].UpdateIntegral(m_speed_m_s[i].GetValue());
        }
    }

    XyVector_t GetPosition_m() const
    {
        return {.x_axis = m_position_m[0].GetValue(),
                .y_axis = m_position_m[1].GetValue()};
    }

    XyVector_t GetSpeed_m_s() const
    {
        return {.x_axis = m_speed_m_s[0].GetValue(),
                .y_axis = m_speed_m_s[1].GetValue()};
    }

  private:
    double m_mass_rocket_kg;
    IntegratorArray_t m_speed_m_s;
    IntegratorArray_t m_position_m;
};
