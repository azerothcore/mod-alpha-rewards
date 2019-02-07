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

class AlphaRewards
{
public:

};

class AlphaRewardData : public DataMap::Base
{
public:
    AlphaRewardData() {}
    AlphaRewardData(uint32 RewardPoints) : RewardPointsMap(RewardPoints) {}
    uint32 RewardPointsMap = 0;
};

#define sAlphaRewards ACE_Singleton<CrossFaction, ACE_Null_Mutex>::instance()

#endif
