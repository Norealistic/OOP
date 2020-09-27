#include <string.h>

#include "Dialog.h"

#define options_number 8

namespace NS2 {
    typedef void(*opt_t)(Strophoid&);

    static const opt_t options[options_number] = {
        &Set_a,
        &Get_a,
        &Get_y_coordinate,
        &Get_polar_distance,
        &Get_Curvature_radius,
        &Get_Loop_square,
        &Get_Volume,
        &Get_Asymptote_square
    };

    void Dialog(Strophoid& strophoid) {
        std::cout << "------------------------------------------------------------" << std::endl;
        while (true) {
            Menu();
            std::cout << "------------------------------------------------------------" << std::endl;
            int choice = 0;
            choice = getNum<int>("Your choice: ");
            std::cout << "------------------------------------------------------------" << std::endl;
            if (!choice) {
                break;
            }
            else if (choice < 0 || choice > options_number) {
                std::cout << "Invalid option detected!" << std::endl;
            }
            else {
                options[choice - 1](strophoid);
            }
            std::cout << "------------------------------------------------------------" << std::endl;
        }
    }

    void Menu() {
     std::cout <<
        "0. Quit" << std::endl <<
        "1. Set const a" << std::endl <<
        "2. Get const a" << std::endl <<
        "3. Get y coodrinate" << std::endl <<
        "4. Get polar distance" << std::endl <<
        "5. Get curvature radius" << std::endl <<
        "6. Get square of the loop" << std::endl <<
        "7. Get volume" << std::endl <<
        "8. Get square of the asymptote" << std::endl;
    }

    void Set_a(Strophoid& strophoid){
        double a = 0;
        a = getNum<double>("Enter the const a: ");
               try {
                   strophoid.Set_a(a);
               }
               catch (const char *error) {
                   std::cerr << error << std::endl;
               }
           }
    

    void Get_a(Strophoid& strophoid){
        std::cout << "Const a = " << strophoid.Get_a() << std::endl;
    }

    void Get_y_coordinate(Strophoid& strophoid){
        double x = 0;
        x = getNum<double>("Enter x coordinate: ");
        std::cout << "Y coodinate = " << strophoid.Get_y_coordinate(x) << std::endl;
    }


    void Get_polar_distance(Strophoid& strophoid){
        double t = 0;
        t = getNum<double>("Angle value in degrees: ");
        if (strophoid.Get_polar_distance(t) >= 0) {
            std::cout << "Polar distance = " << strophoid.Get_polar_distance(t) << std::endl;
        }
            else {
                 std::cout << "Polar distance = " << -strophoid.Get_polar_distance(t) << std::endl;
              }
    }
    
    void Get_Curvature_radius(Strophoid& strophoid){
         std::cout << "Curvature_radius = " << strophoid.Get_Curvature_radius() << std::endl;
    }

    void Get_Loop_square(Strophoid& strophoid){
         std::cout << "Loop square = " << strophoid.Get_Loop_square() << std::endl;
    }

    void Get_Volume(Strophoid& strophoid){
        std::cout << "Volume = " << strophoid.Get_Volume() << std::endl;
    }

    void Get_Asymptote_square(Strophoid& strophoid){
        std::cout << "Square between asymptote = " << strophoid.Get_Asymptote_square() << std::endl;
    }

}
