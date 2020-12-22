#pragma once
#include "Character.h"
#include "Enemy.h"
#include "CustomVector.hpp"

namespace Dungeon{
    class Player : public Character{
    private:
        Weapon *weapon;
        MyVector <Armor> armor;
      //  unsigned int max_item_number;
        unsigned int key_nember;
        unsigned int DamageBonus(Enemy& enemy){
            unsigned int bonus = 0;
            if (this->weapon){
                bonus += this->weapon->GetDamageValue();
                switch(this->weapon->GetName()){
                    default: break;
                    case ENCHANTED_WEAPON:{
                        EnchantedWeapon *ench = dynamic_cast<EnchantedWeapon*>(this->weapon);
                        if (enemy.GetName() == ench->GetEnemyTypeDown())
                            bonus /= ench->GetIndex();
                        if (enemy.GetName() == ench->GetEnemyTypeUp())
                            bonus *= ench->GetIndex();
                        break;
                    }
                }
            }
            return bonus;
        }
        
        unsigned int DefenceBonus(){
            unsigned int bonus = 0;
            if (this->armor.MyVector::current_size()){
                for (int i = 0; i < this->armor.MyVector::current_size(); i++)
                    bonus += armor[i].GetDefenceValue();
            }
            return bonus;
        }
    public:
        Player();
        void DrinkPotion(Potion &potion);
        unsigned int GetKeyNumber();
        void SetKeyNumber(unsigned int number);
        void TakeKeys (Keychain& keys);
        void GenerateDamage(Character& character) override;
        void UpgradeFeature(feature& name);
        std::vector <Potion *> PotionList();
        std::vector <Weapon *> WeaponList();
        std::vector <Armor *> ArmorList();
        void SetWeapon(Weapon& weapon);
        Weapon* GetWeapon();
        void TakeWeapon(Weapon* weapon);
        void PutWeaponInBag();
        MyVector <Armor> GetArmor();
        bool TakeArmor(Armor& armor);
        void PutArmorInBag(Armor& armor);
        ~Player();
    };
}
