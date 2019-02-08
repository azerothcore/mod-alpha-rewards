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
    std::unordered_map<uint32, uint32> AlphaQuestPointsMap;
};

class AlphaRewardData : public DataMap::Base
{
public:
    AlphaRewardData() {}
    AlphaRewardData(uint32 RewardPoints) : RewardPointsMap(RewardPoints) {}
    uint32 RewardPointsMap = 0;
};

#define sAlphaRewards ACE_Singleton<AlphaRewards, ACE_Null_Mutex>::instance()

#endif
