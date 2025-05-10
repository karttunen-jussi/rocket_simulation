//---------------------------------------------------------------------------------------------------------------------
// Numerical integration utility for simulation calculations
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class Integrator_t
{
  public:
    explicit Integrator_t(const double time_step_s) :
        m_time_step_s{time_step_s}
    {}

    double UpdateIntegral(const double input)
    {
        // Use Trapezoidal rule for the numerical integration
        m_integrated_result += m_time_step_s * (input + m_previous_input) * 0.5;
        m_previous_input     = input;
        return m_integrated_result;
    }

    double GetValue() const
    {
        return m_integrated_result;
    }

    void SetValue(const double modified_integral_value)
    {
        m_integrated_result = modified_integral_value;
    }

  private:
    double m_time_step_s;
    double m_integrated_result = 0.0;
    double m_previous_input    = 0.0;
};
