#pragma once
#define dx 1
#define dy 1
#include "Dungeon_Level.h"

namespace Dungeon{

    static Player user;
    const couple start_point = {1, 15};//для простоты определена одна и та же точка начала уровня
    //couple current_point = start_point;//текущее местоположение игрока

    struct PlayerStatement{
        Player player;
        couple current_point;
        level_numbers current_level;
    };

    struct EnemyStatement{
        Enemy enemy;
        couple current_point;
        level_numbers current_level;
    };

    static struct PlayerStatement User = {user, start_point, LEVEL_1};

    static std::vector <CatacombsLevel> level_list(3);
    static std::vector <struct EnemyStatement> Level1_enemies;
    static std::vector <struct EnemyStatement> Level2_enemies;
    static std::vector <struct EnemyStatement> Level3_enemies;

    template <class T>
        int getNum(T &a){
            std::cin>>a;
            if (!std::cin.good()){
                return -1;
            }
            return 1;
        }

    void StepsMenu(struct PlayerStatement &user);
    //void StepUp(struct CharacterStatement &user);//шагнуть
    void UpgradeCharacteristicsMenu();
    void UpgradeCharacteristics(struct PlayerStatement &user);
    void PotionsMenu(struct PlayerStatement &user);
    void DoorsMenu(struct PlayerStatement &user);
    void WeaponMenu(struct PlayerStatement &user);
    void ArmorMenu(struct PlayerStatement &user);
    void PlayerInfo(struct PlayerStatement &user);
    void StepUp(struct PlayerStatement &user);
    void StepDown(struct PlayerStatement &user);
    void StepRight(struct PlayerStatement &user);
    void StepLeft(struct PlayerStatement &user);
    void ChangeArmor(struct PlayerStatement &user);
    void ChangeWeapon(struct PlayerStatement &user);
    void DrinkPotion(struct PlayerStatement &user);
    void AttackEmeny(struct PlayerStatement &user, struct EnemyStatement &enemy);
    void GetItem(struct PlayerStatement &user);
    void OpenChest(struct PlayerStatement &user);
        void OpenDoor(struct PlayerStatement &user);
        void CloseDoor(struct PlayerStatement &user);
        void GoUpstairs(struct PlayerStatement &user);
        void GoDownstairs(struct PlayerStatement &user);
        void MakeStep(struct PlayerStatement &user);

        void InitLevels();
        void UploadCharacters(CatacombsLevel& level);
}

