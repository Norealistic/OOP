#pragma once
#include <optional>
#include "Item.h"

namespace Dungeon{
    class Weapon : public virtual Item{
        private:
            unsigned int damage_value;
        public:
            Weapon(){
                this->SetName(WEAPON);
                this->damage_value = rand()%11 + 10;
            }
            
            virtual unsigned int GetDamageValue(){
                return this->damage_value;
            }
            
            virtual void SetDamageValue(unsigned int value){
                this->damage_value = value;
            }
        
            ~Weapon(){
                this->SetName(EMPTY);
                this->damage_value = 0;
            }
    };
}
