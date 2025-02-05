//---------------------------------------------------------------------------------------------------------------------
// Class and free function example with "Box"
//---------------------------------------------------------------------------------------------------------------------

#pragma once

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

struct BoxDimensions_t
{
    double length = 0.0;
    double width  = 0.0;
    double height = 0.0;
};

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC (INLINE) FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

inline double CalcBoxVolume(const double length, const double width, const double height)
{
    return length * width * height;
}

inline double CalcBoxVolume(const BoxDimensions_t& dimensions)
{
    return CalcBoxVolume(dimensions.length, dimensions.width, dimensions.height);
}

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC CLASS DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

class Box_t
{
  public:
    Box_t(const BoxDimensions_t& dimensions) :
        m_dimensions{dimensions}
    {}

    double GetVolume() const
    {
        return CalcBoxVolume(m_dimensions);
    }

    void SetLength(const double length)
    {
        m_dimensions.length = length;
    }

    void SetWidth(const double width)
    {
        m_dimensions.width = width;
    }

    void SetHeight(const double height)
    {
        m_dimensions.height = height;
    }

    void SetDimensions(const BoxDimensions_t& dimensions)
    {
        m_dimensions = dimensions;
    }

    void SetDimensions(const double length, const double width, const double height)
    {
        m_dimensions.length = length;
        m_dimensions.width  = width;
        m_dimensions.height = height;
    }

  private:
    BoxDimensions_t m_dimensions = {};
};
