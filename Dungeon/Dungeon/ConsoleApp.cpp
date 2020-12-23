#include "ConsoleApp.hpp"

namespace Dungeon{


void InitLevels(){
    std::vector <CatacombsLevel> ::iterator it = level_list.begin();
    level_numbers number = LEVEL_1;
    for (int i = 0; i<3; i++){
        it->SetLevel(number);
        number = (level_numbers)((int)(number + 1));
        it++;
    }
}

void UploadCharacters(CatacombsLevel& level){
    srand((unsigned int)time(0));
    std::vector <Enemy> sub_enemies = level.GetEnemies();
    std::vector <Enemy> ::iterator this_enemy = sub_enemies.begin();
    User.current_level = (level_numbers)level.GetLevel();
    level.SetPointType(User.current_point, PLAYER, User.current_level, nullptr);
    for (int i = 0; i < sub_enemies.size(); i++, this_enemy++){
        EnemyStatement enemy;
        enemy.enemy = *this_enemy;
        enemy.current_level = User.current_level;
        couple point;
        do{
            point = {rand()%40, rand()%20};
        }while(level.GetPointType(point) != FLOOR);
        enemy.current_point.x = point.x;
        enemy.current_point.y = point.y;
        level.SetPointType(point, ENEMY, User.current_level, &(*this_enemy));
        switch(level.GetLevel()){
            default:{
                Level1_enemies.push_back(enemy);
                break;
                }
            case 2:{
                Level2_enemies.push_back(enemy);
                break;
            }
            case 3:{
                Level3_enemies.push_back(enemy);
                break;
            }
        }
    }
}

void DoorsMenu(struct PlayerStatement &user){
    couple point = user.current_point;
    if (map_catalog[user.current_level].lines[point.x][point.y+1] == '+' || map_catalog[user.current_level].lines[point.x][point.y-1] == '+' || map_catalog[user.current_level].lines[point.x+1][point.y] == '+' || map_catalog[user.current_level].lines[point.x-1][point.y] == '+')
        std::cout << "  o. open door" << std::endl;
    if (map_catalog[user.current_level].lines[point.x][point.y+1] == '/' || map_catalog[user.current_level].lines[point.x][point.y-1] == '/' || map_catalog[user.current_level].lines[point.x+1][point.y] == '/' || map_catalog[user.current_level].lines[point.x-1][point.y] == '/')
        std::cout << "  c. close door" << std::endl;
}

void StepsMenu(struct PlayerStatement &user){
    couple point = user.current_point;
    std::cout << "You can go..." << std::endl;
    if (map_catalog[user.current_level].lines[point.x][point.y+1] == '.')std::cout << "   w Up" << std::endl;
    if (map_catalog[user.current_level].lines[point.x][point.y-1] == '.')std::cout << "   s Down" << std::endl;
    if (map_catalog[user.current_level].lines[point.x-1][point.y] == '.')std::cout << "   a Left" << std::endl;
    if (map_catalog[user.current_level].lines[point.x+1][point.y] == '.')std::cout << "   d Right" << std::endl;
    if (map_catalog[user.current_level].lines[point.x][point.y+1] == '<' || map_catalog[user.current_level].lines[point.x][point.y-1] == '<' || map_catalog[user.current_level].lines[point.x-1][point.y] == '<' || map_catalog[user.current_level].lines[point.x+1][point.y] == '<')
        std::cout << "  <. Upstairs" << std::endl;
    if (map_catalog[user.current_level].lines[point.x][point.y+1] == '>' || map_catalog[user.current_level].lines[point.x][point.y-1] == '>' || map_catalog[user.current_level].lines[point.x-1][point.y] == '>' || map_catalog[user.current_level].lines[point.x+1][point.y] == '>')
        std::cout << "  >. Downstairs" << std::endl;
    DoorsMenu(user);
    std::cout << "  . Not go, stay here" << std::endl;
}

void UpgradeCharacteristicsMenu(){
    std::cout << "1. Strength" << std::endl <<
    "2. Agility" << std::endl <<
    "3. Stamina" << std::endl <<
    "4. Health" << std::endl;
}

void UpgradeCharacteristics(struct PlayerStatement &user){
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

void PotionsMenu(struct PlayerStatement &user){
    std::vector <Potion *> potion_list = user.player.PotionList();
    std::vector <Potion *> ::iterator it = potion_list.begin();
    char number = 'A';
    for (int i = 0; i < potion_list.size(); i++){
        std::string name;
        if ((*it)->GetModificator().type == STRENGTH) name = "strength";
        if ((*it)->GetModificator().type == AGILITY) name = "agility";
        if ((*it)->GetModificator().type == STAMINA) name = "stamina";
        if ((*it)->GetModificator().type == HEALTH) name = "health";
        std::cout << number << ". " << name << ", " << (*it)->GetModificator().current << std::endl;
        number = number+1;
    }
}

void DrinkPotion(struct PlayerStatement &user){
    std::cout << "You would like to drink potion to upgrade..." << std::endl;
    PotionsMenu(user);
    fflush(stdin);
    char choice;
    do{
        choice = getchar();
        fflush(stdin);
    }while (choice >= 65 && choice <= 90);
    std::vector <Potion *> potion_list = user.player.PotionList();
    int number = (int)(choice - 64);
    Potion *potion = potion_list[number];
    user.player.DrinkPotion(*potion);
}

void StepUp(struct PlayerStatement &user){
    couple point = user.current_point;
    user.current_point.y += dy;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, level, nullptr);
    level_list[level].SetPointType(user.current_point, PLAYER, level, nullptr);
}

void StepDown(struct PlayerStatement &user){
    couple point = user.current_point;
    user.current_point.y -= dy;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, level, nullptr);
    level_list[level].SetPointType(user.current_point, PLAYER, level, nullptr);
}


