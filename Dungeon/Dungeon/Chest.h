#pragma once
#include "Player.h"

namespace Dungeon{
    class Chest{
    private:
        unsigned int catacombs_level_number;
        Item* item;
        bool locked;
        unsigned int must_key_number;
    public:
        Chest();
        unsigned int GetLevelNumber();
        void SetLevelNumber(unsigned int number);
        bool GetLockedStatement();
        void SetLockedStatement(bool flag);
        unsigned int GetNumber();
        void SetNumber (unsigned int number);
        Item* GetItem();
        void SetItem(Item* item);
        void OpenAttempt(Player& player);
    };
}



