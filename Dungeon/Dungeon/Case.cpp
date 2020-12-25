#include "Case.h"

namespace Dungeon{

    Case::Case(TYPE type, couple point){
           this->type = type;
           this->item = nullptr;
           this->chest = nullptr;
           this->coordinates = point;
       }

       Chest* Case::GetChest(){
           return this->chest;
       }

       bool Case::SetChest(Chest* chest){
           if(chest == nullptr) {
               DeleteChest();
               return true;
           }
           if (!this->item){
               this->chest = new Chest;
               *(this->chest) = *chest;
               return true;
           }
           else return false;
       }

       Item* Case::GetItem(){
           return this->item;
       }

       bool Case::SetItem(Item* item){
           if (item == nullptr){
               DeleteItem();
               return true;
           }
           if (!this->chest || (this->chest && !this->chest->GetLockedStatement())){
               this->item = new Item;
               *(this->item) = *item;
               return true;
           }
           else return false;
       }

       couple Case::GetCoordinates(){
           return this->coordinates;
       }

       void Case::SetCoordinates(couple coordinates){
           this->coordinates = coordinates;
       }

       TYPE Case::GetType(){
           return this->type;
       }

       void Case::SetType(TYPE type){
           this->type = type;
       }
    
}
