#include "ScriptMgr.h"
#include "Player.h"
#include "Map.h"
#include "ObjectAccessor.h"
#include "QuestDef.h"
#include "DataMap.h"
#include "mod-alpha-rewards.h"
#include "ace/ACE.h"

class LoadQuestRewardTable : public WorldScript
{
public:
    LoadQuestRewardTable() : WorldScript("LoadQuestRewardTable") { }

    void OnLoadCustomDatabaseTable()
    {
        sLog->outString("Loading Quest Reward System...");

        QueryResult result = WorldDatabase.PQuery("SELECT `quest_id`, `points` FROM `AlphaQuestPoints`");

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
            sAlphaRewards->AlphaQuestPointsMap.emplace(field[0].GetUInt32(), field[1].GetUInt32());
            count++;

        } while (result->NextRow());

        sLog->outString(">> Loaded %u AlphaQuestPoints in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        sLog->outString("");
    }
};

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

    // Reward for Active Game Time staying logged in
    void OnBeforeUpdate(Player* player, uint32 p_time) override
    {
        if (player->isAFK())
            return;

        AlphaRewardData* RewardPoint = player->CustomData.GetDefault<AlphaRewardData>("RewardPoint");

        if (RewardPoint->timer <= p_time)
        {
            RewardPoint->reset();
            sAlphaRewards->AddGamePoint(player, 1);
        }
            
    }

    void OnPlayerCompleteQuest(Player* player, Quest const* quest)
    {
        auto it = sAlphaRewards->AlphaQuestPointsMap.find(quest->GetQuestId());

        if (it != sAlphaRewards->AlphaQuestPointsMap.end())
            sAlphaRewards->AddGamePoint(player, it->second);

        // Do not remove below its there for testing purpose :)
        // ChatHandler(player->GetSession()).PSendSysMessage("You Currently have %u game points", player->CustomData.Get< AlphaRewardData>("RewardPointsMap")->RewardPointsMap);
    }
};

class AlphaRewardGlobalScript : public GlobalScript
{
public:
    AlphaRewardGlobalScript() : GlobalScript("AlphaRewardGlobalScript") {}

    void OnAfterUpdateEncounterState(Map* map, EncounterCreditType type, uint32 creditEntry, Unit* source, Difficulty difficulty_fixed, DungeonEncounterList const* encounters, uint32 dungeonCompleted, bool updated)
    {
        if (!map->IsDungeon() || !map->IsHeroic())
            return;


    }
};

class AlphaRewardBGScript : public BGScript
{
public:
    AlphaRewardBGScript() : BGScript("AlphaRewardBGScript") {}

    void OnBattlegroundEndReward(Battleground* bg, Player* player, TeamId winnerTeamId)
    {

    }
};

void AddAlphaRewardScripts()
{
    new AlphaRewardPlayer();
    new LoadQuestRewardTable();
}
