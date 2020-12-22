#pragma once
#include "Character.h"
#include <time.h>

namespace Dungeon{
    class Enemy : virtual public Character{
       private:
           enemies name;
           unsigned int damage_value;
       public:
           Enemy(enemies name = HUMANLIKE);
           enemies GetName();
           void SetName (enemies name);
           unsigned int GetDamageValue();
           void SetDamageValue(unsigned int value);
           void GenerateDamage(Character& character) override;
           ~Enemy();
       };
}
