#pragma once
#include "Armor.h"
#include "Artefact.h"
#include <vector>

namespace Dungeon{
    class ArtefactArmor : public Armor, public Artefact{
        public:
          ArtefactArmor(){
               this->SetName(ARTEFACT_ARMOR);
               this->SetType(HELMET);
               this->SetDefenceValue(10);
           }
           ~ArtefactArmor(){
               this->SetName(EMPTY);
               this->SetDefenceValue(0);
               this->ClearModificators();
           }
       };
}

