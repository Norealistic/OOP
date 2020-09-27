#pragma once
#include <math.h>
#include <sstream>

namespace NS2 {

    class Strophoid{
    private:
        double a;
    public:
     Strophoid();
     Strophoid(double a);
     Strophoid& Set_a(double a);
     double Get_a() const;
     double Get_y_coordinate(double x) const;
     double Get_polar_distance(double t) const;
     double Get_Curvature_radius() const;
     double Get_Loop_square() const;
     double Get_Volume() const;
     double Get_Asymptote_square() const;
    };
}
