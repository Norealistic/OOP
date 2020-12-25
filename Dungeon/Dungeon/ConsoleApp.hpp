#pragma once
#define dx 1
#define dy 1
#include "Dungeon_Level.h"

namespace Dungeon{

    struct PlayerStatement{
        Player player;
        couple current_point;
        level_numbers current_level;
    };

    struct EnemyStatement{
        Enemy* enemy;
        couple current_point;
        level_numbers current_level;
    };

    template <class T>
    int getNum(T &a);

    void StepsMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void UpgradeCharacteristicsMenu();
    void UpgradeCharacteristics(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void PotionsMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void DoorsMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void WeaponMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void ArmorMenu(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void PlayerInfo(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void StepUp(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number);
    void StepDown(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number);
    void StepRight(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number);
    void StepLeft(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, int number);
    void DrinkPotion(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void AttackEmeny(struct PlayerStatement &user, struct EnemyStatement &enemy, square& map, std::vector <CatacombsLevel> level_list);
    void GetItem(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void OpenChest(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel>& level_list);
    void OpenDoor(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    void CloseDoor(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    bool GoUpstairs(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, couple& start_point, std::vector <std::vector <struct EnemyStatement>>& Level_enemies);
    void GoDownstairs(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, couple& start_point, std::vector <std::vector <struct EnemyStatement>>& Level_enemies);
    void ThroughTheDoor(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list);
    bool MakeStep(struct PlayerStatement &user, square& map, std::vector <CatacombsLevel> level_list, std::vector <std::vector <struct EnemyStatement>>& Level_enemies);
    void InitLevels(level_numbers level, square& map, std::vector <CatacombsLevel>& level_list);
    void UploadCharacters(struct PlayerStatement &user, level_numbers level, square& map, std::vector <CatacombsLevel> level_list, std::vector <std::vector <struct EnemyStatement>>& Level_enemies);
    void Output(square& map);
}

