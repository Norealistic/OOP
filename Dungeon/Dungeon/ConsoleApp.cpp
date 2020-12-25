#include "ConsoleApp.hpp"

namespace Dungeon{


template <class T>
int getNum(T &a){
    std::cin>>a;
    if (!std::cin.good()){
        return -1;
    }
    return 1;
}

void InitLevels(level_numbers level, square& map, std::vector <CatacombsLevel>& level_list){
    //std::vector <CatacombsLevel> ::iterator it = level_list.begin();
    level_list[level].SetLevel(map);
    //number = (level_numbers)((int)(number + 1));
    //it++;
}

void UploadCharacters(struct PlayerStatement &user, level_numbers level, square& map, std::vector <CatacombsLevel> level_list, std::vector <std::vector <struct EnemyStatement>>& Level_enemies){
    srand(time(0));
    //user.current_level = (level_numbers)level_list[level].GetLevel();
    std::vector <Enemy*> sub_enemies = level_list[level].GetEnemies();
    std::vector <Enemy*> ::iterator this_enemy = sub_enemies.begin();
    level_list[level].SetPointType(user.current_point, PLAYER, map);
    std::vector <struct EnemyStatement> Line;
    for (int i = 0; i < sub_enemies.size(); i++, this_enemy++){
        EnemyStatement enemy;
        Enemy* someone = *this_enemy;
        enemy.enemy = someone;
        enemy.current_level = user.current_level;
        couple point;
        do{
            point = {rand()%40, rand()%20};
        }while(level_list[level].GetPointType(point) != FLOOR);
        enemy.current_point.x = point.x;
        enemy.current_point.y = point.y;
        if(enemy.enemy->GetDamageValue() != 0) level_list[level].SetPointType(point, ENEMY, map, &(**this_enemy));
        Line.push_back(enemy);
    }
    Level_enemies.at(level) = Line;
}

void DoorsMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    couple point = user.current_point;
    if (map.lines[point.y][point.x+1] == '+' || map.lines[point.y][point.x-1] == '+' || map.lines[point.y+1][point.x] == '+' || map.lines[point.y-1][point.x] == '+')
        std::cout << "  o. open door" << std::endl;
    if (map.lines[point.y][point.x+1] == '/' || map.lines[point.y][point.x-1] == '/' || map.lines[point.y+1][point.x] == '/' || map.lines[point.y-1][point.x] == '/')
        std::cout << "  c. close door" << std::endl;
}

void StepsMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    couple point = user.current_point;
    std::cout << "You can go..." << std::endl;
    if (map.lines[point.y-1][point.x] == '.')std::cout << "   w Up" << std::endl;
    if (map.lines[point.y+1][point.x] == '.')std::cout << "   s Down" << std::endl;
    if (map.lines[point.y][point.x-1] == '.')std::cout << "   a Left" << std::endl;
    if (map.lines[point.y][point.x+1] == '.')std::cout << "   d Right" << std::endl;
    if (map.lines[point.y+1][point.x] == '<' || map.lines[point.y-1][point.x] == '<' || map.lines[point.y][point.x-1] == '<' || map.lines[point.y][point.x+1] == '<')
        std::cout << "  <. Upstairs" << std::endl;
    if (map.lines[point.y][point.x+1] == '>' || map.lines[point.y][point.x-1] == '>' || map.lines[point.y-1][point.x] == '>' || map.lines[point.y+1][point.x] == '>')
        std::cout << "  >. Downstairs" << std::endl;
    DoorsMenu(user, map, level_list);
    std::cout << "  u. I want to upgrade..." << std::endl;
    std::cout << "  p. I want to drink..." << std::endl;
    std::cout << "  i. Info" << std::endl;
    if((map.lines[point.y][point.x+1] >= 97 && map.lines[point.y][point.x+1] <= 102) || (map.lines[point.y][point.x-1] >= 97 && map.lines[point.y][point.x-1] <= 102) || (map.lines[point.y-1][point.x] >= 97 && map.lines[point.y-1][point.x] <= 102) || (map.lines[point.y+1][point.x] >= 97 && map.lines[point.y+1][point.x] <= 102)) std::cout << "  e. Attack enemy" << std::endl;
    if (map.lines[point.y][point.x+1] == '&' || map.lines[point.y][point.x-1] == '&' || map.lines[point.y-1][point.x] == '&' || map.lines[point.y+1][point.x] == '&')
        std::cout << "  &. Open chest" << std::endl;
    if(map.lines[point.y][point.x+1] == '/' || map.lines[point.y][point.x-1] == '/' || map.lines[point.y-1][point.x] == '/' || map.lines[point.y+1][point.x] == '/')
        std::cout << "  t. Through the door" << std::endl;
    std::cout << "  . Not go, stay here" << std::endl;
}

