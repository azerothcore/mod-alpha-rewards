#include "ScriptMgr.h"
#include "Player.h"
#include "Map.h"
#include "ObjectAccessor.h"
#include "QuestDef.h"
#include "DataMap.h"
#include "mod-alpha-rewards.h"
#include "ace/ACE.h"
#include <map>
#include <string>

void AlphaRewards::OnLoginCheck(Player* player)
{
    QueryResult result = LoginDatabase.PQuery("SELECT `game_point` FROM `account` WHERE `id` = '%u' ", player->GetSession()->GetAccountId());

    if (!result)
        return;

    Field* fields = result->Fetch();
    uint32& points = player->CustomData.GetDefault< AlphaRewardData>("Points")->RewardPointsMap;
    points = fields[0].GetUInt32();
}

void AlphaRewards::OnLogoutUpdate(Player* player)
{
    if (AlphaRewardData* data = player->CustomData.Get<AlphaRewardData>("RewardPointsMap"))
    {
        uint32 reward = data->RewardPointsMap;
        LoginDatabase.DirectPExecute("UPDATE `account` SET `game_point` = '%u' WHERE `id` = '%u'", reward, player->GetSession()->GetAccountId());
    }
}

void AlphaRewards::AddGamePoint(Player* player, uint32 game_point)
{
    player->CustomData.GetDefault<AlphaRewardData>("RewardPointsMap")->RewardPointsMap += game_point;
}

void AlphaRewards::LoadAlphaRewardsTable()
{
    sLog->outString("Loading Quest Reward System...");

    QueryResult result = WorldDatabase.PQuery("SELECT `Entry`, `TypeId`, `Points` FROM `alpha_reward_system`");

    if (!result)
    {
        sLog->outErrorDb(">>  Loaded 0 AlphaQuestPoints. DB table `AlphaQuestPoints` is empty!");
        sLog->outString();
        return;
    }

    uint32 count = 0;
    uint32 oldMSTime = getMSTime();

    do
    {
        Field* field = result->Fetch();

        switch (field[1].GetInt32())
        {
        case 1: // Creature
            sAlphaRewards->AlphaCreaturePointsMap.emplace(field[0].GetUInt32(), field[2].GetUInt32());
            break;
        case 2: // Quest Map
            sAlphaRewards->AlphaQuestPointsMap.emplace(field[0].GetUInt32(), field[2].GetUInt32());
            break;
        case 3: //Achievement
            sAlphaRewards->AlphaAchievementPointsMap.emplace(field[0].GetUInt32(), field[2].GetUInt32());
            break;
        }

        count++;

    } while (result->NextRow());

    sLog->outString(">> Loaded %u AlphaQuestPoints in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString("");
}
