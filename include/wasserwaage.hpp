#ifndef WASSERWAAGE_HPP
#define WASSERWAAGE_HPP

#include <config.hpp>
#include <cmath>

class Vector3D
{
public:
    double x, y, z;

    Vector3D(double x, double y, double z);

    void get(double x, double y, double z);

    double magnitude() const;

    double angleWithX() const;

    double angleWithY() const;

    double angleWithZ() const;
};

void Wasserwaage_Init();
void Wasserwaage_Run();
void Wasserwaage_Reset();

#endif