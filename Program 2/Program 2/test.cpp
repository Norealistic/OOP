#include <math.h>

#include "gtest/gtest.h"

#include "Strophoid.h"

using namespace NS2;

TEST(Strophoid_Constructor, Default_Constructor){
    ASSERT_NO_THROW(Strophoid strophoid);
    Strophoid strophoid;
    ASSERT_EQ(0, strophoid.Get_a());
}

TEST(Strophoid_Constructor, Initial_Constructor){
    ASSERT_NO_THROW(Strophoid strophoid_1(4));
    Strophoid strophoid_1(4);
    ASSERT_EQ(4, strophoid_1.Get_a());
    ASSERT_ANY_THROW(Strophoid strophoid_1(-1));
}

TEST(Strophoid_Methods, Setter){
    Strophoid strophoid;
    ASSERT_NO_THROW(strophoid.Set_a(3));
    ASSERT_EQ(3, strophoid.Get_a());
}

TEST(Strophoid_Methods, Y_coord){
    Strophoid strophoid(6);
    ASSERT_EQ((2* sqrt((6 + 2) / (6 - 2))), strophoid.Get_y_coordinate(2));
}

TEST(Strophoid_Methods, Polar_distance){
    Strophoid strophoid(8);
    ASSERT_EQ((-8 * cos(2 * 30 * M_PI / 180)) / (cos(30 * M_PI / 180)), strophoid.Get_polar_distance(30));
}

TEST(Strophoid_Methods, Curvature_radius){
    Strophoid strophoid(2);
    ASSERT_EQ(2 * sqrt(2), strophoid.Get_Curvature_radius());
}

TEST(Strophoid_Methods, Get_Loop_square){
    Strophoid strophoid(6);
    ASSERT_EQ(pow(6, 2) * (2.0 - M_PI / 2.0), strophoid.Get_Loop_square());
}

TEST(Strophoid_Methods, Volume){
    Strophoid strophoid(3);
    ASSERT_EQ(pow(3, 3) * M_PI * (2 * log(2) - 4/3), strophoid.Get_Volume());
}

TEST(Strophoid_Methods, Asymptote_square){
    Strophoid strophoid(9);
    ASSERT_EQ(pow(9, 2) * (2.0 + M_PI / 2.0), strophoid.Get_Asymptote_square());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