void UpgradeCharacteristicsMenu(){
    std::cout << "1. Strength" << std::endl <<
    "2. Agility" << std::endl <<
    "3. Stamina" << std::endl <<
    "4. Health" << std::endl;
}

void UpgradeCharacteristics(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    UpgradeCharacteristicsMenu();
    int choice;
    getNum<int>(choice);
    feature name;
    switch(choice){
        default: break;
        case 1:{
            name = STRENGTH;
            break;
        }
        case 2:{
            name = AGILITY;
            break;
        }
        case 3:{
            name = STAMINA;
            break;
        }
        case 4:{
            name = HEALTH;
            break;
        }
    }
    user.player.UpgradeFeature(name);
}

void PotionsMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    std::vector <Potion> potion_list = user.player.PotionList();
    std::vector <Potion> ::iterator it = potion_list.begin();
    std::cout << "POTIONS: " << std::endl << std::endl;
    char number = 'A';
    for (int i = 0; i < potion_list.size(); i++){
        std::string name;
        if (it->GetModificator().type == STRENGTH) name = "strength";
        if (it->GetModificator().type == AGILITY) name = "agility";
        if (it->GetModificator().type == STAMINA) name = "stamina";
        if (it->GetModificator().type == HEALTH) name = "health";
        std::cout << number << ". " << name << ", " << it->GetModificator().current << std::endl;
        number = number+1;
    }
}

void DrinkPotion(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    std::cout << "You would like to drink potion to upgrade..." << std::endl;
    PotionsMenu(user, map, level_list);
    fflush(stdin);
    char choice;
    do{
        choice = getchar();
        fflush(stdin);
    }while (choice >= 65 && choice <= 90);
    std::vector <Potion> potion_list = user.player.PotionList();
    int number = (int)(choice - 64);
    Potion potion = potion_list[number];
    user.player.DrinkPotion(potion);
}


void ThroughTheDoor(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    couple point = user.current_point;
    if(map.lines[point.y][point.x+1] == '/')
        StepRight(user, map, level_list, 2);
    if(map.lines[point.y][point.x-1] == '/')
        StepLeft(user, map, level_list, 2);
    if(map.lines[point.y-1][point.x] == '/')
        StepUp(user, map, level_list, 2);
    if(map.lines[point.y+1][point.x] == '/')
        StepDown(user, map, level_list, 2);
}
void StepUp(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number){
    couple point = user.current_point;
    user.current_point.y -= dy*number;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user, map, level_list);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, map);
    level_list[level].SetPointType(user.current_point, PLAYER, map);
}

void StepDown(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number){
    couple point = user.current_point;
    user.current_point.y += dy*number;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user, map, level_list);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, map);
    level_list[level].SetPointType(user.current_point, PLAYER, map);
}


void StepRight(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number){
    couple point = user.current_point;
    user.current_point.x += dx*number;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user, map, level_list);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, map);
    level_list[level].SetPointType(user.current_point, PLAYER, map);
}


void StepLeft(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number){
    couple point = user.current_point;
    user.current_point.x -= dx*number;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user, map, level_list);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, map);
    level_list[level].SetPointType(user.current_point, PLAYER, map);
}


void OpenDoor(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    couple point = user.current_point;
    if (map.lines[point.y][point.x+dx] == '+'){
        point.x += dx;
        level_list[user.current_level].OpenDoor(point);
        map.lines[point.y][point.x] = '/';
    }
    if(map.lines[point.y][point.x-dx] == '+'){
        point.x -= dx;
        level_list[user.current_level].OpenDoor(point);
        map.lines[point.y][point.x] = '/';
    }
    if(map.lines[point.y+dy][point.x] == '+'){
        point.y += dy;
        level_list[user.current_level].OpenDoor(point);
        map.lines[point.y][point.x] = '/';
    }
    if(map.lines[point.y-dy][point.x] == '+'){
        point.y -= dy;
        level_list[user.current_level].OpenDoor(point);
        map.lines[point.y][point.x] = '/';
    }
}

