#pragma once
#include "Weapon.h"
#include "Artefact.h"
#include <vector>

namespace Dungeon{
    class ArtefactWeapon : public virtual Weapon, public virtual Artefact{
        public:
        ArtefactWeapon(){
            this->SetName(ARTEFACT_WEAPON);
            int max = rand()%4;
            for (int i = 0; i <= max; i++){
                feature type = (feature)i;
                unsigned int cur = rand()%51+50;
                characteristic modificator = {type, cur, cur};
                this->SetModificator(modificator);
            }
            this->SetDamageValue(rand()%11 + 10);
            
        }
        ~ArtefactWeapon(){
            this->SetName(EMPTY);
            this->SetDamageValue(0);
            this->ClearModificators();
        }
    };
}


