#include <iostream>
#include "ConsoleApp.hpp"
#include <fstream>

using namespace Dungeon;

Player user;
square map_catalog1[3]; 

const couple start_point = {0, 8};//для простоты определена одна и та же точка начала уровня

struct PlayerStatement User = {user, start_point, LEVEL_1};
std::vector <CatacombsLevel> level_list;
std::vector <std::vector <struct EnemyStatement>> Level_enemies(3);
std::ofstream fout;
std::ifstream fin;


int main(){
    fin.open("/Users/nikita_gal/Desktop/OOP/Dungeon/Dungeon/map.txt");
    square map;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < LINE_QUANTITY; j++){
            fin >> map.lines[j];
        }
        map_catalog1[i] = map;
    }
    fin.close();
    for (int i = 1; i <= 3; i++){
            CatacombsLevel level(i);
            level_list.push_back(level);
        }
        bool flag = false;
        InitLevels(User.current_level, map_catalog[0], level_list);
        UploadCharacters(User, User.current_level, map_catalog[0], level_list, Level_enemies);
        for (int i = 0; i < 3; i++){
            do{
                Output(map_catalog[i]);
                flag = MakeStep(User, map_catalog[i], level_list, Level_enemies);
            }while(!flag);
            if (flag) break;
        }
        return 0;
    }
