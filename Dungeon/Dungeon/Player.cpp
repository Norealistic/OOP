#include "Player.h"
namespace Dungeon{

    Player::Player(){
        this->SetExperience(0);
        for (int i = 0; i < 4; i++){
            characteristic feat;
            feat.type = (feature)i;
            feat.current = 15;
            feat.max = 50;
            this->SetFeature(feat);
        }
        this->weapon = nullptr;
       // this->max_item_number = 10;
        this->key_nember = 0;
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
    }

    void Player::GenerateDamage(Character& character){
        unsigned int damage = 0;
        std::vector <characteristic> features = this->GetFeatures();
        std::vector <characteristic> ::iterator it = features.begin();
        while (it != features.end()){
            damage += it->current/10;
            it++;
        }
        Enemy &enemy = dynamic_cast<Enemy&>(character);
        damage += DamageBonus(enemy); //ИСПРАВЛЕНО
        if (this->weapon->GetName() == ENCHANTED_WEAPON){
            EnchantedWeapon* ench = dynamic_cast<EnchantedWeapon*>(this->weapon);
            enemies name = enemy.GetName();
            if (ench->GetEnemyTypeUp() == name)
                damage *= ench->GetIndex();
            if (ench->GetEnemyTypeDown() == name)
                damage /= ench->GetIndex();
        }
    }

    void Player::UpgradeFeature(feature& name){
        unsigned long xp = this->GetExperience();
        std::vector <characteristic> features = this->GetFeatures();
        std::vector <characteristic> ::iterator it = features.begin();
        while (it->type != name) it++;
        if (xp > 1000){
            xp -= 1000;
            it->current += 10;
            it->max += 10;
        }
        it = features.begin();
        while (it != features.end())
            this->SetFeature(*it);
        this->SetExperience(xp);
    }

    Player::~Player(){
        this->ClearFeatures();
        this->ClearBag();
        this->weapon = nullptr;
        this->key_nember = 0;
        this->armor.MyVector<Armor>::Clear();
        this->SetExperience(0);
    }

    Weapon* Player::GetWeapon(){
        return this->weapon;
    }

    void Player::TakeWeapon(Weapon* weapon){
        switch(weapon->GetName()){
            default: break;
            case ARTEFACT_WEAPON:{
                ArtefactWeapon *art = dynamic_cast<ArtefactWeapon*>(weapon);
                std::vector <characteristic> features = this->GetFeatures();
                std::vector <characteristic> modificators = art->GetModificators();
                std::vector <characteristic> ::iterator it1 = features.begin();
                std::vector <characteristic> ::iterator it2 = modificators.begin();
                for (; it2 <= modificators.end(); it2++){
                    for (; it1 <= features.end(); it1++){
                        if (it1->type == it2->type){
                            it1->current += it2->current;
                            it1->max += it2->max;
                        }
                    }
                }
                it1 = features.begin();
                while (it1 <= features.end())
                    this->SetFeature(*it1);
                break;
            }
        }
        *(this->weapon) = *weapon;
    }

    void Player::PutWeaponInBag(){
        Weapon *weapon = this->weapon;
        this->SetItem(weapon);
        this->weapon = nullptr;
    }

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

    MyVector <Armor> Player::GetArmor(){
        return this->armor;
    }

    bool Player::TakeArmor(Armor& armor){
        int i = 0;
        while (i != this->armor.MyVector<Armor>::current_size()){
            if (this->armor[i].GetType() == armor.GetType()) return false;
            i++;
        }
        this->armor.MyVector<Armor>::Push_back(armor);
        return true;
    }

    void Player::PutArmorInBag(Armor& armor){
        int i = 0;
        while (i != this->armor.MyVector<Armor>::current_size()){
            if (this->armor[i].GetType() == armor.GetType()) break;
            i++;
        }
        if (this->armor[i].GetType() == armor.GetType()){
            this->SetItem(&armor);
            try{
                this->armor.MyVector<Armor>::Erase(i);
            }
            catch (std::out_of_range){
                throw std::out_of_range("No element");
            }
        }
    }

    std::vector <Potion *> Player::PotionList(){
        std::vector <Item *> bag = this->GetItems();
        std::vector <Item *> ::iterator it = bag.begin();
        std::vector <Potion *> list;
        int size = (int)bag.size();
        for (int i = 0; i < size; i++, it++){
            if ((*it)->GetName() == POTION)
                list.push_back(dynamic_cast<Potion *>((*it)));
        }
        return list;
    }

    std::vector <Weapon *> Player::WeaponList(){
        std::vector <Item *> bag = this->GetItems();
        std::vector <Item *> ::iterator it = bag.begin();
        std::vector <Weapon *> list;
        int size = (int)bag.size();
        for (int i = 0; i < size; i++, it++){
            if ((*it)->GetName() == WEAPON || (*it)->GetName() == ENCHANTED_WEAPON || (*it)->GetName() == ARTEFACT_WEAPON)
                list.push_back(dynamic_cast<Weapon *>((*it)));
        }
        return list;
    }

    std::vector <Armor *> Player::ArmorList(){
        std::vector <Item *> bag = this->GetItems();
        std::vector <Item *> ::iterator it = bag.begin();
        std::vector <Armor *> list;
        int size = (int)bag.size();
        for (int i = 0; i < size; i++, it++){
            if ((*it)->GetName() == ARMOR || (*it)->GetName() == ARTEFACT_ARMOR)
                list.push_back(dynamic_cast<Armor *>((*it)));
        }
        return list;
    }

}
