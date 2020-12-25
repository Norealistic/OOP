#include "Player.h"
namespace Dungeon{

    unsigned int Player::DamageBonus(Enemy& enemy){
        srand(time(0));
        unsigned int bonus = 0;
        if (this->weapon.size()>0){
        int index = rand()%(this->weapon.size());
        Weapon weapon = this->weapon.at(index);
            bonus += weapon.GetDamageValue();
            switch(weapon.GetName()){
            default: break;
                case ENCHANTED_WEAPON:{
                    EnchantedWeapon *ench = dynamic_cast<EnchantedWeapon*>(&weapon);
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


    unsigned int Player::DefenceBonus(){
        unsigned int bonus = 0;
        if (this->armor.MyVector::current_size()){
            for (int i = 0; i < this->armor.MyVector::current_size(); i++)
                bonus += armor[i].GetDefenceValue();
        }
        return bonus;
    }
        Player::Player(){
            this->SetExperience(0);
            for (int i = 0; i < 4; i++){
                characteristic feat;
                feat.type = (feature)i;
                feat.current = 50;
                feat.max = 50;
                this->SetFeature(feat);
            }
            this->key_nember = 5;
        }

        void Player::DrinkPotion(Potion &potion){
            characteristic mod = potion.GetModificator();
            std::vector <characteristic> features = this->GetFeatures();
            std::vector <characteristic> ::iterator it = features.begin();
            while (it->type != mod.type)
                it++;
            switch(mod.type){
                case HEALTH:{
                    if (it->max - it->current < mod.current)
                        it->current = it->max;
                    else
                        it->current += mod.current;
                    break;
                }
                    
                default:{
                    it->current += mod.current;
                    it->max += mod.max;
                    break;
                }
            }
            this->ClearFeatures();
            it = features.begin();
            while (it != features.end()){
                this->SetFeature(*it);
                it++;
            }
            std::vector <Potion> ::iterator p = this->potions.begin();
            while (*p != potion) p++;
            this->potions.erase(p);
        }

        void Player::GenerateDamage(Character& character){
            srand(time(0));
            unsigned int damage = 10;
            if (this->weapon.size() > 0){
            int index = rand()%(this->weapon.size());
            Weapon weapon = this->weapon.at(index);
            std::vector <characteristic> features = this->GetFeatures();
            std::vector <characteristic> ::iterator it = features.begin();
            while (it != features.end()){
                damage += it->current/10;
                it++;
            }
            Enemy &enemy = dynamic_cast<Enemy&>(character);
            damage += DamageBonus(enemy);
            if (weapon.GetName() == ENCHANTED_WEAPON){
                EnchantedWeapon* ench = dynamic_cast<EnchantedWeapon*>(&weapon);
                enemies name = enemy.GetName();
                if (ench->GetEnemyTypeUp() == name)
                    damage *= ench->GetIndex();
                if (ench->GetEnemyTypeDown() == name)
                    damage /= ench->GetIndex();
            }
            }
            std::vector <characteristic> features = character.GetFeatures();
            std::vector <characteristic> ::iterator it = features.begin();
            if (it->type == HEALTH){
                if (it->current > damage)
                    it->current -= damage;
                else{
                    it->current = 0;
                    unsigned int xp = character.GetExperience();
                    this->SetExperience(this->GetExperience()+xp);
                    std::vector <Item> item = character.GetItems();
                    std::vector <Item> ::iterator p = item.begin();
                    switch(POTION){
                        default:{
                        Keychain* keychain = new Keychain();
                        this->key_nember += keychain->GetKeyNumber();
                        keychain->~Keychain();
                        break;
                    }
                    case ARMOR:{
                        Armor* armor = new Armor();
                        this->TakeArmor(*armor);
                        armor->~Armor();
                        break;
                    }
                    case ARTEFACT_ARMOR:{
                        ArtefactArmor *artefact_armor = new ArtefactArmor();
                        this->TakeArmor(*artefact_armor);
                        artefact_armor->~ArtefactArmor();
                        break;
                    }
                    case WEAPON:{
                        Weapon *weapon = new Weapon();
                        this->TakeWeapon(*weapon);
                        weapon->~Weapon();
                        break;
                    }
                    case ARTEFACT_WEAPON:{
                        ArtefactWeapon *artefact_weapon = new ArtefactWeapon();
                        this->TakeWeapon(*artefact_weapon);
                        artefact_weapon->~ArtefactWeapon();
                        break;
                    }
                    case ENCHANTED_WEAPON:{
                        EnchantedWeapon *ench_weapon = new EnchantedWeapon();
                        this->TakeWeapon(*ench_weapon);
                        ench_weapon->~EnchantedWeapon();
                        break;
                    }
                    case POTION:{
                        Potion *potion = new Potion();
                        this->SetPotion(*potion);
                        potion->~Potion();
                        break;
                    }
                }
            }
            character.ClearFeatures();
            character.SetFeature(*it);
            
            //character.SetDamage(damage);
        }
        }

        void Player::UpgradeFeature(feature& name){
            unsigned long xp = this->GetExperience();
            std::vector <characteristic> features = this->GetFeatures();
            std::vector <characteristic> ::iterator it = features.begin();
            while (it->type != name) it++;
            if (xp > 100){
                xp -= 100;
                it->current += 10;
                it->max += 10;
            }
            it = features.begin();
            while (it != features.end()){
                this->SetFeature(*it);
                it++;
            }
            this->SetExperience(xp);
        }

        Player::~Player(){
            this->ClearFeatures();
            this->ClearBag();
            this->weapon.clear();
            this->potions.clear();
            this->key_nember = 0;
            this->armor.Clear();
            this->SetExperience(0);
        }

        /*Weapon* Player::GetWeapon(){
            return this->weapon;
        }*/

        void Player::TakeWeapon(Weapon& weapon){
            this->weapon.push_back(weapon);
        }

        /*void Player::PutWeaponInBag(){
            Weapon *weapon = this->weapon;
            this->SetItem(*weapon);
            this->weapon = nullptr;
        }*/

        unsigned int Player::GetKeyNumber(){
            return this->key_nember;
        }


        void Player::SetKeyNumber(unsigned int number){
            this->key_nember = number;
        }

        void Player::TakeKeys(Keychain& keys){
            this->key_nember += keys.GetKeyNumber();
            keys.~Keychain();
        }

        MyVector <Armor> Player::ArmorList(){
            return this->armor;
        }

        bool Player::TakeArmor(Armor& armor){
            MyIterator <Armor> it = this->armor.Begin();
            int i = 0;
            for (;i < this->armor.current_size(); i++, it++){
                if ((*it)->GetType() == armor.GetType()) return false;
                i++;
            }
            this->armor.Push_back(armor);
            return true;
        }

        /*void Player::PutArmorInBag(Armor& armor){
            MyIterator <Armor> it = this->armor.Begin();
            int i = 0;
            for (; i < this->armor.current_size(); i++, it++){
                if ((*it)->GetType() == armor.GetType()) break;
                i++;
            }
            if ((*it)->GetType() == armor.GetType()){
                this->SetItem(armor);
                try{
                    this->armor.Erase(armor);
                }
                catch (std::exception &er){
                    throw std::exception(er);
                }
            }
        }*/

        std::vector <Potion> Player::PotionList(){
            return this->potions;
        }

        std::vector <Weapon> Player::WeaponList(){
            return this->weapon;
        }

        void Player::SetPotion(Potion &potion){
            if (potions.size() < 5)
                this->potions.push_back(potion);
        }
        /*std::vector <Armor> Player::ArmorList(){
            std::vector <Item> bag = this->GetItems();
            std::vector <Item> ::iterator it = bag.begin();
            std::vector <Armor> list;
            int size = bag.size();
            for (int i = 0; i < size; i++, it++){
                if (it->GetName() == ARMOR || it->GetName() == ARTEFACT_ARMOR){
                    Armor *p_it = dynamic_cast<Armor*>(&(*it));
                    list.push_back(*p_it);
                }
            }
            return list;
        }*/
    }
