#pragma once
#include "Item.h"
#include <vector>
#include <iterator>

namespace Dungeon{
    class Artefact: public virtual Item{
         private:
             std::vector <characteristic> modificators;
         public:
         
             Artefact(){
                 this->SetName(ARTEFACT);
                 characteristic health = {HEALTH, 0, 0};
                 this->modificators.push_back(health);
             }
         
             std::vector <characteristic> GetModificators(){
                 return this->modificators;
             }
         
             void SetModificator(characteristic modificator){
                 this->modificators.push_back(modificator);
             }
             
             void ClearModificators(){
                 if (this->modificators.size() > 0)
                 this->modificators.clear();
                 else throw std::invalid_argument("out of array");
             }
             
             void DeleteModificator(unsigned int pos){
                 unsigned int size = (unsigned int)this->modificators.size();
                 if (pos > size - 1)
                     throw std::invalid_argument("out of array");
                 else{
                     std::vector <characteristic> :: iterator i = this->modificators.begin();
                     i += pos;
                     this->modificators.erase(i);
                 }
             }
             ~Artefact(){
                 this->SetName(EMPTY);
                 this->modificators.clear();
             }
         
     };
}