void CloseDoor(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    couple point = user.current_point;
    if (map.lines[point.y][point.x+dx] == '+'){
        point.x += dx;
        level_list[user.current_level].CloseDoor(point);
        map.lines[point.y][point.x] = '/';
    }
    if(map.lines[point.y][point.x-dx] == '+'){
        point.x -= dx;
        level_list[user.current_level].CloseDoor(point);
        map.lines[point.y][point.x] = '/';
    }
    if(map.lines[point.y+dy][point.x] == '+'){
        point.y += dy;
        level_list[user.current_level].CloseDoor(point);
        map.lines[point.y][point.x] = '/';
    }
    if(map.lines[point.y-dy][point.x] == '+'){
        point.y -= dy;
        level_list[user.current_level].CloseDoor(point);
        map.lines[point.y][point.x] = '/';
    }
}

bool GoUpstairs(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, couple& start_point, std::vector <std::vector <struct EnemyStatement>>& Level_enemies){
    if (user.current_level != LEVEL_3){
        level_list[user.current_level].SetPointType(user.current_point, FLOOR, map);
        user.current_level = (level_numbers)((int)(user.current_level + 1));
        user.current_point = start_point;
        InitLevels(user.current_level, map, level_list);
        UploadCharacters(user, user.current_level, map, level_list, Level_enemies);
        return false;
    }
    else return true;
}

void GoDownstairs(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, couple& start_point, std::vector <std::vector <struct EnemyStatement>>& Level_enemies){
    if (user.current_level != LEVEL_1){
        level_list[user.current_level].SetPointType(user.current_point, FLOOR, map);
        user.current_level = (level_numbers)((int)(user.current_level - 1));
        user.current_point = start_point;
        InitLevels(user.current_level, map, level_list);
        UploadCharacters(user, user.current_level, map, level_list, Level_enemies);
    }
}

bool MakeStep(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, std::vector <std::vector <struct EnemyStatement>>& Level_enemies){
    bool flag = false;
    couple start_point = {0, 8};
    StepsMenu(user, map, level_list);
    fflush(stdin);
    char choice;
    do{
        choice = getchar();
        fflush(stdin);
    }while(choice != 'a' && choice != 'w' && choice != 's' && choice != 'd' && choice != 'o' && choice != 'c' && choice != '<' && choice != '>' && choice != '.' && choice != 'u' && choice != 'p' && choice != 'i' && choice != 'e' && choice != '&' && choice != 't');
    switch(choice){
        default: break;
        case 'a':{
            StepLeft(user, map, level_list, 1);
            couple point = user.current_point;
            if (map.lines[point.y][point.x] == '!' || map.lines[point.y][point.x] == ')' || map.lines[point.y][point.x] == ']' || map.lines[point.y][point.x] == '\'')
                GetItem(user, map, level_list);
            break;
        }
        case 'w':{
            StepUp(user, map, level_list, 1);
            couple point = user.current_point;
            if (map.lines[point.y][point.x] == '!' || map.lines[point.y][point.x] == ')' || map.lines[point.y][point.x] == ']' || map.lines[point.y][point.x] == '\'')
                GetItem(user, map, level_list);
            break;
        }
        case 's':{
            StepDown(user, map, level_list, 1);
            couple point = user.current_point;
            if (map.lines[point.y][point.x] == '!' || map.lines[point.y][point.x] == ')' || map.lines[point.y][point.x] == ']' || map.lines[point.y][point.x] == '\'')
                GetItem(user, map, level_list);
            break;
        }
        case 'd':{
            StepRight(user, map, level_list, 1);
            couple point = user.current_point;
            if (map.lines[point.y][point.x] == '!' || map.lines[point.y][point.x] == ')' || map.lines[point.y][point.x] == ']' || map.lines[point.y][point.x] == '\'')
                GetItem(user, map, level_list);
            break;
        }
        case 'o':{
            OpenDoor(user, map, level_list);
            break;
        }
        case 'c':{
            CloseDoor(user, map, level_list);
            break;
        }
        case '<':{
            flag = GoUpstairs(user, map, level_list, start_point, Level_enemies);
            break;
        }
        case '>':{
            GoDownstairs(user, map, level_list, start_point, Level_enemies);
            break;
        }
        case 'u':{
            UpgradeCharacteristics(user, map, level_list);
            break;
        }
        case 'p':{
            DrinkPotion(user, map, level_list);
            break;
        }
        case 'i':{
            PlayerInfo(user, map, level_list);
            break;
        }
        case 'e':{
            couple point = user.current_point;
            if(map.lines[point.y][point.x+dx] >= 97 && map.lines[point.y][point.x+dx] <= 102)
                point.x += dx;
            if(map.lines[point.y][point.x-dx] >= 97 && map.lines[point.y][point.x-dx] <= 102)
                point.x -= dx;
            if(map.lines[point.y+dy][point.x] >= 97 && map.lines[point.y+dy][point.x] <= 102)
                point.y += dy;
            if(map.lines[point.y-dy][point.x] >= 97 && map.lines[point.y-dy][point.x] <= 102)
                point.y += dy;
            EnemyStatement enemy;
            for (int i = 0; i < Level_enemies[user.current_level].size(); i++){
                if (Level_enemies[user.current_level][i].current_point.x == point.x &&  Level_enemies[user.current_level][i].current_point.y == point.y){
                    enemy = Level_enemies[user.current_level][i];
                }
            }
            AttackEmeny(user, enemy, map, level_list);
            break;
        }

        case '&':{
            OpenChest(user, map, level_list);
            break;
        }
        case 't':{
            ThroughTheDoor(user, map, level_list);
            break;
        }
        case '.': break;
    }
    return flag;
}

void WeaponMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    std::cout << "WEAPON:" << std::endl << std::endl;
    std::vector <Weapon> weapon = user.player.WeaponList();
    std::vector <Weapon> ::iterator it = weapon.begin();
    if (weapon.size() > 0){
    while (it != weapon.end()){
        std::string info = "    ";
        switch(it->GetName()){
            default: break;
            case WEAPON:{
                info += str_item_names[WEAPON] + ", " + std::to_string((int)it->GetDamageValue());
                break;
            }
            case ENCHANTED_WEAPON:{
                EnchantedWeapon *ench = dynamic_cast<EnchantedWeapon*>(&(*it));
                info += str_item_names[ENCHANTED_WEAPON] + ", " + str_enemy_names[ench->GetEnemyTypeUp()] + ", " + std::to_string((int)(ench->GetDamageValue()*ench->GetIndex())) + ", " + str_enemy_names[ench->GetEnemyTypeDown()] + ", " +
                std::to_string((int)(ench->GetDamageValue()/ench->GetIndex()));
                break;
            }
            case ARTEFACT_WEAPON:{
                ArtefactWeapon *art = dynamic_cast<ArtefactWeapon*>(&(*it));
                info += str_item_names[ARTEFACT_WEAPON] + ", " + std::to_string((int)art->GetDamageValue()) + ", ";
                std::vector <characteristic> list = art->GetModificators();
                std::vector <characteristic> ::iterator sub_it = list.begin();
                while (sub_it != list.end()){
                    info += str_feature_names[sub_it->type] + ", +" + std::to_string((int)sub_it->current);
                    if (sub_it++ != list.end()) info += ", ";
                    sub_it++;
                }
                break;
            }
        }
        std::cout << info << std::endl;
        it++;
    }
    }
    std::cout << "... in your bag" << std::endl;
}

void ArmorMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    std::cout << "ARMOR: " << std::endl << std::endl;
    MyVector <Armor> armor = user.player.ArmorList();
    MyIterator <Armor> it = armor.Begin();
    if (armor.current_size() > 0){
    while(it != armor.End()){
        std::string info = "    ";
        switch((*it)->GetName()){
            default: break;
            case ARMOR:{
                info += str_item_names[ARMOR] + ", " + std::to_string((int)(*it)->GetDefenceValue()) + ", " + str_armor_types[(*it)->GetType()];
                break;
            }
            case ARTEFACT_ARMOR:{
                ArtefactArmor *art = dynamic_cast<ArtefactArmor*>(*it);
                info += str_item_names[ARTEFACT_ARMOR] + ", " + std::to_string((int)art->GetDefenceValue()) + ", ";
                std::vector <characteristic> list = art->GetModificators();
                std::vector <characteristic> ::iterator sub_it = list.begin();
                while (sub_it != list.end()){
                    info += str_feature_names[sub_it->type] + ", +" + std::to_string((int)sub_it->current);
                    if (sub_it++ != list.end()) info += ", ";
                    sub_it++;
                }
                break;
            }
        }
        std::cout << info << std::endl;
        it++;
    }
    }
    std::cout << "... in your bag" << std::endl;
}

