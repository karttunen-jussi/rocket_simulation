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
        m_x_axis{.speed_m_s{pars.time_step_s}, .position_m{pars.time_step_s}},
        m_y_axis{.speed_m_s{pars.time_step_s}, .position_m{pars.time_step_s}}
    {}

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
    void UpdateAxisState(const double power_kW, AxisState_t& axis)
    {
        // Limit the near zero speed values to prevent force approaching infinity near zero speeds.
        const double speed_abs_m_s     = std::abs(axis.speed_m_s.GetValue());
        const double speed_bounded_m_s = std::max(speed_abs_m_s, saturation_limit_division_near_zero);

        // Force is power divided by speed. Note that bounded speed is used in divider.
        const double force_N = (power_kW * convert_kW_to_W) / speed_bounded_m_s;

        // Acceleration is force divided by mass (because F = m*a)
        const double acceleration_m_s2 = force_N / m_mass_rocket_kg;

        // Speed is integral of acceleration
        axis.speed_m_s.UpdateIntegral(acceleration_m_s2);

        // Position is integral of speed
        axis.position_m.UpdateIntegral(axis.speed_m_s.GetValue());
    }

    double m_mass_rocket_kg;
    AxisState_t m_x_axis;
    AxisState_t m_y_axis;
};
