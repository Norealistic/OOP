#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Case.h"
#include "Maps.h"
#include <time.h>
#include <cmath>

namespace Dungeon{
     class CatacombsLevel{
        private:
            unsigned int level_number;
            std::vector <std::vector <Case>> case_array;
            couple size;
            Player *player;
            std::vector <Enemy> Enemies;
        public:
            CatacombsLevel(unsigned int level = 0);
            couple GetSize();
            TYPE GetPointType(couple& point){
                int x = point.x;
                int y = point.y;
                return case_array[x][y].GetType();
            }
            void SetPointType(couple& point, TYPE type, level_numbers level, Enemy *enemy){
               int x = point.x;
               int y = point.y;
               case_array[x][y].SetType(type);
               switch(type){
                   default: break;
                   case FLOOR:{
                       map_catalog[level].lines[x][y] = '.';
                       break;
                   }
                   case OPENED_DOOR:{
                       map_catalog[level].lines[x][y] = '/';
                       break;
                   }
                   case CLOSED_DOOR:{
                       map_catalog[level].lines[x][y] = '+';
                       break;
                   }
                   case WALL:{
                       map_catalog[level].lines[x][y] = '#';
                       break;
                   }
                   case STAIRS_UP:{
                       map_catalog[level].lines[x][y] = '<';
                       break;
                   }
                   case STAIRS_DOWN:{
                       map_catalog[level].lines[x][y] = '>';
                       break;
                   }
                   case PLAYER:{
                       map_catalog[level].lines[x][y] = '@';
                       break;
                   }
                   case ENEMY:{
                       char letter = 97 + (int)(enemy->GetName());
                       map_catalog[level].lines[x][y] = letter;
                       break;
                   }
               }
            };
            void SetLevel(level_numbers level);
            unsigned int GetLevel(){return level_number;};
            Player* GetPlayer();
            void SetPlayer(Player* player);
            std::vector <Enemy> GetEnemies();
            void SetEnemy(Enemy& enemy);
            void OpenDoor(couple& point);
            void CloseDoor(couple& point);
            void map_output(level_numbers level);
        };
}
