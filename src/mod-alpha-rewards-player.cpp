#include "ScriptMgr.h"
#include "Player.h"
#include "Map.h"
#include "ObjectAccessor.h"
#include "QuestDef.h"
#include "DataMap.h"
#include "mod-alpha-rewards.h"
#include "ace/ACE.h"

/*
Todo:

Make reward points configable.
Add dungeon Complete.

*/

class AlphaRewardPlayer : public PlayerScript
{
public:
    AlphaRewardPlayer() : PlayerScript("AlphaRewardPlayer") { }

    //On Login Get Current GamePoints
    void OnLogin(Player* p) override
    {
        sAlphaRewards->OnLoginCheck(p);
    }

    //On logout update the gamepoints.
    void OnLogout(Player* p) override
    {
        sAlphaRewards->OnLogoutUpdate(p);
    }

    void OnPlayerCompleteQuest(Player* player, Quest const* quest)
    {
        // If player completes Daily Heroic also we could add more quest ids if need
        switch (quest->GetQuestId())
        {
            // Daily Heroic Dungeron
        case 24788:
            sAlphaRewards->AddGamePoint(player, 1 );
            break;
        }

        // Do not remove below its there for testing purpose :)
        // ChatHandler(player->GetSession()).PSendSysMessage("You Currently have %u game points", player->CustomData.Get< AlphaRewardData>("RewardPointsMap")->RewardPointsMap);
    }
};


void AddAlphaRewardScripts()
{
    new AlphaRewardPlayer();
}
