#pragma once
#include <iostream>
#include <cstring>

namespace Dungeon{

    typedef enum {EMPTY, ITEM, KEYCHAIN, ARMOR, ARTEFACT, ARTEFACT_ARMOR, WEAPON, ARTEFACT_WEAPON, ENCHANTED_WEAPON, POTION} item_names;

       const std::string str_item_names[10] = {"EMPTY", "ITEM", "KEYCHAIN", "ARMOR", "ARTEFACT", "ARTEFACT_ARMOR", "WEAPON", "ARTEFACT_WEAPON", "ENCHANTED_WEAPON", "POTION"};
       typedef enum {STRENGTH, AGILITY, STAMINA, HEALTH} feature;

       const std::string str_feature_names[4] = {"STRENGTH", "AGILITY", "STAMINA", "HEALTH"};
       
       typedef struct characteristic{
           feature type;
           unsigned int current;
           unsigned int max;
       } characteristic;

       typedef enum {HUMANLIKE, INSECT, BEAST, UNDEAD, DEVIL, ICY} enemies;

       const std::string str_enemy_names[6] = {"HUMANLIKE", "INSECT", "BEAST", "UNDEAD", "DEVIL", "ICY"};

       typedef enum {HELMET, CHESTPLATE, LEGGINGS, BOOTS} armor_type;

       const std::string str_armor_types[4] = {"HELMET", "CHESTPLATE", "LEGGINGS", "BOOTS"};


    class Item{
        private:
            item_names name;
    public: 
        Item(){
            this->name = ITEM;
        }
        
        virtual void SetName(item_names name){
            this->name = name;
        }
        
        virtual item_names GetName(){
            return this->name;
        }
        
        ~Item(){
            this->name = EMPTY;
        }
    };
}