void StepRight(struct PlayerStatement &user){
    couple point = user.current_point;
    user.current_point.x += dx;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, level, nullptr);
    level_list[level].SetPointType(user.current_point, PLAYER, level, nullptr);
}


void StepLeft(struct PlayerStatement &user){
    couple point = user.current_point;
    user.current_point.x -= dx;
    level_numbers level = user.current_level;
    Case place = level_list[level].GetCase(user.current_point);
    if (place.GetItem()){
        GetItem(user);
        level_list[level].SetCase(place, user.current_point);
    }
    level_list[level].SetPointType(point, FLOOR, level, nullptr);
    level_list[level].SetPointType(user.current_point, PLAYER, level, nullptr);
}


void OpenDoor(struct PlayerStatement &user){
    couple point = user.current_point;
    if (map_catalog[user.current_level].lines[point.x][point.y+1] == '+'){
        point.y += dy;
        level_list[user.current_level].OpenDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '/';
    }
    if(map_catalog[user.current_level].lines[point.x][point.y-1] == '+'){
        point.y -= dy;
        level_list[user.current_level].OpenDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '/';
    }
    if(map_catalog[user.current_level].lines[point.x+1][point.y] == '+'){
        point.x += dx;
        level_list[user.current_level].OpenDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '/';
    }
    if(map_catalog[user.current_level].lines[point.x-1][point.y] == '+'){
        point.x -= dx;
        level_list[user.current_level].OpenDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '/';
    }
}

void CloseDoor(struct PlayerStatement &user){
    couple point = user.current_point;
    if (map_catalog[user.current_level].lines[point.x][point.y+1] == '/'){
        point.y += dy;
        level_list[user.current_level].CloseDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '+';
    }
    if(map_catalog[user.current_level].lines[point.x][point.y-1] == '/'){
        point.y -= dy;
        level_list[user.current_level].CloseDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '+';
    }
    if(map_catalog[user.current_level].lines[point.x+1][point.y] == '/'){
        point.x += dx;
        level_list[user.current_level].CloseDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '+';
    }
    if(map_catalog[user.current_level].lines[point.x-1][point.y] == '/'){
        point.x -= dx;
        level_list[user.current_level].CloseDoor(point);
        map_catalog[user.current_level].lines[point.x][point.y] = '+';
    }
}

void GoUpstairs(struct PlayerStatement &user){
    user.current_level = (level_numbers)((int)(user.current_level + 1));
    user.current_point = start_point;
}

void GoDownstairs(struct PlayerStatement &user){
    if (user.current_level != LEVEL_1){
        user.current_level = (level_numbers)((int)(user.current_level - 1));
        user.current_point = start_point;
    }
}

void MakeStep(struct PlayerStatement &user){
    StepsMenu(user);
    fflush(stdin);
    char choice;
    do{
        choice = getchar();
        fflush(stdin);
    }while(choice != 'a' && choice != 'w' && choice != 's' && choice != 'd' && choice != 'o' && choice != 'c' && choice != '<' && choice != '>' && choice != '.');
    switch(choice){
        default: break;
        case 'a':{
            StepLeft(user);
            break;
        }
        case 'w':{
            StepUp(user);
            break;
        }
        case 's':{
            StepDown(user);
            break;
        }
        case 'd':{
            StepRight(user);
            break;
        }
        case 'o':{
            OpenDoor(user);
            break;
        }
        case 'c':{
            CloseDoor(user);
            break;
        }
        case '<':{
            GoUpstairs(user);
            break;
        }
        case '>':{
            GoDownstairs(user);
            break;
        }
        case '.': break;
    }
}