void PlayerInfo(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    PotionsMenu(user, map, level_list);
    WeaponMenu(user, map, level_list);
    ArmorMenu(user, map, level_list);
    std::cout << "experience: " << user.player.GetExperience() << std::endl;
    std::vector <characteristic> feature_table = user.player.GetFeatures();
    std::vector <characteristic> ::iterator it = feature_table.begin();
    while (it != feature_table.end()){
        std::cout << str_feature_names[it->type] << ": " << it->current << std::endl;
        it++;
    }
    /*if(user.player.GetWeapon() != nullptr){
    Weapon* weapon = user.player.GetWeapon();
    switch (weapon->GetName()){
        default: break;
        case WEAPON:{
            std::cout << str_item_names[WEAPON] << ": " << weapon->GetDamageValue() << std::endl;
            break;
        }
        case ENCHANTED_WEAPON:{
            EnchantedWeapon *ench = dynamic_cast<EnchantedWeapon*>(weapon);
            std::cout << str_item_names[ENCHANTED_WEAPON] << ": " << str_enemy_names[ench->GetEnemyTypeUp()] << ", " << ench->GetIndex()*ench->GetDamageValue() << ", " << str_enemy_names[ench->GetEnemyTypeDown()] << ", " << ench->GetDamageValue()/ench->GetIndex();
            break;
        }
        case ARTEFACT_WEAPON:{
            ArtefactWeapon *art = dynamic_cast<ArtefactWeapon*>(weapon);
            std::cout << str_item_names[ARTEFACT_WEAPON] << ": " << art->GetDamageValue() << std::endl;
            std::vector <characteristic> list = art->GetModificators();
            std::vector <characteristic> ::iterator sub_it = list.begin();
            while (sub_it != list.end()){
                std::cout << "  " << str_feature_names[sub_it->type] << ": +" << sub_it->current << std::endl;
                sub_it++;
            }
            break;
        }
    }
    }
    MyVector <Armor> armor = user.player.GetArmor();
    MyIterator <Armor> my_it = armor.Begin();
    for(int i = 0; i < armor.current_size(); i++, my_it++){
        switch((*my_it)->GetName()){
            default: break;
            case ARMOR:{
                std::cout << str_item_names[ARMOR] << ": " << (*my_it)->GetDefenceValue() << ", " << str_armor_types[(*my_it)->GetType()] << std::endl;
                break;
            }
            case ARTEFACT_ARMOR:{
                std::cout << str_item_names[ARMOR] << ": " << (*my_it)->GetDefenceValue() << ", " << str_armor_types[(*my_it)->GetType()] << std::endl;
                ArtefactArmor *art = dynamic_cast<ArtefactArmor*>(*my_it);
                std::vector <characteristic> modificators = art->GetModificators();
                std::vector <characteristic> ::iterator mod = modificators.begin();
                while (mod != modificators.end()){
                    std::cout << "  " << str_feature_names[mod->type] << ": +" << mod->current << std::endl;
                    mod++;
                }
            }
        }
    }*/
    std::cout << "Key quantity: " << user.player.GetKeyNumber() << std::endl;
}

void AttackEmeny(struct PlayerStatement &user, struct EnemyStatement &enemy, square& map, std::vector <CatacombsLevel> level_list){
    characteristic enemy_health = {HEALTH, 0, 0};
    characteristic player_health = {HEALTH, 0, 0};
    do{
        user.player.GenerateDamage(*(enemy.enemy));
        enemy.enemy->GenerateDamage(user.player);
        std::vector <characteristic> enemys = enemy.enemy->GetFeatures();
        enemy_health = enemys[0];
        std::vector <characteristic> players = user.player.GetFeatures();
        std::vector <characteristic> ::iterator it = players.begin();
        while (it->type != HEALTH) it++;
        player_health = *it;
    }while(player_health.current != 0 && enemy_health.current != 0);
    if (enemy_health.current == 0){
        std::vector <Item> items = enemy.enemy->GetItems();
        std::vector <Item> ::iterator it = items.begin();
        couple point = enemy.current_point;
        Case& cassse = level_list[enemy.current_level].GetCase(point);
        cassse.SetItem(&(*it));
        level_list[enemy.current_level].SetCase(cassse, point);
        level_list[enemy.current_level].SetPointType(point, FLOOR, map);
        enemy.enemy->~Enemy();
    }
    if (player_health.current == 0)
        throw "I'm dead";
}

