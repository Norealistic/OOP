#include <iostream>
#include "ConsoleApp.hpp"

using namespace Dungeon;

int main(){
    bool flag = false;
    
    InitLevels();
    do{
        try{
            map_output(User.current_level);
            MakeStep(User);
        }
        catch (std::string error){
            std::cout << error << std::endl;
            flag = true;
        }
    }while(!flag);
    return 0;
}