void WeaponMenu(struct PlayerStatement &user){
    std::cout << "There are..." << std::endl;
    std::vector <Weapon *> weapon = user.player.WeaponList();
    std::vector <Weapon *> ::iterator it = weapon.begin();
    while (it != weapon.end()){
        std::string info = "    ";
        switch((*it)->GetName()){
            default: break;
            case WEAPON:{
                info += str_item_names[WEAPON] + ", " + std::to_string((int)(*it)->GetDamageValue());
                break;
            }
            case ENCHANTED_WEAPON:{
                EnchantedWeapon *ench = dynamic_cast<EnchantedWeapon*>((*it));
                info += str_item_names[ENCHANTED_WEAPON] + ", " + str_enemy_names[ench->GetEnemyTypeUp()] + ", " + std::to_string((int)(ench->GetDamageValue()*ench->GetIndex())) + ", " + str_enemy_names[ench->GetEnemyTypeDown()] + ", " +
                std::to_string((int)(ench->GetDamageValue()/ench->GetIndex()));
                break;
            }
            case ARTEFACT_WEAPON:{
                ArtefactWeapon *art = dynamic_cast<ArtefactWeapon*>((*it));
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
    }
    std::cout << "... in your bag" << std::endl;
}

void ArmorMenu(struct PlayerStatement &user){
    std::cout << "There are..." << std::endl;
    std::vector <Armor *> armor = user.player.ArmorList();
    std::vector <Armor *> ::iterator it = armor.begin();
    while(it != armor.end()){
        std::string info = "    ";
        switch((*it)->GetName()){
            default: break;
            case ARMOR:{
                info += str_item_names[ARMOR] + ", " + std::to_string((int)(*it)->GetDefenceValue()) + ", " + str_armor_types[(*it)->GetType()];
                break;
            }
            case ARTEFACT_ARMOR:{
                ArtefactArmor *art = dynamic_cast<ArtefactArmor*>((*it));
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
    }
    std::cout << "... in your bag" << std::endl;
}

void PlayerInfo(struct PlayerStatement &user){
    PotionsMenu(user);
    WeaponMenu(user);
    ArmorMenu(user);
    std::cout << "experience: " << user.player.GetExperience() << std::endl;
    std::vector <characteristic> feature_table = user.player.GetFeatures();
    std::vector <characteristic> ::iterator it = feature_table.begin();
    while (it != feature_table.end()){
        std::cout << str_feature_names[it->type] << ": " << it->current << std::endl;
    }
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
    }
    std::cout << "Key quantity: " << user.player.GetKeyNumber() << std::endl;
}

    void AttackEmeny(struct PlayerStatement &user, struct EnemyStatement &enemy){
        characteristic enemy_health = {HEALTH, 0, 0};
        characteristic player_health = {HEALTH, 0, 0};
        do{
            user.player.GenerateDamage(enemy.enemy);
            enemy.enemy.GenerateDamage(user.player);
            std::vector <characteristic> enemys = enemy.enemy.GetFeatures();
            enemy_health = enemys[0];
            std::vector <characteristic> players = user.player.GetFeatures();
            std::vector <characteristic> ::iterator it = players.begin();
            while (it->type != HEALTH) it++;
            player_health = *it;
        }while(player_health.current != 0 && enemy_health.current != 0);
        if (enemy_health.current == 0){
            std::vector <Item *> items = enemy.enemy.GetItems();
            std::vector <Item *> ::iterator it = items.begin();
            couple point = enemy.current_point;
            Case& cassse = level_list[enemy.current_level].GetCase(point);
            cassse.SetItem((*it));
            level_list[enemy.current_level].SetCase(cassse, point);
            level_list[enemy.current_level].SetPointType(point, FLOOR, enemy.current_level, nullptr);
        }
        if (player_health.current == 0)
            throw "I'm dead";
    }

    void GetItem(struct PlayerStatement &user){
        Case& current = level_list[user.current_level].GetCase(user.current_point);
        user.player.SetItem(current.GetItem());
        current.SetItem(nullptr);
    }

    void OpenChest(struct PlayerStatement &user){
        Case place;
        couple points[4] = {{user.current_point.x, user.current_point.y+dy}, {user.current_point.x, user.current_point.y-dy}, {user.current_point.x+dx, user.current_point.y}, {user.current_point.x-dx, user.current_point.y}};
        couple *current = points;
        do{
            place = level_list[user.current_level].GetCase(*current);
            current++;
        }while(current && !place.GetChest());
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
        level_list[user.current_level].SetPointType(*current, FLOOR, user.current_level, nullptr);
    }



}

