#include "Dungeon_Level.h"


namespace Dungeon {

    CatacombsLevel::CatacombsLevel(unsigned int level){
        this->level_number = level;
        this->size = {40, 20};
        this->player = new Player();
        srand((unsigned int)time(0));
        this->Enemies.resize(5*pow(level,2));
        std::vector <Enemy> ::iterator it = this->Enemies.begin();
        for (int i = 0; i < 5*pow(level,2); i++){
           // *it = Enemy(((enemies)(rand()%6)));
            item_names name;
            do{
                name = (item_names)(rand()%8 + 2);
            }while (name == ARTEFACT);
            switch(name){
                default:{
                    Keychain* keychain = new Keychain;
                    it->SetItem(keychain);
                    keychain->~Keychain();
                    break;
                }
                case ARMOR:{
                    Armor* armor = new Armor();
                    it->SetItem(armor);
                    armor->~Armor();
                    break;
                }
                case ARTEFACT_ARMOR:{
                    ArtefactArmor* artefact_armor = new ArtefactArmor();
                    it->SetItem(artefact_armor);
                    artefact_armor->~ArtefactArmor();
                    break;
                }
                case WEAPON:{
                    Weapon *weapon = new Weapon;
                    it->SetItem(weapon);
                    weapon->~Weapon();
                    break;
                }
                case ARTEFACT_WEAPON:{
                    ArtefactWeapon *artefact_weapon = new ArtefactWeapon;
                    it->SetItem(artefact_weapon);
                    artefact_weapon->~ArtefactWeapon();
                    break;
                }
                case ENCHANTED_WEAPON:{
                    EnchantedWeapon *ench_weapon = new EnchantedWeapon;
                    it->SetItem(ench_weapon);
                    ench_weapon->~EnchantedWeapon();
                    break;
                }
                case POTION:{
                    Potion *potion = new Potion;
                    it->SetItem(potion);
                    potion->~Potion();
                    break;
                }
            }
            it++;
        }
    }

    couple CatacombsLevel::GetSize(){
        return this->size;
    }

    void CatacombsLevel::SetLevel(level_numbers level){
    srand((unsigned int)time(0));
    this->size = {40, 20};
    this->case_array.clear();
    this->case_array.resize(20);//20 строк
    std::vector <std::vector <Case>> ::iterator it = this->case_array.begin();
    for (int i = 0; i < 20; i++){
        it->resize(40);//40 столбцов
        it++;
    }
    it = this->case_array.begin();
    int i = 0, j = 0;
    for(;it < this->case_array.end(); it++){
        std::vector <Case> ::iterator sub_it = it->begin();
        for (;sub_it < it->end(); sub_it++){
            couple point = {i,j};
            if (map_catalog[i].lines[j] == "#"){
                this->case_array[point.x][point.y] = (Case(WALL, point)); ///
                break;
            }
            else if (map_catalog[i].lines[j] == "+"){
                this->case_array[point.x][point.y] = (Case(CLOSED_DOOR, point));
                break;
            }
            else if (map_catalog[i].lines[j] == "&"){
                Chest *chest = new Chest();
                chest->SetLevelNumber((unsigned int)level);
                chest->SetNumber(rand()%(int)level + 1);
                item_names name;
                do{
                    name = (item_names)(rand()%8 + 2);
                }while (name == ARTEFACT);
                switch(name){
                    default:{
                        Keychain* keychain = new Keychain;
                        chest->SetItem(keychain);
                        keychain->~Keychain();
                        break;
                    }
                    case ARMOR:{
                        Armor* armor = new Armor();
                        chest->SetItem(armor);
                        armor->~Armor();
                        break;
                    }
                    case ARTEFACT_ARMOR:{
                        ArtefactArmor *artefact_armor = new ArtefactArmor;
                        chest->SetItem(artefact_armor);
                        artefact_armor->~ArtefactArmor();
                        break;
                    }
                    case WEAPON:{
                        Weapon *weapon = new Weapon();
                        chest->SetItem(weapon);
                        weapon->~Weapon();
                        break;
                    }
                    case ARTEFACT_WEAPON:{
                        ArtefactWeapon *artefact_weapon = new ArtefactWeapon();
                        chest->SetItem(artefact_weapon);
                        artefact_weapon->~ArtefactWeapon();
                        break;
                    }
                    case ENCHANTED_WEAPON:{
                        EnchantedWeapon *ench_weapon = new EnchantedWeapon();
                        chest->SetItem(ench_weapon);
                        ench_weapon->~EnchantedWeapon();
                        break;
                    }
                    case POTION:{
                        Potion *potion = new Potion();
                        chest->SetItem(potion);
                        potion->~Potion();
                        break;
                    }
                }
                this->case_array[point.x][point.y] = (Case(FLOOR, point));
                bool flag = sub_it->SetChest(chest);
                if (!flag)
                    throw std::exception();
                break;
            }
            else if (map_catalog[i].lines[j] == ">"){
                this->case_array[point.x][point.y] = (Case(STAIRS_DOWN, point));
                break;
            }
            else if (map_catalog[i].lines[j] == "<"){
                this->case_array[point.x][point.y] = (Case(STAIRS_UP, point));
                break;
            }
            else{
                this->case_array[point.x][point.y] = (Case(FLOOR, point));
                break;
            }
            }
         i++;
        }
    }


    Player* CatacombsLevel::GetPlayer(){
        return this->player;
    }

    void CatacombsLevel::SetPlayer(Player* player){
        this->player = player;
    }

    std::vector <Enemy> CatacombsLevel::GetEnemies(){
        return this->Enemies;
    }

    void CatacombsLevel::SetEnemy(Enemy& enemy){
        this->Enemies.push_back(enemy);
    }

    void CatacombsLevel::OpenDoor(couple& point){
        std::vector <std::vector <Case>> ::iterator it = this->case_array.begin();
        it += point.x;
        std::vector <Case> ::iterator sub_it = it->begin();
        sub_it += point.y;
        if (sub_it->GetType() == CLOSED_DOOR)
            sub_it->SetType(OPENED_DOOR);
        else throw std::invalid_argument("It is not a door");
    }

    void CatacombsLevel::CloseDoor(couple &point){
        std::vector <std::vector <Case>> ::iterator it = this->case_array.begin();
        it += point.x;
        std::vector <Case> ::iterator sub_it = it->begin();
        sub_it += point.y;
        if (sub_it->GetType() == OPENED_DOOR)
            sub_it->SetType(CLOSED_DOOR);
        else throw std::invalid_argument("It is not a door");
    }

}
