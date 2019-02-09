#ifndef ALPHAREWARDS_H
#define ALPHAREWARDS_H

#include "ScriptMgr.h"
#include "Language.h"
#include "Player.h"
#include "Vehicle.h"
#include "ObjectAccessor.h"
#include "Group.h"
#include "Map.h"
#include "Log.h"
#include "Opcodes.h"
#include <vector>
#include <algorithm>
#include "BattlegroundMgr.h"
#include <map>
#include <unordered_map>

class AlphaRewards
{
public:
    void OnLoginCheck(Player* player);
    void OnLogoutUpdate(Player* player);
    void AddGamePoint(Player* player, uint32 game_point);
    void LoadAlphaRewardsTable();
    std::unordered_map<uint32, uint32> AlphaQuestPointsMap;
    std::unordered_map<uint32, uint32> AlphaCreaturePointsMap;
    std::unordered_map<uint32, uint32> AlphaAchievementPointsMap;
};

class AlphaRewardData : public DataMap::Base
{
public:
    AlphaRewardData() { reset(); }
    AlphaRewardData(uint32 RewardPoints) : RewardPointsMap(RewardPoints), timer(timer) {}
    uint32 timer = 2*HOUR*IN_MILLISECONDS; // make this config Driven and rmoev below void Reset();
    uint32 RewardPointsMap = 0;

    void reset()
    {
        /*
        for when config is added

        timer = static_cast<uint32>(sConfigMgr->GetIntDefault("RewardPlayTime", 2))*HOUR*IN_MILLISECONDS;

        */
        timer = static_cast <uint32>(2)* HOUR*IN_MILLISECONDS; 
    }
};

#define sAlphaRewards ACE_Singleton<AlphaRewards, ACE_Null_Mutex>::instance()

#endif
