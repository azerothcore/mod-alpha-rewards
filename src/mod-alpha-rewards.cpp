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
    player->CustomData.Set("RewardPointsMap", new AlphaRewardData(fields[0].GetInt32()));
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
