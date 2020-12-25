#pragma once
#include "Character.h"
#include "Enemy.h"
#include "CustomVector.hpp"

namespace Dungeon{
    
    class Player : public Character{
    private:
        std::vector <Weapon> weapon;
        MyVector <Armor> armor;
        std::vector <Potion> potions;
        const unsigned int potion_number = 5;
        //unsigned int max_item_number;
        unsigned int key_nember;
        unsigned int DamageBonus(Enemy& enemy);
        unsigned int DefenceBonus();
    public:
        Player();
        void DrinkPotion(Potion &potion);
        void SetPotion(Potion &potion);
        unsigned int GetKeyNumber();
        void SetKeyNumber(unsigned int number);
        void TakeKeys (Keychain& keys);
        void GenerateDamage(Character& character) override;
        void UpgradeFeature(feature& name);
        std::vector <Potion> PotionList();
        std::vector <Weapon> WeaponList();
        void TakeWeapon(Weapon& weapon);
        MyVector <Armor> ArmorList();
        bool TakeArmor(Armor& armor);
        ~Player();
    };

}
