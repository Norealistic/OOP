#pragma once
#include "Keychain.h"
#include "Potion.h"
#include "Artefact_Weapon.h"
#include "Enchanted_Weapon.h"
#include "Artefact_Armor.h"
#include <vector>
#include <iterator>

namespace Dungeon{
    class Character{
    private:
        unsigned long xp;
        std::vector <characteristic> feature_table;
        std::vector <Item *> bag;
    public:
        Character();
        unsigned long GetExperience();
        void SetExperience(unsigned long xp);
        std::vector <characteristic> GetFeatures();
        void SetFeature(characteristic& feat);
        virtual void GenerateDamage(Character& character);
        void SetDamage(unsigned int damage);
        std::vector <Item *> GetItems();
        void DeleteItem(Item& item);
        void SetItem(Item* item);
        void ClearFeatures();
        void ClearBag();
        ~Character();
        Character& operator= (Character& character){
            this->xp = character.xp;
            this->feature_table = character.feature_table;
            this->bag = character.bag;
            return *this;
        } 
    };
}
