#pragma once

struct BoxDimensions_t
{
    double length = 0.0;
    double width  = 0.0;
    double height = 0.0;
};

inline double CalcBoxVolume(const BoxDimensions_t& dimensions)
{
    const double volume = dimensions.length * dimensions.width * dimensions.height;
    return volume;
}

inline double CalcBoxVolume(const double length, const double width, const double height)
{
    const double volume = length * width * height;
    return volume;
}
