#include "Armor.h"

namespace Dungeon{

    Armor::Armor(){
        srand((unsigned int)time(0));
        this->SetName(ARMOR);
        this->type = (armor_type)(rand()%4);
        this->defence_value = rand()%11 + 10;
    }

    armor_type Armor::GetType(){
        return this->type;
    }

    unsigned int Armor::GetDefenceValue(){
        return this->defence_value;
    }

    void Armor::SetType(armor_type type){
        this->type = type;
    }

    void Armor::SetDefenceValue(unsigned int value){
        this->defence_value = value;
    }
}
