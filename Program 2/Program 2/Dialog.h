#pragma once

#include <iostream>

#include "Strophoid.h"
#include "util.h"

namespace NS2 {
    void Dialog(Strophoid& strophoid);
    void Menu();
    void Set_a(Strophoid& strophoid);
    void Get_a(Strophoid& strophoid);
    void Get_y_coordinate(Strophoid& strophoid);
    void Get_polar_distance(Strophoid& strophoid);
    void Get_Curvature_radius(Strophoid& strophoid);
    void Get_Loop_square(Strophoid& strophoid);
    void Get_Volume(Strophoid& strophoid);
    void Get_Asymptote_square(Strophoid& strophoid);
}
