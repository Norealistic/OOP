#include "Character.h"

namespace Dungeon{

     Character::Character(){
         this->xp = 0;
         this->feature_table.reserve(4);
         std::vector <characteristic> ::iterator it = this->feature_table.begin();
         int n = 0;
         for (; it <= this->feature_table.end(); it++, n++){
             it->type = (feature)n;
             it->current = 100;
             it->max = 100;
         }
     }

     unsigned long Character::GetExperience(){
         return this->xp;
     }

     void Character::SetExperience(unsigned long xp){
         this->xp = xp;
     }

     std::vector <characteristic> Character::GetFeatures(){
         return this->feature_table;
     }

     void Character::SetFeature(characteristic& feat){
         this->feature_table.push_back(feat);
     }

     void Character::GenerateDamage(Character& character){
         character.SetDamage(10);
     }

     Character::~Character(){
         this->xp = 0;
         this->feature_table.clear();
         this->bag.clear();
     }
     
     void Character::SetDamage(unsigned int damage){
         std::vector <characteristic> ::iterator it = this->feature_table.end();
         if (it->current >= damage)
             it->current -= damage;
         else
             it->current = 0;
     }

     std::vector <Item *> Character::GetItems(){
         return this->bag;
     }

     void Character::SetItem(Item* item){
         this->bag.push_back(item);
     }

    void Character::ClearFeatures(){
         this->feature_table.clear();
     }

     void Character::ClearBag(){
         this->bag.clear();
     }

     void Character::DeleteItem(Item& item){
         std::vector <Item *> ::iterator it = this->bag.begin();
         while ((*it)->GetName() != item.GetName()) it++;
         switch (item.GetName()){
             default: break;
             case KEYCHAIN:{
                 Item something = *(*it);
                 Keychain *key1 = dynamic_cast<Keychain*>(&something);
                 Keychain &key2 = dynamic_cast<Keychain&>(item);
                 if (key1->GetKeyNumber() == key2.GetKeyNumber()) this->bag.erase(it);
                 break;
             }
             case ARMOR:{
                 Item something = *(*it);
                 Armor *arm1 = dynamic_cast<Armor*>(&something);
                 Armor &arm2 = dynamic_cast<Armor&>(item);
                 if (arm1->GetDefenceValue() == arm2.GetDefenceValue() && arm1->GetType() == arm2.GetType()) this->bag.erase(it);
                 break;
             }
             case WEAPON:{
                 Item something = *(*it);
                 Weapon *weapon1 = dynamic_cast<Weapon*>(&something);
                 Weapon &weapon2 = dynamic_cast<Weapon&>(item);
                 if (weapon1->GetDamageValue() == weapon2.GetDamageValue()) this->bag.erase(it);
                 break;
             }
             case POTION:{
                 Item something = *(*it);
                 Potion *potion1 = dynamic_cast<Potion*>(&something);
                 Potion &potion2 = dynamic_cast<Potion&>(item);
                 if (potion1->GetModificator().type == potion2.GetModificator().type && potion1->GetModificator().current == potion2.GetModificator().current) this->bag.erase(it);
                 break;
             }
             case ARTEFACT_WEAPON:{
                 Item something = *(*it);
                 ArtefactWeapon *weapon1 = dynamic_cast<ArtefactWeapon*>(&something);
                 ArtefactWeapon &weapon2 = dynamic_cast<ArtefactWeapon&>(item);
                 if (weapon1->GetDamageValue() == weapon2.GetDamageValue()) this->bag.erase(it);
                 break;
             }
             case ENCHANTED_WEAPON:{
                 Item something = *(*it);
                 EnchantedWeapon *weapon1 = dynamic_cast<EnchantedWeapon*>(&something);
                 EnchantedWeapon &weapon2 = dynamic_cast<EnchantedWeapon&>(item);
                 if (weapon1->GetDamageValue() == weapon2.GetDamageValue()) this->bag.erase(it);
                 break;
             }
             case ARTEFACT_ARMOR:{
                 Item something = *(*it);
                 ArtefactArmor *arm1 = dynamic_cast<ArtefactArmor*>(&something);
                 ArtefactArmor &arm2 = dynamic_cast<ArtefactArmor&>(item);
                 if (arm1->GetDefenceValue() == arm2.GetDefenceValue() && arm1->GetType() == arm2.GetType()) this->bag.erase(it);
                 break;
             }
         }
     }
}
