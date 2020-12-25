#pragma once
#include "Weapon.h"

namespace Dungeon{
    class EnchantedWeapon : public Weapon{
    private:
        enemies enemy_type_up;
        enemies enemy_type_down;
        unsigned int index;
    public:
        EnchantedWeapon();
        enemies GetEnemyTypeUp();
        enemies GetEnemyTypeDown();
        unsigned int GetIndex();
        void SetIndex(unsigned int index);
        void SetEnemyTypeUp (enemies up);
        void SetEnemyTypeDown (enemies down);
        ~EnchantedWeapon();
    };
}
