#include "Chest.h"

namespace Dungeon{

    Chest::Chest(){
        this->catacombs_level_number = 0;
        this->item = nullptr;
        this->locked = true;
        this->must_key_number = 1;
    }

    unsigned int Chest::GetLevelNumber(){
        return this->catacombs_level_number;
    }

    void Chest::SetLevelNumber(unsigned int number){
        this->catacombs_level_number = number;
    }

    Item* Chest::GetItem(){
        return this->item;
    }

    bool Chest::GetLockedStatement(){
        return this->locked;
    }

    void Chest::SetLockedStatement(bool flag){
        this->locked = flag;
    }

    void Chest::SetItem(Item* item){
        *(this->item) = *item;
    }

    unsigned int Chest::GetNumber(){
        return this->must_key_number;
    }

    void Chest::SetNumber(unsigned int number){
        this->must_key_number = number;
    }

    void Chest::OpenAttempt(Player& player){
        unsigned int number = player.GetKeyNumber();
        if (number >= this->GetNumber()){
            number -= this->GetNumber();
            this->locked = false;
            player.SetItem(this->item);
        }
        else throw std::invalid_argument("key number is not enough");
    }

}
