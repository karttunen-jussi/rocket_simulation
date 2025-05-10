//---------------------------------------------------------------------------------------------------------------------
// Rocket
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

#include "utility/numerical_integration.hpp"

#include <algorithm>
#include <cassert>
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
    double position_limit_m;
};

struct XyVector_t
{
    double x_axis;
    double y_axis;
};

struct AxisState_t
{
    Integrator_t speed_m_s;
    Integrator_t position_m;
};

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class Rocket_t
{
  public:
    explicit Rocket_t(const RocketPars_t& pars) :
        m_mass_rocket_kg{pars.mass_rocket_kg},
        m_position_limit_m{pars.position_limit_m},
        m_x_axis{.speed_m_s{pars.time_step_s}, .position_m{pars.time_step_s}},
        m_y_axis{.speed_m_s{pars.time_step_s}, .position_m{pars.time_step_s}}
    {
        assert(pars.mass_rocket_kg > 0.0);
        assert(pars.position_limit_m > 0.0);
    }

    void UpdateState(const XyVector_t& power_kW)
    {
        UpdateAxisState(power_kW.x_axis, m_x_axis);
        UpdateAxisState(power_kW.y_axis, m_y_axis);
    }

    XyVector_t GetPosition_m() const
    {
        return {.x_axis = m_x_axis.position_m.GetValue(),
                .y_axis = m_y_axis.position_m.GetValue()};
    }

    XyVector_t GetSpeed_m_s() const
    {
        return {.x_axis = m_x_axis.speed_m_s.GetValue(),
                .y_axis = m_y_axis.speed_m_s.GetValue()};
    }

  private:
    void UpdateAxisState(const double power_kW, AxisState_t& axis) const
    {
        // Limit the near zero speed values to prevent force approaching infinity near zero speeds.
        const double speed_abs_m_s     = std::abs(axis.speed_m_s.GetValue());
        const double speed_bounded_m_s = std::max(speed_abs_m_s, saturation_limit_division_near_zero);

        // Force is power divided by speed. Note that bounded speed is used in divider.
        const double force_N = (power_kW * convert_kW_to_W) / speed_bounded_m_s;

        // Acceleration is force divided by mass (because F = m*a)
        const double acceleration_m_s2 = force_N / m_mass_rocket_kg;

        // Speed is integral of acceleration
        const double current_speed_m_s = axis.speed_m_s.UpdateIntegral(acceleration_m_s2);

        // Position is integral of speed
        const double current_position_m = axis.position_m.UpdateIntegral(current_speed_m_s);

        if (current_position_m > m_position_limit_m)
        {
            const double updated_position_m = current_position_m - m_position_limit_m;
            axis.position_m.SetValue(updated_position_m);
        }
        else if (current_position_m < 0.0)
        {
            const double updated_position_m = current_position_m + m_position_limit_m;
            axis.position_m.SetValue(updated_position_m);
        }
    }

    double m_mass_rocket_kg;
    double m_position_limit_m;
    AxisState_t m_x_axis;
    AxisState_t m_y_axis;
};
