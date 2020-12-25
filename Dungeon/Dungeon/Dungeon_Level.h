#pragma once
#include "Player.h"
#include <vector>
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
         std::vector <Enemy*> Enemies;
     public:
         CatacombsLevel(unsigned int level = 0);
         unsigned int GetLevel();
         TYPE GetPointType(couple& point);
         void SetPointType(couple& point, TYPE type, square& map, Enemy *enemy = nullptr);
         couple GetSize();
         Case& GetCase(couple &point);
         void SetCase(Case& point, couple& there);
         void SetLevel(square& map);
         Player* GetPlayer();
         void SetPlayer(Player* player);
         std::vector <Enemy*> GetEnemies();
         void SetEnemy(Enemy& enemy);
         void OpenDoor(couple& point);
         void CloseDoor(couple& point);
     };
}
