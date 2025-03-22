#ifndef NIGHT_LIGHT_HPP
#define NIGHT_LIGHT_HPP

#include <config.hpp>

struct Acceleration
{
    double x;
    double y;
    double z;
    double x_old;
    double y_old;
    double z_old;
};

void NightLight_Init();
void NightLight_Run();
void NightLight_Reset();

#endif