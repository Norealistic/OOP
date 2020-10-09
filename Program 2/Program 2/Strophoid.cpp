#include <stdio.h>
#include "Strophoid.h"

namespace NS2{

    Strophoid::Strophoid() {
        this->a = 0;
    }

    Strophoid::Strophoid(double a){
        Set_a(a);
    }
    
    Strophoid& Strophoid::Set_a(double a){
        if (a < 0) {
            throw "A should be a non-negative number!";
        }
        this->a = a;
        return *this;
    }
    
    double Strophoid::Get_a() const{
        return a;
    }

    double Strophoid::Get_y_coordinate(double x) const{
        return (x * sqrt( (a + x) / (a - x) ) );
    }

    double Strophoid::Get_polar_distance(double t) const{
        t = t * M_PI / 180;
        return ((-a * cos(2 * t)) / (cos(t)));
    }

    double Strophoid::Get_Curvature_radius() const{
        return (a * sqrt(2));
    }

    double Strophoid::Get_Loop_square() const{
        return (pow(a, 2) * (2.0 - M_PI / 2.0));
    }
    
    double Strophoid::Get_Volume() const{
        return (pow(a, 3) * M_PI * (2 * log(2) - 4/3));
    }

    double Strophoid::Get_Asymptote_square() const{
        return (pow(a, 2) * (2.0 + M_PI / 2.0));
    }

}


