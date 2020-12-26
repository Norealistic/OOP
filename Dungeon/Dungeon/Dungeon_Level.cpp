#include "Dungeon_Level.h"


namespace Dungeon {

    CatacombsLevel::CatacombsLevel(unsigned int level){
            this->level_number = level;
            this->size = {40, 20};
            this->player = new Player();
            srand(time(0));
            this->Enemies.resize(5*pow(level,2));
            std::vector <Enemy*> ::iterator it = this->Enemies.begin();
            for (int i = 0; i < 5*pow(level,2); i++){
                this->Enemies[i] = new Enemy((enemies)(rand()%6));
                item_names name;
                do{
                    name = (item_names)(rand()%8 + 2);
                }while (name == ARTEFACT);
                switch(name){
                    default:{
                        Keychain* keychain = new Keychain();
                        (*it)->SetItem(*keychain);
                        keychain->~Keychain();
                        break;
                    }
                    case ARMOR:{
                        Armor* armor = new Armor();
                        (*it)->SetItem(*armor);
                        armor->~Armor();
                        break;
                    }
                    case ARTEFACT_ARMOR:{
                        ArtefactArmor *artefact_armor = new ArtefactArmor();
                        (*it)->SetItem(*artefact_armor);
                        artefact_armor->~ArtefactArmor();
                        break;
                    }
                    case WEAPON:{
                        Weapon *weapon = new Weapon();
                        (*it)->SetItem(*weapon);
                        weapon->~Weapon();
                        break;
                    }
                    case ARTEFACT_WEAPON:{
                        ArtefactWeapon *artefact_weapon = new ArtefactWeapon();
                        (*it)->SetItem(*artefact_weapon);
                        artefact_weapon->~ArtefactWeapon();
                        break;
                    }
                    case ENCHANTED_WEAPON:{
                        EnchantedWeapon *ench_weapon = new EnchantedWeapon();
                        (*it)->SetItem(*ench_weapon);
                        ench_weapon->~EnchantedWeapon();
                        break;
                    }
                    case POTION:{
                        Potion *potion = new Potion();
                        (*it)->SetItem(*potion);
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

        void CatacombsLevel::SetLevel(square& map){
            srand(time(0));
            this->size = {40, 20};
            this->case_array.clear();
            this->case_array.resize(this->size.y);//20 строк
            //std::vector <std::vector <Case>> ::iterator it = this->case_array.begin();
            for (int i = 0; i < this->size.y; i++){
                this->case_array[i].resize(this->size.x);//40 столбцов
                //it++;
            }
            
            for(int i = 0; i < this->size.y; i++){
                //std::vector <std::vector <Case>> ::iterator sub_it = it->begin();
                for (int j = 0; j < this->size.x; j++){
                    couple point = {i,j};
                    switch(map.lines[i][j]){
                            default: {
                                this->case_array[i][j] = Case(FLOOR, point);
                                break;
                            }
                            case '#': {
                                this->case_array[i][j] = Case(WALL, point);
                                break;
                            }
                            case '+': {
                                this->case_array[i][j] = Case(CLOSED_DOOR, point);
                                break;
                            }
                            case '&':{
                                Chest *chest = new Chest();
                                chest->SetLevelNumber((unsigned int)this->level_number);
                                chest->SetNumber(rand()%(int)(this->level_number + 1));
                                item_names name = POTION;
                                do{
                                    name = (item_names)(rand()%8 + 2);
                                }while (name == ARTEFACT);
                                switch(name){
                                    default:{
                                        Keychain* keychain = new Keychain();
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
                                        ArtefactArmor *artefact_armor = new ArtefactArmor();
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
                                this->case_array[i][j] = Case(FLOOR, point);
                                bool flag = this->case_array[i][j].SetChest(chest);
                                if (!flag)
                                    throw std::exception();
                                break;
                            }
                            case '>':{
                                this->case_array[i][j] = Case(STAIRS_DOWN, point);
                                break;
                            }
                            case '<':{
                                this->case_array[i][j] = Case(STAIRS_UP, point);
                                break;
                            }
                            case '@':{
                                this->case_array[i][j] = Case(PLAYER, point);
                                break;
                            }
                    }
                    if (map.lines[i][j] >= 97 && map.lines[i][j] <= 102){
                        this->case_array[i][j] = Case(ENEMY, point);
                    }
                }
            }
        }

        Player* CatacombsLevel::GetPlayer(){
            return this->player;
        }

        void CatacombsLevel::SetPlayer(Player* player){
            this->player = player;
        }

        std::vector <Enemy*> CatacombsLevel::GetEnemies(){
            return this->Enemies;
        }

        void CatacombsLevel::SetEnemy(Enemy& enemy){
            this->Enemies.push_back(&enemy);
        }

        void CatacombsLevel::OpenDoor(couple& point){
            std::vector <std::vector <Case>> ::iterator it = this->case_array.begin();
            it += point.y;
            std::vector <Case> ::iterator sub_it = it->begin();
            sub_it += point.x;
            if (sub_it->GetType() == CLOSED_DOOR)
                sub_it->SetType(OPENED_DOOR);
            else throw std::invalid_argument("It is not a door");
        }

        void CatacombsLevel::CloseDoor(couple &point){
            std::vector <std::vector <Case>> ::iterator it = this->case_array.begin();
            it += point.y;
            std::vector <Case> ::iterator sub_it = it->begin();
            sub_it += point.x;
            if (sub_it->GetType() == OPENED_DOOR)
                sub_it->SetType(CLOSED_DOOR);
            else throw std::invalid_argument("It is not a door");
        }

    void CatacombsLevel::SetPointType(couple& point, TYPE type, square& map, Enemy *enemy){
        int x = point.x;
        int y = point.y;
        case_array[y][x].SetType(type);
        switch(type){
            default: break;
            case FLOOR:{
                if(this->case_array[y][x].GetChest())
                    map.lines[x][y] = '&';
                if(this->case_array[y][x].GetItem()){
                    Item *item = this->case_array[y][x].GetItem();
                    switch(item->GetName()){
                        default: break;
                        case KEYCHAIN:{
                            map.lines[y][x] = '\'';
                            break;
                        }
                        case ARMOR:{
                            map.lines[y][x] = ']';
                            break;
                        }
                        case ARTEFACT_ARMOR:{
                            map.lines[y][x] = ']';
                            break;
                        }
                        case WEAPON:{
                            map.lines[y][x] = ')';
                            break;
                        }
                        case ARTEFACT_WEAPON:{
                            map.lines[y][x] = ')';
                            break;
                        }
                        case ENCHANTED_WEAPON:{
                            map.lines[y][x] = ')';
                            break;
                        }
                        case POTION:{
                            map.lines[y][x] = '!';
                            break;
                        }
                    }
                }
                map.lines[y][x] = '.';
                break;
            }
            case OPENED_DOOR:{
                map.lines[y][x] = '/';
                break;
            }
            case CLOSED_DOOR:{
                map.lines[y][x] = '+';
                break;
            }
            case WALL:{
                map.lines[y][x] = '#';
                break;
            }
            case STAIRS_UP:{
                map.lines[y][x] = '<';
                break;
            }
            case STAIRS_DOWN:{
                map.lines[y][x] = '>';
                break;
            }
            case PLAYER:{
                map.lines[y][x] = '@';
                break;
            }
            case ENEMY:{
                char letter = 97 + (int)(enemy->GetName());
                map.lines[y][x] = letter;
                break;
            }
        }
    }

    Case& CatacombsLevel::GetCase(couple &point){
        return this->case_array[point.y][point.x];
    }

    void CatacombsLevel::SetCase(Case& point, couple& there){
        this->case_array[there.y][there.x] = point;
    }

    TYPE CatacombsLevel::GetPointType(couple& point){
        int x = point.x;
        int y = point.y;
        return case_array[y][x].GetType();
    }

    unsigned int CatacombsLevel::GetLevel(){
        return level_number;
    }
    }
