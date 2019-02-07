#include "ScriptMgr.h"
#include "Player.h"
#include "Map.h"
#include "ObjectAccessor.h"
#include "QuestDef.h"
#include "DataMap.h"
#include "mod-alpha-rewards.h"


class AlphaRewardPlayer : public PlayerScript
{
public:
    AlphaRewardPlayer() : PlayerScript("AlphaRewardPlayer") { }

    //On Login Get Current GamePoints
    void OnLogin(Player* p) override
    {
        QueryResult result = LoginDatabase.PQuery("SELECT `game_point` FROM `account` WHERE `id` = '%u' ", p->GetSession()->GetAccountId());

        if (!result)
            return;

        Field* fields = result->Fetch();
        p->CustomData.Set("RewardPointsMap", new AlphaRewardData(fields[0].GetInt32()));

    }

    //On logout update the gamepoints.
    void OnLogout(Player* p) override
    {
        if (AlphaRewardData* data = p->CustomData.Get<AlphaRewardData>("RewardPointsMap"))
        {
            uint32 reward = data->RewardPointsMap;
            LoginDatabase.DirectPExecute("UPDATE `account` SET `game_point` = '%u' WHERE `id` = '%u'", reward, p->GetSession()->GetAccountId());
        }
    }

    void OnPlayerCompleteQuest(Player* player, Quest const* quest)
    {
        // If player completes Daily Heroic also we could add more quest ids if need
        switch (quest->GetQuestId())
        {
            // Daily Heroic Dungeron
            case 24788:
                player->CustomData.GetDefault<AlphaRewardData>("RewardPointsMap")->RewardPointsMap += 1;
                break;
        }

        // Do not remove below its there for testing purpose :)
        // ChatHandler(player->GetSession()).PSendSysMessage("You Currently have %u game points", player->CustomData.Get< AlphaRewardData>("RewardPointsMap")->RewardPointsMap);
    }
};

/*class AlphaRewardCreature : public CreatureScript
{

};*/

void AddAlphaRewardScripts()
{
    new AlphaRewardPlayer();
    //new AlphaRewardCreature();
}
