#include "Enchanted_Weapon.h"

namespace Dungeon{

    EnchantedWeapon::EnchantedWeapon(){
        srand((unsigned int)time(0));
        this->SetName(ENCHANTED_WEAPON);
        this->SetDamageValue(rand()%56 + 50);
        enemies type_down = (enemies)(rand()%6);
        this->enemy_type_down = type_down;
        enemies type_up;
        do{
            type_up = (enemies)(rand()%6);
        }while(type_up == type_down);
        this->enemy_type_up = type_up;
        this->index = rand()%5 + 1;
    }

    enemies EnchantedWeapon::GetEnemyTypeUp(){
        return this->enemy_type_up;
    }

    enemies EnchantedWeapon::GetEnemyTypeDown(){
        return this->enemy_type_down;
    }

    unsigned int EnchantedWeapon::GetIndex(){
        return this->index;
    }

    void EnchantedWeapon::SetEnemyTypeUp(enemies up){
        this->enemy_type_up = up;
    }

    void EnchantedWeapon::SetEnemyTypeDown(enemies down){
        this->enemy_type_down = down;
    }
    
    void EnchantedWeapon::SetIndex(unsigned int index){
        this->index = index;
    }

    EnchantedWeapon::~EnchantedWeapon(){
        this->SetName(EMPTY);
        this->SetDamageValue(0);
        this->index = 0;
    }
}
