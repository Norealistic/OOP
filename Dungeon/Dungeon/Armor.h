#pragma once
#include "Item.h"

namespace Dungeon{
    class Armor : public virtual Item{
           
           private:
               armor_type type;
               unsigned int defence_value;
           public:
               Armor();
               armor_type GetType();
               virtual unsigned int GetDefenceValue();
               virtual void SetType(armor_type type);
               virtual void SetDefenceValue(unsigned int value);
               bool operator != (Armor &obj) {
                   if (this->GetDefenceValue() == obj.GetDefenceValue() && this->GetType() == obj.GetType())
                       return false;
                   else return true;
               };
       };
}
