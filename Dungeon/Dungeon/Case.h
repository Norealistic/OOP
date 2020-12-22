#pragma once
#include "Chest.h"

namespace Dungeon{

    typedef struct couple{
        int x;
        int y;
    }couple;


    typedef enum {FLOOR, OPENED_DOOR, CLOSED_DOOR, WALL, STAIRS_UP, STAIRS_DOWN, PLAYER, ENEMY} TYPE;
        

        class Case{
        private:
            TYPE type;
            Item* item;
            Chest* chest;
            couple coordinates;
        public:
            Case(TYPE type = FLOOR, couple point = {0,0});
            Chest* GetChest();
            bool SetChest(Chest* chest);
            Item* GetItem();
            bool SetItem(Item* item);
            couple GetCoordinates();
            void SetCoordinates(couple coordinates);
            TYPE GetType();
            void SetType(TYPE type);
        };
}
