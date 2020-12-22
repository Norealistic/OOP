#pragma once
#include "Item.h"

namespace Dungeon{
    class Keychain : public virtual Item{
    private:
        unsigned int key_number;
    public:
        Keychain(){
            srand((unsigned int)time(0));
            this->SetName(KEYCHAIN);
            this->key_number = rand()%3 + 1;
        }
        
        const unsigned int GetKeyNumber(){
            return this->key_number;
        }
        
        void SetKeyNumber(unsigned int number){
            this->key_number = number;
        }
        
        ~Keychain(){
            this->SetName(EMPTY);
            this->key_number = 0;
        }
    };
}

