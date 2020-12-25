#pragma once
#include "Item.h"

namespace Dungeon{
class Potion : public Item{
    private:
        characteristic modificator;
    public:
        Potion(){
            srand((unsigned int)time(0));
            this->SetName(POTION);
            this->modificator.type = (feature)(rand()%4);
            this->modificator.current = rand()%21 + 10;
            this->modificator.max = this->modificator.current;
        }
        
        characteristic GetModificator(){
            return this->modificator;
        }
        void SetModificator(characteristic modificator){
            this->modificator = modificator;
        }
        ~Potion(){
            this->SetName(EMPTY);
            this->modificator.current = 0;
            this->modificator.max = 0;
        }
    
        bool operator == (Potion& left){
            if (this->GetName() == left.GetName() && this->modificator.type == left.modificator.type && this->modificator.max == left.modificator.max && this->modificator.current == left.modificator.current)
                return true;
            else return false;
        };

        bool operator != (Potion& left){
            return !(*this == left);
        };
    
    
    };
}

