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
            void SetLevel(level_numbers level);
            unsigned int GetLevel(){return level_number;};
            Player* GetPlayer();
            void SetPlayer(Player* player);
            std::vector <Enemy> GetEnemies();
            void SetEnemy(Enemy& enemy);
            void OpenDoor(couple& point);
            void CloseDoor(couple& point);
            void map_output(level_numbers level);
            void Output();
            Case& GetCase(couple &point){
                return this->case_array[point.x][point.y];
            }
            void SetCase(Case& point, couple& there){
                this->case_array[there.x][there.y] = point;
            }
         
            void SetPointType(couple& point, TYPE type, level_numbers level, Enemy *enemy){
                int x = point.x;
                int y = point.y;
                case_array[x][y].SetType(type);
                switch(type){
                    default: break;
                    case FLOOR:{
                        if(this->case_array[x][y].GetChest())
                            map_catalog[level].lines[x][y] = '&';
                        if(this->case_array[x][y].GetItem()){
                            Item *item = this->case_array[x][y].GetItem();
                            switch(item->GetName()){
                                default: break;
                                case KEYCHAIN:{
                                    map_catalog[level].lines[x][y] = '\'';
                                    break;
                                }
                                case ARMOR:{
                                    map_catalog[level].lines[x][y] = ']';
                                    break;
                                }
                                case ARTEFACT_ARMOR:{
                                    map_catalog[level].lines[x][y] = ']';
                                    break;
                                }
                                case WEAPON:{
                                    map_catalog[level].lines[x][y] = ')';
                                    break;
                                }
                                case ARTEFACT_WEAPON:{
                                    map_catalog[level].lines[x][y] = ')';
                                    break;
                                }
                                case ENCHANTED_WEAPON:{
                                    map_catalog[level].lines[x][y] = ')';
                                    break;
                                }
                                case POTION:{
                                    map_catalog[level].lines[x][y] = '!';
                                    break;
                                }
                            }
                        }
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
         
        };
}
