#include "Enemy.h"

namespace Dungeon{
    Enemy::Enemy(enemies name){
        srand((unsigned int)time(0));
        this->name = name;
        this->damage_value = rand()%11 + 10;;
        this->SetExperience(rand()%101 + 120);
        unsigned int max = rand()%106 + 120;
        characteristic health = {HEALTH, max, max};
        this->ClearFeatures();
        this->SetFeature(health);
    }

    enemies Enemy::GetName(){
        return this->name;
    }

    void Enemy::SetName (enemies name){
        this->name = name;
    }

    unsigned int Enemy::GetDamageValue(){
        return this->damage_value;
    }

    void Enemy::SetDamageValue(unsigned int value){
        this->damage_value = value;
    }

    void Enemy::GenerateDamage(Character& character){
        character.SetDamage(this->damage_value);
    }

    Enemy::~Enemy(){
        this->SetExperience(0);
        this->ClearFeatures();
        this->ClearBag();
        this->damage_value = 0;
    }
}