void GetItem(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list){
    Case& current = level_list[user.current_level].GetCase(user.current_point);
    switch(current.GetItem()->GetName()){
        default: break;
        case KEYCHAIN:{
            int keys = user.player.GetKeyNumber();
            user.player.SetKeyNumber(keys+1);
            break;
        }
        case ARMOR:{
            Armor *armor = dynamic_cast<Armor*>(current.GetItem());
            user.player.TakeArmor(*armor);
            break;
        }
        case WEAPON:{
            Weapon *weapon = dynamic_cast<Weapon*>(current.GetItem());
            user.player.TakeWeapon(*weapon);
            break;
        }
        case POTION:{
            Potion *potion = dynamic_cast<Potion*>(current.GetItem());
            user.player.SetPotion(*potion);
            break;
        }
        case ARTEFACT_ARMOR:{
            ArtefactArmor *armor = dynamic_cast<ArtefactArmor*>(current.GetItem());
            user.player.TakeArmor(*armor);
            break;
        }
        case ARTEFACT_WEAPON:{
            ArtefactWeapon *weapon = dynamic_cast<ArtefactWeapon*>(current.GetItem());
            user.player.TakeWeapon(*weapon);
            break;
        }
        case ENCHANTED_WEAPON:{
            EnchantedWeapon *weapon = dynamic_cast<EnchantedWeapon*>(current.GetItem());
            user.player.TakeWeapon(*weapon);
            break;
        }
    }
    current.SetItem(nullptr);
}

void OpenChest(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel>& level_list){
    Case place;
    couple points[4] = {{user.current_point.x, user.current_point.y+dy}, {user.current_point.x, user.current_point.y-dy}, {user.current_point.x+dx, user.current_point.y}, {user.current_point.x-dx, user.current_point.y}};
    couple *current = points;
    do{
        place = level_list[user.current_level].GetCase(*current);
        current++;
    }while(current && !place.GetChest());
    current--;
    try{
        place.GetChest()->OpenAttempt(user.player);
    }
    catch(const std::invalid_argument &er){
        std::cout << er.what() << std::endl;
        return;
    }
    Item *item = place.GetChest()->GetItem();
    place.SetChest(nullptr);
    place.SetItem(item);
    level_list[user.current_level].SetCase(place, *current);
    level_list[user.current_level].SetPointType(*current, FLOOR, map);
    switch(item->GetName()){
        default: break;
        case KEYCHAIN:{
            int keys = user.player.GetKeyNumber();
            user.player.SetKeyNumber(keys+1);
            break;
        }
        case ARMOR:{
            Armor *armor = dynamic_cast<Armor*>(item);
            user.player.TakeArmor(*armor);
            break;
        }
        case WEAPON:{
            Weapon *weapon = dynamic_cast<Weapon*>(item);
            user.player.TakeWeapon(*weapon);
            break;
        }
        case POTION:{
            Potion *potion = new Potion();
            potion = dynamic_cast<Potion*>(item);
            user.player.SetPotion(*potion);
            break;
        }
        case ARTEFACT_ARMOR:{
            ArtefactArmor *armor = dynamic_cast<ArtefactArmor*>(item);
            user.player.TakeArmor(*armor);
            break;
        }
        case ARTEFACT_WEAPON:{
            ArtefactWeapon *weapon = dynamic_cast<ArtefactWeapon*>(item);
            user.player.TakeWeapon(*weapon);
            break;
        }
        case ENCHANTED_WEAPON:{
            EnchantedWeapon *weapon = dynamic_cast<EnchantedWeapon*>(item);
            user.player.TakeWeapon(*weapon);
            break;
        }
    }
}

void Output(square& map){
    map_output(map);
}
}
