/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Icecrown
SD%Complete: 100
SDComment: Quest support: 12807, Vendor support: 34885
SDCategory: Icecrown
EndScriptData */

/* ContentData
npc_arete
npc_dame_evniki_kapsalis
EndContentData */

#include "precompiled.h"
#include "TemporarySummon.h"
#include "Vehicle.h"

/*######
## npc_arete
######*/

#define GOSSIP_ARETE_ITEM1 "Lord-Commander, I would hear your tale."
#define GOSSIP_ARETE_ITEM2 "<You nod slightly but do not complete the motion as the Lord-Commander narrows his eyes before he continues.>"
#define GOSSIP_ARETE_ITEM3 "I thought that they now called themselves the Scarlet Onslaught?"
#define GOSSIP_ARETE_ITEM4 "Where did the grand admiral go?"
#define GOSSIP_ARETE_ITEM5 "That's fine. When do I start?"
#define GOSSIP_ARETE_ITEM6 "Let's finish this!"
#define GOSSIP_ARETE_ITEM7 "That's quite a tale, Lord-Commander."

enum
{
    GOSSIP_TEXTID_ARETE1        = 13525,
    GOSSIP_TEXTID_ARETE2        = 13526,
    GOSSIP_TEXTID_ARETE3        = 13527,
    GOSSIP_TEXTID_ARETE4        = 13528,
    GOSSIP_TEXTID_ARETE5        = 13529,
    GOSSIP_TEXTID_ARETE6        = 13530,
    GOSSIP_TEXTID_ARETE7        = 13531,

    QUEST_THE_STORY_THUS_FAR    = 12807
};

bool GossipHello_npc_arete(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_THE_STORY_THUS_FAR) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE1, pCreature->GetGUID());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_arete(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE6, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE7, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(QUEST_THE_STORY_THUS_FAR);
            break;
    }

    return true;
}

/*######
## npc_dame_evniki_kapsalis
######*/

enum
{
    TITLE_CRUSADER              = 123,

    FACTION_ARGENT_CRUSADE      = 1106,
    
    //Horde
    FACTION_ORGRIMMAR           = 76,
    FACTION_DARKSPEAR_TROLLS    = 530,
    FACTION_UNDERCITY           = 68,
    FACTION_THUNDER_BLUFF       = 81,
    FACTION_SILVERMOON_CITY     = 911,

    //Alliance
    FACTION_STORMWIND           = 72,
    FACTION_IRONFORGE           = 47,
    FACTION_GNOMEREGAN          = 54,
    FACTION_DARNASSUS           = 69,
    FACTION_EXODAR              = 930,
};

bool GossipHello_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetReputationRank(FACTION_ARGENT_CRUSADE) >= REP_EXALTED &&
        ((pPlayer->GetTeam() == HORDE &&
        pPlayer->GetReputationRank(FACTION_ORGRIMMAR) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_DARKSPEAR_TROLLS) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_UNDERCITY) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_THUNDER_BLUFF) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_SILVERMOON_CITY) >= REP_EXALTED) ||
        (pPlayer->GetTeam() == ALLIANCE &&
        pPlayer->GetReputationRank(FACTION_STORMWIND) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_IRONFORGE) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_GNOMEREGAN) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_DARNASSUS) >= REP_EXALTED &&
        pPlayer->GetReputationRank(FACTION_EXODAR) >= REP_EXALTED)))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
    return true;
}

/*##### QUEST: ORBAZ FATE #####
SDAuthor: MaxXx2021 aka Mioka
SDComplete: 80%
SDComment: Need Core Support Chain Dest on Map Allow.
*/

enum
{
    SAY_ORBAZ_YELL01      = -1954301,
    SAY_ORBAZ_YELL02      = -1954302,
    SAY_ORBAZ_YELL03      = -1954303,

    SAY_ORBAZ_SLAY        = -1954304,
   
    SAY_MOGRAINE_EVENT01  = -1954305,
    SAY_MOGRAINE_EVENT02  = -1954306,
    SAY_ORBAZ_EVENT03     = -1954307,
    SAY_MOGRAINE_EVENT04  = -1954308,

    SAY_ORBAZ_DEATH       = -1954309,
    SAY_MOGRAINE_END      = -1954310,

    NPC_ORBAZ             = 31283,
    NPC_DARION            = 31290,
    NPC_OMINOS            = 32406,
 
    SPELL_PLAGUE_STRIKE   = 60186,
    SPELL_POWER_BLADE     = 61015,
    SPELL_POWER_DAMAGE    = 61016,
    SPELL_UNHOLY_GROUND   = 55741,
    SPELL_FLY_CLOUD       = 60984,
    SPELL_FLY_CLOUD_VIS   = 60977,
    SPELL_FLY_CLOUD_DMG   = 60984,
    SPELL_SUMMON_MOGRAINE = 58939,
};

struct MANGOS_DLL_DECL npc_orbaz_bloodbaneAI : public ScriptedAI
{
    npc_orbaz_bloodbaneAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }
  
    uint64 m_uiDarionGUID;

    uint32 m_uiPlagueStrikeTimer;
    uint32 m_uiCloudTimer;
    uint32 m_uiEnergyTimer; //in phase II when darion come!
    uint32 m_uiYellTimer;

    uint8 m_uiYell;
    uint8 m_uiPhase;

    void Reset() 
    {
        m_uiPlagueStrikeTimer = 5000;
        m_uiCloudTimer = urand(10000, 18000);
        m_uiEnergyTimer = 7000;
        m_uiYellTimer = 9000;
        m_uiYell = 0;
        m_uiPhase = 1;
        if (Creature* pDarion = m_creature->GetMap()->GetCreature(m_uiDarionGUID))
           pDarion->ForcedDespawn(1000);
        m_uiDarionGUID = 0;
    }

    void Aggro(Unit* pWho)
    { 
        m_creature->MonsterYell("Ah. I'll be waiting.",LANG_UNIVERSAL,NULL);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_ORBAZ_DEATH, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_ORBAZ_SLAY, m_creature);
    }

    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_PLAGUE_STRIKE)
            m_creature->CastSpell(pTarget, SPELL_UNHOLY_GROUND, false);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_DARION)
        {
            pSummoned->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
            pSummoned->SetFacingToObject(m_creature);
            m_uiDarionGUID = pSummoned->GetGUID(); 
        } 
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho, 2.0f, urand(0, 6.0f));
        }
    }

    void DamageTaken(Unit *done_by, uint32 &damage) 
    {
        if (damage > m_creature->GetHealth() && done_by->GetEntry() != NPC_DARION)
            damage = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiPlagueStrikeTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_PLAGUE_STRIKE);
            m_uiPlagueStrikeTimer = urand(9000, 15000);
        }
        else 
            m_uiPlagueStrikeTimer -= uiDiff;

        switch(m_uiPhase)
        {
            case 1:
                if (m_uiYellTimer < uiDiff)
                {
                    switch(m_uiYell)
                    {
                        case 0: DoScriptText(SAY_ORBAZ_YELL01, m_creature); m_uiYell++; break;
                        case 1: DoScriptText(SAY_ORBAZ_YELL02, m_creature); m_uiYell++; break;
                        case 2: DoScriptText(SAY_ORBAZ_YELL03, m_creature); m_uiYell++; break;
                    }
                    m_uiYellTimer = urand(15000, 20000);
                } 
                else 
                    m_uiYellTimer -= uiDiff;

                if (m_creature->GetHealthPercent() < 40.0f)
                {
                    m_uiPhase = 2;
                    m_creature->InterruptNonMeleeSpells(false);
                    m_creature->CastSpell(m_creature, SPELL_SUMMON_MOGRAINE, true);
                    m_creature->CastSpell(m_creature, SPELL_POWER_BLADE, false);
                    m_uiYellTimer = 3000;
                    m_uiYell = 0;
                }
                break;
            case 2:
                if (m_creature->HasAura(SPELL_POWER_BLADE))
                {
                    if (m_uiEnergyTimer < uiDiff)
                    {
                        DoCast(m_creature->getVictim(), SPELL_POWER_DAMAGE);
                        m_uiEnergyTimer = 3000;
                    }
                    else 
                        m_uiEnergyTimer -= uiDiff;
                }
                else 
                {
                    if (m_uiEnergyTimer < uiDiff)
                    {
                        m_creature->CastSpell(m_creature, SPELL_POWER_BLADE, false);
                        m_uiEnergyTimer = 7000;
                    }
                    else 
                        m_uiEnergyTimer -= uiDiff;
                }

                if (m_uiYellTimer < uiDiff)
                {
                    m_uiYellTimer = 15000;
                    switch(m_uiYell)
                    {
                        case 0: 
                            if (Creature* pDarion = m_creature->GetMap()->GetCreature(m_uiDarionGUID))
                                DoScriptText(SAY_MOGRAINE_EVENT01, pDarion); 
                            m_uiYellTimer = 5000;
                            m_uiYell++;
                            break;
                        case 1: 
                            if (Creature* pDarion = m_creature->GetMap()->GetCreature(m_uiDarionGUID))
                                DoScriptText(SAY_MOGRAINE_EVENT02, pDarion);
                            m_uiYellTimer = 7000;
                            m_uiYell++;
                            break;
                        case 2: 
                            if (Creature* pDarion = m_creature->GetMap()->GetCreature(m_uiDarionGUID))
                                DoScriptText(SAY_ORBAZ_EVENT03, m_creature);
                            m_uiYellTimer = 5000;
                            m_uiYell++;
                            break;
                        case 3:
                            if (Creature* pDarion = m_creature->GetMap()->GetCreature(m_uiDarionGUID))
                                DoScriptText(SAY_MOGRAINE_EVENT04, pDarion);
                            m_uiYellTimer = 5000;
                            m_uiYell++;
                            break;
                        case 4:
                            if (Creature* pDarion = m_creature->GetMap()->GetCreature(m_uiDarionGUID))
                                pDarion->AI()->AttackStart(m_creature);
                            m_uiYellTimer = 7000;
                            m_uiYell++;
                            break;
                    }
                }
                else 
                    m_uiYellTimer -= uiDiff;
                break;
        }
         
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_orbaz_bloodbane(Creature* pCreature)
{
    return new npc_orbaz_bloodbaneAI(pCreature);
}

struct MANGOS_DLL_DECL npc_darion_mograine_fbAI : public ScriptedAI
{
    npc_darion_mograine_fbAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint8 m_uiStep;
   
    uint32 m_uiStepTimer;

    void Reset()
    {
        m_uiStep = 0;
        m_uiStepTimer = 1000;
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho, 2.0f, urand(0, 360.0f));
        }
    }

    void EnterEvadeMode()
    {
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);

        m_creature->SetLootRecipient(NULL);
        m_uiStepTimer = 5000;
        if (m_creature->IsTemporarySummon())
            m_uiStep = 1;
    }

    void JumpNextStep(uint32 Timer)
    {
        m_uiStep++;
        m_uiStepTimer = Timer;
    }

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_MOGRAINE_END, m_creature);
                JumpNextStep(5000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, 5969.264f, 1965.250f, 514.225f);
                m_creature->ForcedDespawn(10000);
                JumpNextStep(5000);
                break;
        }
    }

    void DoMeleeAttackIfReady()
    {
        //Make sure our attack is ready before checking distance
        if (m_creature->isAttackReady())
        {
            //If we are within range melee the target
            if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
            {
                WeaponAttackType attack = urand(0,1) ? BASE_ATTACK : OFF_ATTACK;
                m_creature->AttackerStateUpdate(m_creature->getVictim(), attack);
                m_creature->resetAttackTimer(attack);
            }  
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiStepTimer < uiDiff)
            Event();
        else 
            m_uiStepTimer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_darion_mograine_fb(Creature* pCreature)
{
    return new npc_darion_mograine_fbAI(pCreature);
}

//################ QUEST: The Admiral Revealed ###################

enum
{
    SAY_MALGANIS_ESCAPE_01   = -1999407,
    SAY_MALGANIS_ESCAPE_02   = -1999408,
    SAY_MALGANIS_SLAY_01     = -1999403,
    SAY_MALGANIS_SLAY_02     = -1999404,
    SAY_MALGANIS_SLAY_03     = -1999405,
    SAY_MALGANIS_SLAY_04     = -1999406,
    SAY_MALGANIS_40HP        = -1999401,
    SAY_MALGANIS_15HP        = -1999402,
    SAY_WESTWIND_AGGRO       = -1999409,
    SAY_WESTWIND_50HP        = -1999410,
    SAY_WESTWIND_SHIELD      = -1999411,
    SAY_WESTWIND_SLAY_01     = -1999412,
    SAY_WESTWIND_SLAY_02     = -1999413,
    SAY_WESTWIND_SLAY_03     = -1999414,
    SAY_WESTWIND_SLAY_04     = -1999415,

    //Main Spells
    SPELL_SHIELD             = 50161,
    SPELL_MALGANIS_PORTAL    = 27731,
    SPELL_MALGANIS_DUMMY     = 27768,
    SPELL_MALGANIS_RETURN    = 31699,
    SPELL_REMOVE_SHIELD      = 20211,
    SPELL_SHIELD_TRIGG       = 31699,

    //Weswind Form
    SPELL_HEROIC_STRIKE      = 57846,
    SPELL_CLEAVE             = 15284,
    SPELL_WHIRLWIND          = 50622,

    //Malganis Form
    SPELL_SWAMP              = 60502,
    SPELL_MIND_BLAST         = 60500,
    SPELL_VAMPIRE            = 60501,

    NPC_MALGANIS             = 29620, //He is Alive?
    NPC_WESTWIND             = 29621,
    NPC_CREDIT               = 29627, //spell on this credit empty, i think this npc escape portal and kill credit, and killed by spell MALGANIS_DUMMY

    PHASE_WESTWIND           = 1,
    PHASE_SHIELD             = 2,
    PHASE_TRANSFORM          = 3,
    PHASE_MALGANIS           = 4,
    PHASE_ESCAPE             = 5,
};

struct MANGOS_DLL_DECL boss_hight_admiral_westwindAI : public ScriptedAI
{
    boss_hight_admiral_westwindAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }
  
    uint64 m_uiCreditGUID;

    uint32 m_uiSpell01Timer;
    uint32 m_uiSpell02Timer;
    uint32 m_uiSpell03Timer;
    uint32 m_uiStepTimer;

    uint8 m_uiStep;
    uint8 m_uiPhase;

    bool m_bNonFight;
  
    Unit* pOwner;

    void Reset() 
    {
        m_uiSpell01Timer = 5000;
        m_uiSpell02Timer = urand(10000, 18000);
        m_uiSpell03Timer = 7000;
        m_uiStepTimer = 9000;
        m_uiStep = 0;
        m_uiPhase = PHASE_WESTWIND;
        m_uiCreditGUID = 0;
        m_bNonFight = false;
        pOwner = NULL;
        m_creature->SetVisibility(VISIBILITY_ON);
        SetEquipmentSlots(true, 0, 0, 0);
    }

    void Aggro(Unit* pWho)
    { 
        DoScriptText(SAY_WESTWIND_AGGRO, m_creature);
        pOwner = pWho;
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 3))
        {
            case 0: 
                if (m_uiPhase != PHASE_MALGANIS)
                    DoScriptText(SAY_WESTWIND_SLAY_01, m_creature); 
                else 
                    DoScriptText(SAY_MALGANIS_SLAY_01, m_creature); 
                break;
            case 1:
                if (m_uiPhase != PHASE_MALGANIS)
                    DoScriptText(SAY_WESTWIND_SLAY_02, m_creature); 
                else
                    DoScriptText(SAY_MALGANIS_SLAY_02, m_creature); 
                break;
            case 2:
                if (m_uiPhase != PHASE_MALGANIS)
                    DoScriptText(SAY_WESTWIND_SLAY_03, m_creature); 
                else
                    DoScriptText(SAY_MALGANIS_SLAY_03, m_creature); 
                break;
            case 3:
                if (m_uiPhase != PHASE_MALGANIS)
                    DoScriptText(SAY_WESTWIND_SLAY_04, m_creature); 
                else 
                    DoScriptText(SAY_MALGANIS_SLAY_04, m_creature); 
                break;
        }
    }

    void AttackStart(Unit* pWho)
    {
        if (m_bNonFight)
            return;

        if(m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho, 2.0f);
        }
    }

    void DamageTaken(Unit *done_by, uint32 &damage) 
    {
        if (damage > m_creature->GetHealth())
        {
            damage = 0;
            if (!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            {
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_bNonFight = true;
                m_creature->SetHealth(1);
                DoScriptText(SAY_MALGANIS_ESCAPE_01, m_creature);
                m_creature->GetMotionMaster()->Clear(false);
                m_creature->GetMotionMaster()->MoveIdle();
                m_creature->AttackStop();
                m_creature->StopMoving();
                if (Creature* pCredit = m_creature->SummonCreature(NPC_CREDIT, 7493.825f, 4866.314f, -12.477f, 1.432f, TEMPSUMMON_CORPSE_DESPAWN, 0))
                {
                    m_uiCreditGUID = pCredit->GetGUID();
                    pCredit->SetDisplayId(11686);
                    pCredit->CastSpell(pCredit, SPELL_MALGANIS_PORTAL, false);
                    pCredit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
                m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
                m_uiStep = 0;
                m_uiStepTimer = 7000;
                m_uiPhase = PHASE_ESCAPE;
            }
        }
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_REMOVE_SHIELD && m_uiPhase == PHASE_SHIELD)
        {
            m_creature->RemoveAurasDueToSpell(SPELL_SHIELD);
            DoScriptText(SAY_WESTWIND_SHIELD, m_creature);
            m_uiStepTimer = 10500;
            m_uiPhase = PHASE_TRANSFORM;
        }
    }

    void EscapePhase()
    {
        switch(m_uiStep)
        {
            case 0:
                m_creature->GetMotionMaster()->MoveTargetedHome(); 
                m_uiStepTimer = 1000;
                m_uiStep++;
                break;
            case 2:
                DoScriptText(SAY_MALGANIS_ESCAPE_02, m_creature);
                if (pOwner && pOwner->IsInWorld())
                    m_creature->SetFacingToObject(pOwner);
                m_uiStepTimer = 10000;
                m_uiStep++;
                break;
            case 3:
                m_creature->SetVisibility(VISIBILITY_OFF);
                m_uiStepTimer = 3000;
                m_uiStep++;
                break;
            case 4:
                if (pOwner && pOwner->IsInWorld())
                    if (Creature* pCredit = m_creature->GetMap()->GetCreature(m_uiCreditGUID))
                        pOwner->DealDamage(pCredit, pCredit->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                m_creature->ForcedDespawn(500);
                m_uiStep++;
                break;
        }
    }

    void JustReachedHome()
    {
        if (m_uiPhase == PHASE_ESCAPE)
            m_uiStep = 2;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        switch(m_uiPhase)
        {
            case PHASE_WESTWIND:
            case PHASE_SHIELD:
            case PHASE_TRANSFORM:
                if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                    return;

                if (m_uiSpell01Timer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_HEROIC_STRIKE) == CAST_OK)
                        m_uiSpell01Timer = urand(4000, 8000);
                }
                else 
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE) == CAST_OK)
                        m_uiSpell02Timer = urand(6000, 12000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_WHIRLWIND) == CAST_OK)
                        m_uiSpell03Timer = urand(9000, 15000);
                }
                else
                    m_uiSpell03Timer -= uiDiff;


                if (m_creature->GetHealthPercent() < 50 && m_uiPhase == PHASE_WESTWIND)
                {
                    m_creature->CastSpell(m_creature, SPELL_SHIELD, false);
                    DoScriptText(SAY_WESTWIND_50HP, m_creature); 
                    m_uiPhase = PHASE_SHIELD;
                }

                if (m_uiPhase == PHASE_TRANSFORM)
                {
                    if (m_uiStepTimer < uiDiff)
                    {
                        m_uiPhase = PHASE_MALGANIS;
                        m_creature->UpdateEntry(NPC_MALGANIS);
                        SetEquipmentSlots(false, 0, 0, 0);
                    }
                    else
                        m_uiStepTimer -= uiDiff;
                }
                DoMeleeAttackIfReady();
                break;
            case PHASE_MALGANIS:
                if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                    return;

                if (m_uiSpell01Timer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_SWAMP) == CAST_OK)
                        m_uiSpell01Timer = urand(6000, 13000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                        if (DoCastSpellIfCan(pTarget, SPELL_MIND_BLAST) == CAST_OK)
                            m_uiSpell02Timer = urand(5000, 10000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    if (!m_creature->HasAura(SPELL_VAMPIRE))
                        DoCastSpellIfCan(m_creature, SPELL_VAMPIRE);
                    m_uiSpell03Timer = 2000;
                }
                else
                    m_uiSpell03Timer -= uiDiff;

                if( m_creature->GetHealthPercent() < 40 && m_uiStep == 0)
                {
                    m_uiStep++;
                    DoScriptText(SAY_MALGANIS_40HP, m_creature);
                }

                if (m_creature->GetHealthPercent() < 15 && m_uiStep == 1)
                {
                    m_uiStep++;
                    DoScriptText(SAY_MALGANIS_15HP, m_creature);
                }
                DoMeleeAttackIfReady();
                break;
            case PHASE_ESCAPE:
                if (m_uiStepTimer < uiDiff)
                    EscapePhase();
                else
                    m_uiStepTimer -= uiDiff;
                break;
        }
    }
};

CreatureAI* GetAI_boss_hight_admiral_westwind(Creature* pCreature)
{
    return new boss_hight_admiral_westwindAI(pCreature);
}

//################ QUEST: The Second Chance ###################

enum
{
    SAY_EVENT_01                = -1999430,
    SAY_EVENT_02                = -1999431,
    SAY_EVENT_03                = -1999432,
    SAY_EVENT_04                = -1999433,
    SAY_EVENT_05                = -1999434,
    SAY_EVENT_06                = -1999435,
    SAY_EVENT_07                = -1999436,
    SAY_EVENT_08                = -1999437,
    SAY_EVENT_09                = -1999438,
    SAY_EVENT_10                = -1999439,
    SAY_EVENT_11                = -1999440,
    SAY_EVENT_12                = -1999441,
    SAY_EVENT_13                = -1999442,

    SPELL_SUMMON_GATE           = 26560, //spell script target
    SPELL_SUMMON_ARETE          = 18280,
    SPELL_SUMMON_SOUL           = 12600,
    SPELL_GET_SOUL              = 60452,
    SPELL_TELEPORT              = 52096,
   
    NPC_LANDGREN                = 29542,
    NPC_LANDGREN_SOUL           = 29572, //383 drowned state
    NPC_ARETE                   = 29560,
    NPC_SOUL_TARGET             = 29577,

    GO_ARETE_GATE               = 191579,

    SPELL_MIND_BLAST_L          = 60453,
    SPELL_MIND_SHIRE            = 60440,
    SPELL_SHADOW_FORM           = 60449,
    SPELL_SHADOW_PAIN           = 60446,
};

struct MANGOS_DLL_DECL npc_archbishop_landgrenAI : public ScriptedAI
{
    npc_archbishop_landgrenAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        m_creature->SetCorpseDelay(300000);
        m_creature->SetRespawnDelay(300005);
        Reset();
    }

    uint32 m_uiBlastTimer;
    uint32 m_uiPainTimer;
    uint32 m_uiShireTimer;
    uint32 m_uiFormTimer;

    void Reset()
    {
        m_uiBlastTimer = urand(5000, 13000);
        m_uiShireTimer = urand(1000, 5000);
        m_uiPainTimer = urand(8000, 20000);
        m_uiFormTimer = 1000;
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_EVENT_01, m_creature);
        m_creature->CastSpell(m_creature, SPELL_SUMMON_ARETE, true);
    }

    inline float GetManaPercent() 
    {
        return (((float)m_creature->GetPower(POWER_MANA) / (float)m_creature->GetMaxPower(POWER_MANA)) * 100);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (GetManaPercent() < 30)
            m_creature->SetPower(POWER_MANA, m_creature->GetMaxPower(POWER_MANA));

        if (m_uiPainTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                if (DoCastSpellIfCan(pTarget, SPELL_SHADOW_PAIN) == CAST_OK)
                    m_uiPainTimer = urand(8000, 20000);
        }
        else
            m_uiPainTimer -= uiDiff;

        if (m_uiBlastTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                if (DoCastSpellIfCan(pTarget, SPELL_MIND_BLAST_L) == CAST_OK)
                    m_uiBlastTimer = urand(5000, 10000);
        }
        else
            m_uiBlastTimer -= uiDiff;

        if (m_uiShireTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_MIND_SHIRE) == CAST_OK)
                m_uiShireTimer = urand(8000, 12000);
        }
        else
            m_uiShireTimer -= uiDiff;

        if (m_uiFormTimer < uiDiff && m_creature->GetHealthPercent() < 50 && !m_creature->HasAura(SPELL_SHADOW_FORM))
        {
            DoCastSpellIfCan(m_creature, SPELL_SHADOW_FORM);
        }
        else
            m_uiFormTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_archbishop_landgren(Creature* pCreature)
{
    return new npc_archbishop_landgrenAI(pCreature);
}

struct MANGOS_DLL_DECL npc_lord_commander_areteAI : public ScriptedAI
{
    npc_lord_commander_areteAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
        if (m_creature->IsTemporarySummon())
        {
            TemporarySummon* pSummon = (TemporarySummon*)m_creature;
            if (Unit* pOwner = m_creature->GetMap()->GetUnit(pSummon->GetSummonerGuid()))
                m_uiLandgrenGUID = pOwner->GetGUID();
            m_bEvent = true;
            m_creature->ForcedDespawn(300000);
        }
    }

    bool m_bEvent;

    uint32 m_uiStepTimer;
    uint32 m_uiStep;
    uint32 m_uiCheckGateTimer;

    uint64 m_uiLandgrenGUID;
    uint64 m_uiSoulGUID;

    void Reset()
    {
        m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        m_creature->SetVisibility(VISIBILITY_OFF);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_uiCheckGateTimer = 2000;
        m_bEvent = false;
        m_uiStepTimer = 2000;
        m_uiStep = 0;
        m_uiLandgrenGUID = 0;
        m_uiSoulGUID = 0;
    }
   
    void JumpNextStep(uint32 Time)
    {
        m_uiStepTimer = Time;
        m_uiStep++;
    }

    void StartEvent(GameObject* pGate)
    {
        m_bEvent = false;
        m_uiStepTimer = 2000;
        m_uiStep = 1;
        m_creature->NearTeleportTo(pGate->GetPositionX(), pGate->GetPositionY(), pGate->GetPositionZ(), 0);
        m_creature->SetVisibility(VISIBILITY_ON);
        m_creature->CastSpell(m_creature, SPELL_TELEPORT, false);
        pGate->RemoveFromWorld();
    }

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiLandgrenGUID))
                {
                    float X, Y, Z, fAng;
                    fAng = m_creature->GetAngle(pLandgren);
                    X = pLandgren->GetPositionX()-3*cos(fAng);
                    Y = pLandgren->GetPositionY()-3*sin(fAng);
                    Z = pLandgren->GetPositionZ()+5;
                    m_creature->UpdateAllowedPositionZ(X, Y, Z);
                    m_creature->GetMotionMaster()->MovePoint(0, X, Y, Z);
                }
                DoScriptText(SAY_EVENT_02, m_creature);
                JumpNextStep(5000);
                 break;
            case 2:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiLandgrenGUID))
                {
                    if (Creature* pSoul = m_creature->SummonCreature(NPC_SOUL_TARGET, pLandgren->GetPositionX(), pLandgren->GetPositionY(), pLandgren->GetPositionZ(), 1.432f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 15000))
                    { 
                        pSoul->SetDisplayId(11686);
                        pSoul->SetObjectScale(0.3f);
                        m_creature->CastSpell(pSoul, SPELL_GET_SOUL, false);
                    }
                }
                DoScriptText(SAY_EVENT_03, m_creature);
                JumpNextStep(5000);
                break;
            case 3:
                m_creature->InterruptNonMeleeSpells(false);
                m_creature->CastSpell(m_creature, SPELL_SUMMON_SOUL, false);
                JumpNextStep(2000);
                break;
            case 4:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                {
                    DoScriptText(SAY_EVENT_04, pLandgren);
                    pLandgren->GetMotionMaster()->MovePoint(0, pLandgren->GetPositionX()-0.3, pLandgren->GetPositionY()+0.3, pLandgren->GetPositionZ()+2);
                }
                JumpNextStep(7000);
                break;
            case 5:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                    pLandgren->SetFacingToObject(m_creature);
                DoScriptText(SAY_EVENT_05, m_creature);
                JumpNextStep(7000);
                break;
            case 6:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                    DoScriptText(SAY_EVENT_06, pLandgren);
                JumpNextStep(1000);
                break;
            case 7:
                DoScriptText(SAY_EVENT_07, m_creature);
                JumpNextStep(4000);
                break;
            case 8:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                    m_creature->CastSpell(pLandgren, 46685, false);
                JumpNextStep(6000);
                break;
            case 9:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                    DoScriptText(SAY_EVENT_08, pLandgren);
                JumpNextStep(4000);
                break;
            case 10:
                m_creature->InterruptNonMeleeSpells(false);
                JumpNextStep(2000);
                break;
            case 11:
                DoScriptText(SAY_EVENT_09, m_creature);
                JumpNextStep(3000);
                break;
            case 12:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                    DoScriptText(SAY_EVENT_10, pLandgren);
                JumpNextStep(12000);
                break;
            case 13:
                DoScriptText(SAY_EVENT_11, m_creature);
                JumpNextStep(10000);
                break;
            case 14:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                   m_creature->CastSpell(pLandgren, 46685, false);
                JumpNextStep(2000);
                break;
            case 15:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                    DoScriptText(SAY_EVENT_12, pLandgren);
                JumpNextStep(4000);
                break;
            case 16:
                if (Creature* pLandgren = m_creature->GetMap()->GetCreature(m_uiSoulGUID))
                {
                    pLandgren->SetVisibility(VISIBILITY_OFF);
                    pLandgren->ForcedDespawn(1000);
                }
                JumpNextStep(1000);
                break;
            case 17:
                DoScriptText(SAY_EVENT_13, m_creature);
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                JumpNextStep(3000);
                break;
            
        }
    }

    void JustSummoned(Creature* pCreature)
    {
        if (pCreature->GetEntry() == NPC_LANDGREN_SOUL)
        { 
            pCreature->setFaction(35);
            pCreature->SetUInt32Value(UNIT_NPC_EMOTESTATE, 383);
            m_uiSoulGUID = pCreature->GetGUID();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEvent)
        {
            if (m_uiCheckGateTimer < uiDiff)
            {
                if (GameObject* pPortal = GetClosestGameObjectWithEntry(m_creature, GO_ARETE_GATE, 20.0f))
                    StartEvent(pPortal);
                m_uiCheckGateTimer = 2000;
            }
            else
                m_uiCheckGateTimer -= uiDiff;
        }

        if (m_uiStepTimer < uiDiff)
            Event();
        else
            m_uiStepTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_lord_commander_arete(Creature* pCreature)
{
    return new npc_lord_commander_areteAI(pCreature);
}

/*##### QUEST: Tirion's Gambit #####
SDAuthor: MaxXx2021
*/

enum
{
    SAY_TG_EVENT_01                = -1954700,
    SAY_TG_EVENT_02                = -1954701,
    SAY_TG_EVENT_03                = -1954702,
    SAY_TG_EVENT_04                = -1954703,
    SAY_TG_EVENT_05                = -1954704,
    SAY_TG_EVENT_06                = -1954705,
    SAY_TG_EVENT_07                = -1954706,
    SAY_TG_EVENT_08                = -1954707,
    SAY_TG_EVENT_09                = -1954708,
    SAY_TG_EVENT_10                = -1954709,
    SAY_TG_EVENT_11                = -1954710,
    SAY_TG_EVENT_12                = -1954711,
    SAY_TG_EVENT_13                = -1954712,
    SAY_TG_EVENT_14                = -1954713,
    SAY_TG_EVENT_15                = -1954714,
    SAY_TG_EVENT_16                = -1954715,
    SAY_TG_EVENT_17                = -1954716,
    SAY_TG_EVENT_18                = -1954717,
    SAY_TG_EVENT_19                = -1954718,
    SAY_TG_EVENT_20                = -1954719,

    NPC_TIRION_FORDRING            = 32239,
    NPC_LICH_KING_TG               = 32184,
    NPC_INKVISITOR                 = 32272,
    NPC_DARION_MOGRAINE_TG         = 32312,
    NPC_KOLTIRA                    = 32311,
    NPC_THASSARIAN                 = 32310,
    NPC_TIRION_ESCORT              = 32241,
    NPC_UNHOLY_MAN                 = 32175,
    NPC_DEATH_KNIGHT               = 32309,
    NPC_QUEST_CREDIT               = 32648,

    EQUIP_ASHBRINGER               = 13262, //mog 365 /kol 647 /thas 647 / dk 32309 / es 32241
    EQUIP_ESCORT                   = 13160,

    SPELL_FURY_LK                  = 60536,
    SPELL_TIRION_ATTACK            = 42904,
    SPELL_HEART_BLOW               = 60484,

    GO_FROZEN_HEART                = 193794,
    GO_ESCAPE_PORTAL               = 193941,
  
    QUEST_TIRION_GAMBIT_A          = 13403,
    QUEST_TIRION_GAMBIT_H          = 13364,
};

struct Location
{
    float x, y, z, x2, y2, z2;
    uint32 id;
};

struct Location Summon[]=
{
    {6162.911f, 2688.551f, 573.914f, 6133.930f, 2758.642f, 573.914f}, 
    {6165.741f, 2689.889f, 573.914f, 6133.930f, 2758.642f, 573.914f}, 
    {6169.457f, 2691.660f, 573.914f, 6133.930f, 2758.642f, 573.914f}, 
    {6168.437f, 2687.293f, 573.914f, 6133.930f, 2758.642f, 573.914f}
};

struct MANGOS_DLL_DECL npc_tirionTGAI : public ScriptedAI
{
    npc_tirionTGAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiStep;
    uint32 m_uiStepTimer;
    uint32 m_uiHeroFaction;
 
    uint64 m_uiEscortGUID[3];
    uint64 m_uiAcylteGUID[3];
    uint64 m_uiLichKingGUID;
    uint64 m_uiMograineGUID;
   
    void Reset() 
    {
        SetEquipmentSlots(false, 0, 0, 0);
        m_uiHeroFaction = 0;
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        m_uiStep = 0;
        m_uiStepTimer = 1000;
        m_uiLichKingGUID = 0;
        m_uiMograineGUID = 0;
        m_uiEscortGUID[0] = 0;
        m_uiEscortGUID[1] = 0;
        m_uiEscortGUID[2] = 0;
        m_uiAcylteGUID[0] = 0;
        m_uiAcylteGUID[1] = 0;
        m_uiAcylteGUID[2] = 0;
    }

    void StartEvent(uint8 EventId)
    {
        m_uiStep = EventId;
        m_uiStepTimer = 100;
    }

    void ResetEvent()
    {
        for (uint8 i = 0; i < 3; i++)
            if(Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[i])) 
            {
                pEscort->AddSplineFlag(SPLINEFLAG_WALKMODE);
                pEscort->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(0));
                pEscort->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
            }
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
        Reset();
        m_creature->ForcedDespawn();
    }

    void JumpNextStep(uint32 Time)
    {
        m_uiStepTimer = Time;
        m_uiStep++;
    }

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                DoScriptText(SAY_TG_EVENT_01, m_creature);
                if (Creature* pEscort = GetClosestCreatureWithEntry(m_creature, NPC_TIRION_ESCORT, 50.0f))
                {
                    m_uiEscortGUID[0] = pEscort->GetGUID();
                    pEscort->UpdateEntry(30407);
                    if (Creature* pEscort2 = GetClosestCreatureWithEntry(m_creature, NPC_TIRION_ESCORT, 50.0f))
                    {
                        m_uiEscortGUID[1] = pEscort2->GetGUID();
                        pEscort2->UpdateEntry(30407);
                        if (Creature* pEscort3 = GetClosestCreatureWithEntry(m_creature, NPC_TIRION_ESCORT, 50.0f))
                        {
                            m_uiEscortGUID[2] = pEscort3->GetGUID();
                            pEscort3->GetMotionMaster()->MoveFollow(m_creature, 2.0f, m_creature->GetAngle(m_creature) - 225.0f);
                        }
                        pEscort->UpdateEntry(NPC_TIRION_ESCORT);
                        pEscort2->UpdateEntry(NPC_TIRION_ESCORT);
                        pEscort->GetMotionMaster()->MoveFollow(m_creature, 2.0f, m_creature->GetAngle(m_creature) - 180.0f);
                        pEscort2->GetMotionMaster()->MoveFollow(m_creature, 2.0f, m_creature->GetAngle(m_creature) - 135.0f);
                    }
                }
                JumpNextStep(4000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, 6244.514f,2653.304f,570.250f);
                JumpNextStep(3000);
                break;
            case 3:
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6238.080f,2637.720f,570.250f);
                JumpNextStep(5000);
                break;
            case 4:
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6205.637f,2607.220f,570.250f);
                JumpNextStep(17000);
                break;
            case 5:
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6190.103f,2637.606f,570.250f);
                JumpNextStep(17000);
                break;
            case 6:              
                DoScriptText(SAY_TG_EVENT_02, m_creature);
                JumpNextStep(2000);
                break;
            case 7:
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6180.998f,2657.858f,573.766f);
                JumpNextStep(10000);
                break;
            case 8:     
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6144.981f,2736.049f,573.914f);         
                JumpNextStep(32000);
                break;
            case 9:                               
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6163.32f,2746.957f,573.914f);
                if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[0])) 
                {
                    pEscort->GetMotionMaster()->Clear(false);
                    pEscort->GetMotionMaster()->MovePoint(0, 6168.990f,2761.715f,573.915f);
                }
                if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[1])) 
                {
                    pEscort->GetMotionMaster()->Clear(false);
                    pEscort->GetMotionMaster()->MovePoint(0, 6172.088f,2763.098f,573.915f);
                }
                if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[2])) 
                {
                    pEscort->GetMotionMaster()->Clear(false);
                    pEscort->GetMotionMaster()->MovePoint(0, 6175.234f,2764.600f,573.915f);
                }
                JumpNextStep(9000);
                break;
            case 10:                                
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6165.613f,2760.049f,573.914f);
                JumpNextStep(7000);
                break;
            case 11:
                if (Creature* pInkvisitor = GetClosestCreatureWithEntry(m_creature, NPC_INKVISITOR, 150.0f)) 
                {
                    m_creature->SetFacingToObject(pInkvisitor);
                    if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[0]))
                        pEscort->SetFacingToObject(pInkvisitor);
                    if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[1]))
                        pEscort->SetFacingToObject(pInkvisitor);
                    if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[2]))
                        pEscort->SetFacingToObject(pInkvisitor);
                }
                DoScriptText(SAY_TG_EVENT_03, m_creature);
                if (Creature* pAcylte = m_creature->SummonCreature(NPC_UNHOLY_MAN,6166.140f,2688.851f,573.914f,1.987f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,80000))
                {
                    m_uiAcylteGUID[0] = pAcylte->GetGUID();
                    pAcylte->GetMotionMaster()->MovePoint(0, 6133.930f,2758.642f,573.914f);
                } 
                if (Creature* pAcylte = m_creature->SummonCreature(NPC_UNHOLY_MAN,6165.166f,2684.646f,573.914f,1.987f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,80000))
                {
                    m_uiAcylteGUID[1] = pAcylte->GetGUID();
                    pAcylte->GetMotionMaster()->MovePoint(0, 6132.520f,2753.841f,573.914f);
                } 
                if (Creature* pAcylte = m_creature->SummonCreature(NPC_UNHOLY_MAN,6170.443f,2687.208f,573.914f,1.987f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,80000))
                {
                    m_uiAcylteGUID[2] = pAcylte->GetGUID();
                    pAcylte->GetMotionMaster()->MovePoint(0, 6138.576f,2757.051f,573.914f);
                } 
                JumpNextStep(32000);
                break;
            case 12:     
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[0]))                                         
                    pAcylte->SetStandState(UNIT_STAND_STATE_KNEEL);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[1]))
                    pAcylte->SetStandState(UNIT_STAND_STATE_KNEEL);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[2]))
                    pAcylte->SetStandState(UNIT_STAND_STATE_KNEEL);  
                JumpNextStep(2000);
                break;   
            case 13:
                if (GameObject* pHeart = GetClosestGameObjectWithEntry(m_creature, GO_FROZEN_HEART, 150.0f))          
                    pHeart->SetRespawnTime(123);          
                JumpNextStep(3000);
                break;
            case 14:
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[0])) 
                    DoScriptText(SAY_TG_EVENT_04, pAcylte);
                JumpNextStep(4000);
                break; 
            case 15:
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[0]))
                    pAcylte->SetStandState(UNIT_STAND_STATE_STAND);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[1]))
                    pAcylte->SetStandState(UNIT_STAND_STATE_STAND);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[2]))
                    pAcylte->SetStandState(UNIT_STAND_STATE_STAND);  
                JumpNextStep(2000);
                break;   
            case 16:
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[0]))
                    pAcylte->HandleEmoteCommand(2);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[1]))
                    pAcylte->HandleEmoteCommand(2);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[2]))
                    pAcylte->HandleEmoteCommand(2); 
                JumpNextStep(2000);
                break;   
            case 17:
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[0]))
                    pAcylte->GetMotionMaster()->MovePoint(0, 6166.140f,2688.851f,573.914f);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[1]))
                    pAcylte->GetMotionMaster()->MovePoint(0, 6165.166f,2684.646f,573.914f);
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[2]))
                    pAcylte->GetMotionMaster()->MovePoint(0, 6170.443f,2687.208f,573.914f);
                DoScriptText(SAY_TG_EVENT_05, m_creature);
                JumpNextStep(5000);
                break; 
            case 18:
                DoScriptText(SAY_TG_EVENT_06, m_creature);
                if (Creature* pLichKing = m_creature->SummonCreature(NPC_LICH_KING_TG,6166.140f,2688.851f,573.914f,1.987f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,240000))
                {
                    m_uiLichKingGUID = pLichKing->GetGUID();
                    pLichKing->GetMotionMaster()->MovePoint(0, 6133.930f,2758.642f,573.914f);
                    m_creature->SetFacingToObject(pLichKing);
                }
                JumpNextStep(9000);
                break;  
            case 19:
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[0]))
                {
                    pAcylte->GetMotionMaster()->MovementExpired(false);
                    pAcylte->GetMotionMaster()->MovePoint(0, 6133.294f,2691.485f,573.914f);
                }
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[1]))
                {
                    pAcylte->GetMotionMaster()->MovementExpired(false);
                    pAcylte->GetMotionMaster()->MovePoint(0, 6133.294f,2691.485f,573.914f);
                }
                if (Creature* pAcylte = m_creature->GetMap()->GetCreature(m_uiAcylteGUID[2]))
                {
                    pAcylte->GetMotionMaster()->MovementExpired(false);
                    pAcylte->GetMotionMaster()->MovePoint(0, 6133.294f,2691.485f,573.914f);
                }
                JumpNextStep(25000);
                break; 
            case 20:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    pLichKing->SetFacingToObject(m_creature);
                    DoScriptText(SAY_TG_EVENT_07, pLichKing);
                    m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(EQUIP_ASHBRINGER));
                    m_creature->GetMotionMaster()->MovePoint(0, 6167.601f,2757.219f,573.914f);
                }
                JumpNextStep(2000);
                break;  
            case 21:
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6157.914f,2755.602f,573.914f);
                JumpNextStep(3000);
                break;  
            case 22:
                m_creature->GetMotionMaster()->MovementExpired(false);
                m_creature->GetMotionMaster()->MovePoint(0, 6143.597f,2757.256f,573.914f);
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                   DoScriptText(SAY_TG_EVENT_08, pLichKing);
                JumpNextStep(14000);
                break; 
            case 23:
                DoScriptText(SAY_TG_EVENT_09, m_creature);
                JumpNextStep(5000);
                break;     
            case 24:
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_TG_EVENT_10, pLicKing);
                JumpNextStep(11000);
                break;    
            case 25:
                DoScriptText(SAY_TG_EVENT_11, m_creature);
                JumpNextStep(6000);
                break;   
            case 26:
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_TG_EVENT_12, pLicKing);
                JumpNextStep(8000);
                break;     
            case 27:
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_TG_EVENT_13, pLicKing);
                JumpNextStep(3000);
                break;   
            case 28:
                DoScriptText(SAY_TG_EVENT_14, m_creature);
                JumpNextStep(16000);
                break;   
            case 29:
                DoScriptText(SAY_TG_EVENT_15, m_creature);
                JumpNextStep(4000);
                break;  
            case 30:
                m_creature->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                m_creature->GetMap()->CreatureRelocation(m_creature, 6130.473f,2762.259f,573.914f, m_creature->GetOrientation());
                m_creature->SendMonsterMoveJump(6130.473f, 2762.259f, 573.914f, 20.0f, SPLINEFLAG_TRAJECTORY, 1000);
                JumpNextStep(200);
                break; 
            case 31:
                DoCast(m_creature, SPELL_TIRION_ATTACK); 
                JumpNextStep(800);
                break;
            case 32:    
                DoCast(m_creature,SPELL_HEART_BLOW);
                JumpNextStep(500);
                break;
            case 33:
                m_creature->SetHealth(1);
                if (Creature* pInkvisitor = GetClosestCreatureWithEntry(m_creature, NPC_INKVISITOR, 150.0f)) 
                {
                    pInkvisitor->DealDamage(pInkvisitor, pInkvisitor->GetMaxHealth(),NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
                m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    pLicKing->DealDamage(pLicKing, pLicKing->GetMaxHealth() - 200000,NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                    pLicKing->GetMap()->CreatureRelocation(((Creature*)pLicKing), 6130.926f, 2743.355f, 573.914f, 0.537f);
                    pLicKing->SendMonsterMove(6130.926f, 2743.355f, 573.914f, SPLINETYPE_NORMAL , SPLINEFLAG_NONE, 500);
                }
                JumpNextStep(500);
                break;
            case 34:
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    pLicKing->SetStandState(UNIT_STAND_STATE_KNEEL);
                    DoScriptText(SAY_TG_EVENT_16, pLicKing);
                }
                JumpNextStep(500);
                break;
            case 35:
                if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[0])) 
                {
                    pEscort->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    pEscort->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(EQUIP_ESCORT));
                    pEscort->GetMotionMaster()->MovePoint(0, 6137.778f,2759.621f,573.914f);
                }
                if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[1]))
                {
                    pEscort->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    pEscort->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(EQUIP_ESCORT));
                    pEscort->GetMotionMaster()->MovePoint(0, 6128.400f,2757.948f,573.914f);
                }
                if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[2]))
                {
                    pEscort->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    pEscort->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(EQUIP_ESCORT));
                    pEscort->GetMotionMaster()->MovePoint(0, 6132.821f,2765.189f,573.914f);
                }
                JumpNextStep(5000);
                break;
            case 36:
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[0])) 
                    {
                        pEscort->SetFacingToObject(pLicKing);
                        DoScriptText(SAY_TG_EVENT_17, pEscort);
                        pEscort->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    }
                    if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[1]))
                    {
                        pEscort->SetFacingToObject(pLicKing);
                        pEscort->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    }
                    if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[2]))
                    {
                        pEscort->SetFacingToObject(pLicKing);
                        pEscort->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    }
                }
                JumpNextStep(3000);
                break;
            case 37:
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_TG_EVENT_18, pLicKing);
                JumpNextStep(3000);
                break;
            case 38:
                GetAcylte();
                JumpNextStep(6000);
                break;
            case 39:
                if (Creature* pMograine = m_creature->SummonCreature(NPC_DARION_MOGRAINE_TG, 6164.402f, 2694.072f, 573.914f, 1.987f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,120000))
                {
                    m_uiMograineGUID = pMograine->GetGUID();
                    pMograine->setFaction(m_uiHeroFaction);
                    pMograine->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    pMograine->GetMotionMaster()->MovePoint(0, 6133.930f,2758.642f,573.914f);
                }
                if (Creature* pKoltira = m_creature->SummonCreature(NPC_KOLTIRA,6161.058f,2692.482f,573.914f,1.987f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,120000))
                {
                    DoScriptText(SAY_TG_EVENT_19, pKoltira); 
                    pKoltira->setFaction(m_uiHeroFaction); 
                    pKoltira->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    pKoltira->GetMotionMaster()->MovePoint(0, 6133.930f,2758.642f,573.914f);
                }
                for (uint8 i = 0; i < 4; i++)
                {
                    if (Creature* pKnight = m_creature->SummonCreature(NPC_DEATH_KNIGHT, Summon[i].x, Summon[i].y, Summon[i].z, 1.987f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,120000))
                    {
                        pKnight->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pKnight->GetMotionMaster()->MovePoint(0, Summon[i].x2, Summon[i].y2, Summon[i].z2);
                    }
                }
                JumpNextStep(50000);
                break;
            case 40:
                if (Creature* pMograine = m_creature->GetMap()->GetCreature(m_uiMograineGUID))
                {
                    pMograine->setFaction(35);
                    pMograine->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    pMograine->GetMotionMaster()->MovePoint(0, 6133.930f,2758.642f,573.914f);
                    if (GameObject* pPortal = GetClosestGameObjectWithEntry(m_creature, GO_ESCAPE_PORTAL, 150.0f))               
                        pPortal->SetRespawnTime(1*MINUTE);
                    pMograine->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                }
                JumpNextStep(4000);
                break;
            case 41:
                if (Creature* pMograine = m_creature->GetMap()->GetCreature(m_uiMograineGUID))
                {
                    if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    {
                        pLicKing->SetStandState(UNIT_STAND_STATE_STAND);
                        pMograine->SetFacingToObject(pLicKing);
                    }
                    DoScriptText(SAY_TG_EVENT_20, pMograine); 
                }
                JumpNextStep(4000);
                break;
            case 42:
                if (Creature* pLicKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    pLicKing->CastSpell(pLicKing,SPELL_FURY_LK ,false);
                ResetEvent();
                JumpNextStep(15000);
                break;
       }
    }

    void GetAcylte()
    {
        std::list<Creature*> pCreatures;
        GetCreatureListWithEntryInGrid(pCreatures, m_creature, NPC_UNHOLY_MAN, 100.0f);

        if (pCreatures.empty())
            return;
 
        for (std::list<Creature*>::iterator iter = pCreatures.begin(); iter != pCreatures.end(); ++iter)
        {
            float fAng = m_creature->GetAngle((*iter));
            float X = m_creature->GetPositionX() + 17.0f*cos(fAng);
            float Y = m_creature->GetPositionY() + 17.0f*sin(fAng);
            (*iter)->SetStandState(UNIT_STAND_STATE_STAND);
            (*iter)->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
            (*iter)->GetMotionMaster()->MovePoint(0, X, Y, m_creature->GetPositionZ());
            (*iter)->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READYUNARMED);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiStepTimer <= uiDiff)
            Event();
        else
            m_uiStepTimer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

enum
{
    SPELL_BLOOD_STRIKES        = 52374,
    SPELL_FROST                = 52375,
    SPELL_DEATH                = 57602,
    SPELL_GRIP                 = 52372,
    SPELL_WRATH                = 60545,
};

struct MANGOS_DLL_DECL npc_ebon_knightAI : public ScriptedAI
{
    npc_ebon_knightAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiBloodTimer;
    uint32 m_uiDeathTimer;
    uint32 m_uiFrostTimer;
    uint32 m_uiGripTimer;
    uint32 m_uiWrathTimer;

    void Reset() 
    {
        m_uiBloodTimer = 5000;
        m_uiDeathTimer = 1000;
        m_uiFrostTimer = 12000;
        m_uiGripTimer = 7000;
        m_uiWrathTimer = 14000;
        if (m_creature->GetEntry() == NPC_UNHOLY_MAN)
            m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->GetMotionMaster()->MovementExpired();
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!pWho)
            return;

        if (!m_creature->hasUnitState(UNIT_STAT_STUNNED) && pWho->isTargetableForAttack() &&
            m_creature->IsHostileTo(pWho) && pWho->isInAccessablePlaceFor(m_creature))
        {
            if (!m_creature->CanFly() && m_creature->GetDistanceZ(pWho) > CREATURE_Z_ATTACK_RANGE)
                return;

            float attackRadius = m_creature->GetAttackDistance(pWho);
            if (m_creature->IsWithinDistInMap(pWho, attackRadius) && m_creature->IsWithinLOSInMap(pWho))
            {
                if (!m_creature->getVictim())
                {
                    AttackStart(pWho);
                    pWho->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
                }
                else if (m_creature->GetMap()->IsDungeon())
                {
                    pWho->SetInCombatWith(m_creature);
                    m_creature->AddThreat(pWho, 0.0f);
                }
            }
        }
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho, 2.0f, urand(0, 359));
        }
    }

    void DamageTaken(Unit *done_by, uint32 &damage) 
    {
        if (m_creature->GetEntry() != NPC_UNHOLY_MAN)
            damage = 0;
    }

    void EnterEvadeMode()
    {
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);

        m_creature->SetLootRecipient(NULL);
        Reset();
    }

   void UpdateAI(const uint32 diff)
   {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();

        switch(m_creature->GetEntry())
        {
            case NPC_DARION_MOGRAINE_TG:
            case NPC_DEATH_KNIGHT:
                if (m_uiBloodTimer < diff)
                {
                    DoCast(m_creature->getVictim(), SPELL_BLOOD_STRIKES);
                    m_uiBloodTimer = 5000 + rand()%10000;
                }
                else
                    m_uiBloodTimer -= diff;

                if (m_uiDeathTimer < diff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_DEATH);
                    m_uiDeathTimer = 9300;
                }
                else
                    m_uiDeathTimer -= diff;

                if (m_uiFrostTimer < diff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_FROST);
                    m_uiFrostTimer = 15000 + rand()%10000;
                }
                else
                    m_uiFrostTimer -= diff;

                if (m_uiGripTimer < diff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_GRIP);
                    m_uiGripTimer = 11000 + rand()%9000;
                }
                else
                    m_uiGripTimer -= diff;
                break;
            case NPC_KOLTIRA:
            case NPC_THASSARIAN:
                if (m_uiWrathTimer < diff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_WRATH, false);
                    m_uiWrathTimer = 3000;
                }
                else
                    m_uiWrathTimer -= diff;
                break;
        }
    }
};

CreatureAI* GetAI_npc_ebon_knight(Creature* pCreature)
{
    return new npc_ebon_knightAI(pCreature);
}

CreatureAI* GetAI_npc_tirionTG(Creature* pCreature)
{
    return new npc_tirionTGAI(pCreature);
}

bool GossipHello_npc_tirionTG(Player *pPlayer, Creature *pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_TIRION_GAMBIT_A) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_TIRION_GAMBIT_H) == QUEST_STATUS_INCOMPLETE)
        if(((npc_tirionTGAI*)pCreature->AI())->m_uiStep == 0)
            pPlayer->ADD_GOSSIP_ITEM(0, "Tirion, I'am ready!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->PlayerTalkClass->SendGossipMenu(pPlayer->GetGossipTextId(pCreature),pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_tirionTG(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action )
{
    if (action == GOSSIP_ACTION_INFO_DEF+2)
    {
        ((npc_tirionTGAI*)pCreature->AI())->StartEvent(1);
        ((npc_tirionTGAI*)pCreature->AI())->m_uiHeroFaction = pPlayer->getFaction();
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

bool GOUse_go_escape_portal(Player* pPlayer, GameObject* pGo)
{       
    pPlayer->TeleportTo(pPlayer->GetMapId(), 6445.204f, 409.518f, 495.632f, 2.765f, false);
    return false;
};

/*##### QUEST: Banshee Revange #####
SDAuthor: MaxXx2021
*/

enum
{
    SAY_EVN01         = -1544071,
    SAY_EVN02         = -1544072,
    SAY_EVN03         = -1544073,
    SAY_EVN04         = -1544074,
    SAY_EVN05         = -1544075,
    SAY_EVN06         = -1544076,
    SAY_EVN07         = -1544077,
    SAY_EVN08         = -1544078,
    SAY_EVN09         = -1544079,
    SAY_EVN10         = -1544080,
    SAY_EVN11         = -1544081,
    SAY_EVN12         = -1544082,
    SAY_EVN13         = -1544083,
    SAY_EVN14         = -1544084,
    SAY_EVN15         = -1544085,
    SAY_EVN16         = -1544086,
    SAY_EVN17         = -1544087,
    SAY_SPECIAL       = -1544088,

    SPELL_BALARGARDE_BUFF  = 59663, //use in phase 2 battle then lich king summon.
    SPELL_ICE_GROUND       = 51103, //Safidrang Cast this spell in combat!
    SPELL_ARTHAS_TELEPORT  = 64446, //Visual summon Arthas!

    SPELL_FROSTBOLT        = 15043,
    SPELL_BLIZZARD         = 61085,
    SPELL_LEAP             = 60108,
    SPELL_WHIRLWIND_B      = 61076,

    NPC_BALARGARGE         = 31016, //Boss
    NPC_VARDMADRA          = 31029, //Valkyre
    NPC_BALAR_ESCORT       = 31030, //escort balargarde
    NPC_BALAR_DRAKE        = 31056, //escort vehicle!
    NPC_LICH_KING_BR       = 31083, //or 31013?
    NPC_SAFIDRANG          = 31050, //balagarde vehicle!

    GO_HORN                = 193028,

    QUEST_BANSHEE          = 13142  //Quest
};

struct Locations
{
    float x, y, z, o;
    uint32 id;
};

struct Locations PositionQBR[]=
{
    {7132.894f, 4272.786f, 898.200f, 1.37f}, //summon vardmadra
    {7100.888f, 4424.060f, 840.200f, 1.37f}, //summon balargarde
    {7044.113f, 4388.936f, 891.897f, 5.52f}, //escort 1 position move
    {7027.320f, 4323.263f, 891.897f, 0.39f}, //escort 2 position move
    {7118.356f, 4303.155f, 891.897f, 2.34f}, //escort 3 position move
    {7134.516f, 4372.949f, 891.897f, 3.56f}, //escort 4 position move
    {7091.663f, 4426.110f, 840.200f, 4.42f}, //escort summon 1
    {7109.263f, 4421.933f, 840.200f, 4.42f}  //escort summon 2
};

struct MANGOS_DLL_DECL npc_vardmadraAI : public ScriptedAI
{
    npc_vardmadraAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiStepTimer;
    uint32 m_uiStep;
    uint64 m_uiLichKingGUID;
    uint64 m_uiBalargardeGUID;
    uint64 m_uiSafidrangGUID;
    uint64 m_uiEscortGUID[4];

    void Reset() 
    {
        AddFlags(m_creature);
        m_uiLichKingGUID = 0;
        m_uiBalargardeGUID = 0;
        m_uiSafidrangGUID = 0;
        m_uiEscortGUID[0] = 0;
        m_uiEscortGUID[1] = 0;
        m_uiEscortGUID[2] = 0;
        m_uiEscortGUID[3] = 0;
        m_uiStep = 0;
        m_uiStepTimer = 100;
    }

    void ResetEvent()
    {
        if (Creature* pDrake = m_creature->GetMap()->GetCreature(m_uiSafidrangGUID))
            Kill(pDrake);
        for (uint8 i = 0; i < 4; i++)
            if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[i]))
                if (Creature* pVehicle = m_creature->GetMap()->GetCreature(((pEscort->GetVehicle())->GetBase())->GetGUID()))
                {
                    Kill(pVehicle);
                    Kill(pEscort);
                }
        if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
            pBalargarde->RemoveFromWorld();
        if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
            Kill(pLichKing);

        Kill(m_creature);
    }

    void StartEvent(uint8 EventId)
    {
        m_uiStep = EventId;
        m_uiStepTimer = 100;
    }

    void JumpNextStep(uint32 Time)
    {
        m_uiStepTimer = Time;
        m_uiStep++;
    }

    void JustSummoned(Creature* pSummon)
    {
        if (pSummon->GetEntry() == NPC_BALAR_ESCORT)
            if (Creature* vDrake = m_creature->SummonCreature(NPC_BALAR_DRAKE, pSummon->GetPositionX(), pSummon->GetPositionY(), pSummon->GetPositionZ(), pSummon->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10))
            {
                pSummon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                AddFlags(vDrake);
                pSummon->EnterVehicle(vDrake->GetVehicleKit(), 0);
            }
    }

    void AddFlags(Creature* pUnit)
    {
        pUnit->SetSpeedRate(MOVE_RUN, 3.0f, true);
        pUnit->SetSpeedRate(MOVE_WALK, 3.0f, true);
        pUnit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pUnit->AddSplineFlag(SPLINEFLAG_FLYING);
        pUnit->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
        pUnit->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
    }

    void Kill(Creature* pVictim)
    {
        pVictim->DealDamage(pVictim, pVictim->GetMaxHealth() ,NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
    }

    void MoveToPoint(Creature* pPas, float X, float Y, float Z, uint8 pCommand)
    {
        pPas->GetMap()->CreatureRelocation(pPas, X, Y, Z, 0);
        if(Creature* pVehicle = m_creature->GetMap()->GetCreature(pPas->GetVehicle()->GetBase()->GetGUID()))
        { 
            if(pCommand == 0)
            {
                pVehicle->GetMap()->CreatureRelocation(pVehicle, X, Y, Z, 0);
                pVehicle->SendMonsterMove(X, Y, Z, SPLINETYPE_NORMAL , pVehicle->GetSplineFlags(), 6000);
            }
            else
                pVehicle->GetMotionMaster()->MovePoint(0, X, Y, Z);
        }
    }

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                if (Creature* pSummon = m_creature->SummonCreature(NPC_BALAR_ESCORT,PositionQBR[6].x, PositionQBR[6].y, PositionQBR[6].z, PositionQBR[6].o,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10))
                    m_uiEscortGUID[0] = pSummon->GetGUID();
                if (Creature* pSummon = m_creature->SummonCreature(NPC_BALAR_ESCORT,PositionQBR[7].x, PositionQBR[7].y, PositionQBR[7].z, PositionQBR[7].o,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10))
                    m_uiEscortGUID[1] = pSummon->GetGUID();
                if (Creature* pSummon = m_creature->SummonCreature(NPC_BALAR_ESCORT,PositionQBR[6].x, PositionQBR[6].y, PositionQBR[6].z, PositionQBR[6].o,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10))
                    m_uiEscortGUID[2] = pSummon->GetGUID();
                if (Creature* pSummon = m_creature->SummonCreature(NPC_BALAR_ESCORT,PositionQBR[7].x, PositionQBR[7].y, PositionQBR[7].z, PositionQBR[7].o,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10))
                    m_uiEscortGUID[3] = pSummon->GetGUID();
                if (Creature* pBalargarde = m_creature->SummonCreature(NPC_BALARGARGE,7100.888f, 4424.06f, 840.20f, PositionQBR[7].o,TEMPSUMMON_CORPSE_TIMED_DESPAWN,30000))
                {
                    m_uiBalargardeGUID = pBalargarde->GetGUID();
                    if (Creature* vDrake = m_creature->SummonCreature(NPC_SAFIDRANG, pBalargarde->GetPositionX(), pBalargarde->GetPositionY(), pBalargarde->GetPositionZ(), pBalargarde->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10))
                    {
                        AddFlags(vDrake);
                        m_uiSafidrangGUID = vDrake->GetGUID();
                        pBalargarde->EnterVehicle(vDrake->GetVehicleKit(), 0);
                    }
                }
                m_creature->GetMotionMaster()->MovePoint(0, 7095.09f, 4326.43f, 881.427f);
                JumpNextStep(9000);
                break;
            case 2:
                DoScriptText(SAY_EVN01, m_creature);
                JumpNextStep(100);
                break;
            case 3:
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[0]))
                    MoveToPoint(Escort, PositionQBR[6].x, PositionQBR[6].y, 890.0f, 0);
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[1]))
                    MoveToPoint(Escort, PositionQBR[7].x, PositionQBR[7].y, 890.0f, 0);
                JumpNextStep(2000);
                break;
            case 4:
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[2]))
                    MoveToPoint(Escort, PositionQBR[6].x, PositionQBR[6].y, 890.0f, 0);
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[3]))
                    MoveToPoint(Escort, PositionQBR[7].x, PositionQBR[7].y, 890.0f, 0);
                JumpNextStep(2000);
                break;
            case 5:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    MoveToPoint(pBalargarde, pBalargarde->GetPositionX(), pBalargarde->GetPositionY(), 890.0f, 0);
                JumpNextStep(2000);
                break;
            case 6:
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[0]))
                    MoveToPoint(Escort, PositionQBR[2].x, PositionQBR[2].y, PositionQBR[2].z, 0);
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[1]))
                    MoveToPoint(Escort, PositionQBR[5].x, PositionQBR[5].y, PositionQBR[5].z, 0);
                JumpNextStep(1000);
                break;
            case 7:
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[2]))
                    MoveToPoint(Escort, PositionQBR[3].x, PositionQBR[3].y, PositionQBR[3].z, 0);
                if (Creature* Escort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[3]))
                    MoveToPoint(Escort, PositionQBR[4].x, PositionQBR[4].y, PositionQBR[4].z, 0);
                JumpNextStep(3000);
                break;
            case 8:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    MoveToPoint(pBalargarde, 7080.51f,4356.35f,892.74f, 0);
                JumpNextStep(6000);
                break;
            case 9:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                {
                    if (Unit* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[1]))
                        if (Creature* pVehicle = m_creature->GetMap()->GetCreature(pEscort->GetVehicle()->GetBase()->GetGUID()))
                            pVehicle->SetFacingToObject(pBalargarde);
                    if (Unit* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[2]))
                        if (Creature* pVehicle = m_creature->GetMap()->GetCreature(pEscort->GetVehicle()->GetBase()->GetGUID()))
                            pVehicle->SetFacingToObject(pBalargarde);
                    if (Unit* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[3]))
                        if (Creature* pVehicle = m_creature->GetMap()->GetCreature(pEscort->GetVehicle()->GetBase()->GetGUID()))
                            pVehicle->SetFacingToObject(pBalargarde);
                    if (Unit* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[0]))
                        if (Creature* pVehicle = m_creature->GetMap()->GetCreature(pEscort->GetVehicle()->GetBase()->GetGUID()))
                            pVehicle->SetFacingToObject(pBalargarde);
                    DoScriptText(SAY_EVN02, pBalargarde);
                }
                JumpNextStep(7000);
                break;
            case 10:
                DoScriptText(SAY_EVN03, m_creature);
                JumpNextStep(8000);
                break;
            case 11:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    DoScriptText(SAY_EVN04, pBalargarde);
                JumpNextStep(5000);
                break;
            case 12:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                {
                    pBalargarde->ExitVehicle();
                    pBalargarde->GetMap()->CreatureRelocation(((Creature*)pBalargarde), 7076.957f,4342.736f, 871.4411f, 0);
                    pBalargarde->SendMonsterMoveJump(7076.957f,4342.736f,871.4411f, 10.0f, SPLINEFLAG_TRAJECTORY, 3000);
                }
                JumpNextStep(3000);
                break;
            case 13:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    DoScriptText(SAY_EVN05, pBalargarde);
                JumpNextStep(9000);
                break;
            case 14:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    pBalargarde->HandleEmoteCommand(15);
                JumpNextStep(2000);
                break;
            case 15:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    pBalargarde->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); 
                JumpNextStep(1000);
                break;
            case 17:
                if (Creature* pLichKing = m_creature->SummonCreature(NPC_LICH_KING_BR,7089.565f,4385.47f,872.3707f,4.48f,TEMPSUMMON_CORPSE_TIMED_DESPAWN,10))
                {
                    m_uiLichKingGUID = pLichKing->GetGUID();
                    if(Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    {
                        pLichKing->SetFacingToObject(pBalargarde);
                        pBalargarde->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pBalargarde->RemoveAllAuras();
                        pBalargarde->InterruptNonMeleeSpells(false);
                        pBalargarde->GetMotionMaster()->Clear(false);
                        pBalargarde->GetMotionMaster()->MoveIdle();
                        pBalargarde->StopMoving();
                        pBalargarde->AttackStop();
                        pBalargarde->SetFacingToObject(pLichKing);
                        pBalargarde->SetStandState(UNIT_STAND_STATE_KNEEL);
                        DoScriptText(SAY_EVN06, pBalargarde);
                        m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), 871.441f, 0);
                        m_creature->SendMonsterMove(m_creature->GetPositionX(), m_creature->GetPositionY(),871.441f, SPLINETYPE_NORMAL , m_creature->GetSplineFlags(), 3000);
                        m_creature->SetFacingToObject(pLichKing);
                    }
                }
                JumpNextStep(2000);
                break;
            case 18:
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                JumpNextStep(3000);
                break;
            case 19:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                   DoScriptText(SAY_EVN07, pLichKing);
                JumpNextStep(6000);
                break;
            case 20:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    pBalargarde->SetStandState(UNIT_STAND_STATE_STAND);
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    DoScriptText(SAY_EVN08, pLichKing);
                    pLichKing->SetSpeedRate(MOVE_RUN, 2.0f, true);
                    pLichKing->GetMotionMaster()->MovePoint(0, 7094.678f,4330.858f,871.467f);
                }
                JumpNextStep(13000);
                break;
            case 21:
                DoScriptText(SAY_EVN09, m_creature);
                JumpNextStep(4000);
                break;
            case 22:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_EVN10, pLichKing);
                JumpNextStep(5000);
                break;
            case 23:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    pLichKing->HandleEmoteCommand(37);
                DoScriptText(SAY_EVN11, m_creature);
                JumpNextStep(2000);
                break;
            case 24:
                m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
                m_creature->SetHealth(1);
                JumpNextStep(3000);
                break;
            case 25:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    pLichKing->HandleEmoteCommand(11);
                    pLichKing->PlayDirectSound(14820);
                }
                JumpNextStep(3000);
                break;
            case 26:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    {
                        pLichKing->SetFacingToObject(pBalargarde);
                        DoScriptText(SAY_EVN12, pLichKing);
                    }
                }
                JumpNextStep(6000);
                break;
            case 27:
                if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                    DoScriptText(SAY_EVN13, pBalargarde);
                JumpNextStep(3000);
                break;
            case 28:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_EVN14, pLichKing);
                JumpNextStep(5000);
                break;
            case 29:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    pLichKing->HandleEmoteCommand(15);
                JumpNextStep(4000);
                break;
            case 30:
                if(Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                {
                    if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                        pLichKing->CastSpell(pBalargarde, SPELL_BALARGARDE_BUFF, false);
                    pBalargarde->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Unit* pTarget = pBalargarde->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                        pBalargarde->AI()->AttackStart(pTarget);
                    DoScriptText(SAY_EVN15, pBalargarde);
                }
                JumpNextStep(100);
                break;
            case 32:
                if(Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                {
                    if (Creature* pBalargarde = m_creature->GetMap()->GetCreature(m_uiBalargardeGUID))
                        pLichKing->SetFacingToObject(pBalargarde);
                    DoScriptText(SAY_EVN16, pLichKing);
                }
                JumpNextStep(7000);
                break;
            case 33:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_EVN17, pLichKing);
                JumpNextStep(7000);
                break;
            case 34:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    pLichKing->CastSpell(pLichKing, SPELL_ARTHAS_TELEPORT, false);
                JumpNextStep(1000);
                break;
            case 35:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    Kill(pLichKing);
                JumpNextStep(1000);
                break;
            case 36:
                if (Creature* pDrake = m_creature->GetMap()->GetCreature(m_uiSafidrangGUID))
                {
                    pDrake->GetMotionMaster()->MovementExpired(false);
                    pDrake->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+200.0f, m_creature->GetPositionZ() + 50.0f);
                }
                JumpNextStep(7000);
                break;
            case 37:
                if (Creature* pDrake = m_creature->GetMap()->GetCreature(m_uiSafidrangGUID))
                    Kill(pDrake);
                for (uint8 i = 0; i < 4; i++)
                    if (Creature* pEscort = m_creature->GetMap()->GetCreature(m_uiEscortGUID[i]))
                        if(Creature* pVehicle = m_creature->GetMap()->GetCreature(pEscort->GetVehicle()->GetBase()->GetGUID()))
                        {
                            Kill(pVehicle);
                            Kill(pEscort);
                        }
                Kill(m_creature);
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiStepTimer <= uiDiff)
            Event();
        else
            m_uiStepTimer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_vardmadra(Creature* pCreature)
{
    return new npc_vardmadraAI(pCreature);
}

struct MANGOS_DLL_DECL npc_balargardeAI : public ScriptedAI
{
    npc_balargardeAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); 
        Reset();
    }

    uint32 m_uiFrostBoltTimer;
    uint32 m_uiBlizzardTimer;
    uint32 m_uiLeapTimer;
    uint32 m_uiWhirlwindTimer;
    uint32 m_uiFrostBombTimer;
    uint32 m_uiDragonMoveTimer;
    uint32 m_uiHelpTimer;
    uint64 m_uiDrakeGUID;
   
    bool m_bHas50Percent;

    void Reset() 
    {
        m_uiFrostBoltTimer = 7000;
        m_uiBlizzardTimer = 18000;
        m_uiLeapTimer = 1000;
        m_uiWhirlwindTimer = 26300;
        m_uiFrostBombTimer = 30000;
        m_uiDragonMoveTimer = 10000;
        m_uiHelpTimer = 15000;
        m_bHas50Percent = false;
        m_uiDrakeGUID = 0;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void Aggro(Unit* pWho)
    {
        if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA, 150.0f))
            m_uiDrakeGUID = ((npc_vardmadraAI*)pVardmadra->AI())->m_uiSafidrangGUID;
    }

    void JustDied(Unit* pKiller)
    {
        if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA, 150.0f))
            ((npc_vardmadraAI*)pVardmadra->AI())->StartEvent(32);
    }

    void AttackStart(Unit* pWho)
    {
        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void EnterEvadeMode()
    {
        if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA, 150.0f))
            ((npc_vardmadraAI*)pVardmadra->AI())->ResetEvent();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFrostBoltTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_FROSTBOLT);
            m_uiFrostBoltTimer = urand(7000, 10000);
        }
        else
            m_uiFrostBoltTimer -= uiDiff;

        if (m_uiLeapTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                DoCast(pTarget, SPELL_LEAP);
            m_uiLeapTimer = urand(12000, 15000);
        }
        else
            m_uiLeapTimer -= uiDiff;

        if (m_uiBlizzardTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                DoCast(pTarget, SPELL_BLIZZARD);
            m_uiBlizzardTimer = urand(16000, 19000);
        }
        else
            m_uiBlizzardTimer -= uiDiff;

        if (m_uiWhirlwindTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                DoCast(pTarget, SPELL_WHIRLWIND_B);
            m_uiWhirlwindTimer = urand(16000, 25000);
        }
        else
            m_uiWhirlwindTimer -= uiDiff;

        if (m_uiFrostBombTimer < uiDiff)
        {
            DoScriptText(SAY_SPECIAL, m_creature);
            if (Creature* pDragon = m_creature->GetMap()->GetCreature(m_uiDrakeGUID))
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                    pDragon->CastSpell(pTarget, SPELL_ICE_GROUND, false);
            m_uiFrostBombTimer = 30000;
        }
        else
            m_uiFrostBombTimer -= uiDiff;

        if (m_uiDragonMoveTimer <= uiDiff)
        {
            if (Creature* pDragon = m_creature->GetMap()->GetCreature(m_uiDrakeGUID))
            {
                pDragon->GetMotionMaster()->MovementExpired(false);
                pDragon->GetMotionMaster()->Clear(false);
                pDragon->GetMotionMaster()->MovePoint(0, (m_creature->GetPositionX()-30)+rand()%60, (m_creature->GetPositionY()-30)+rand()%60, m_creature->GetPositionZ() + 20.0f);
            }
            m_uiDragonMoveTimer = 10000;
        }
        else
            m_uiDragonMoveTimer -= uiDiff;

        if (m_creature->GetHealthPercent() < 50.0f && !m_bHas50Percent)
        {     
            if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA, 150.0f))
                ((npc_vardmadraAI*)pVardmadra->AI())->StartEvent(17);
            m_bHas50Percent = true;
        }

        if (!m_creature->HasAura(SPELL_BALARGARDE_BUFF) && m_bHas50Percent)
        {
            if (m_uiHelpTimer < uiDiff)
            {
                if (Creature* pLichKing = GetClosestCreatureWithEntry(m_creature, NPC_LICH_KING_BR, 150.0f))
                    pLichKing->CastSpell(m_creature, SPELL_BALARGARDE_BUFF, false);
                m_uiHelpTimer = 5000;
            }
            else
                m_uiHelpTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_balargarde(Creature* pCreature)
{
    return new npc_balargardeAI(pCreature);
}

bool GOUse_go_balargarde_horn(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_BANSHEE) == QUEST_STATUS_INCOMPLETE)
        if (Creature* pVardmadra = pPlayer->SummonCreature(NPC_VARDMADRA, 7132.894f, 4272.786f, 898.20f, 1.37f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10))
            ((npc_vardmadraAI*)pVardmadra->AI())->StartEvent(1);

    return false;
};

/*##### QUEST: The Air Stand Still #####
SDAuthor: MaxXx2021
*/

enum
{
    SAY_MOGRAINE_ARRIVE      = -1999510,
    SAY_MOGRAINE_EVADE       = -1999511,

    //Scourge Generals
    NPC_TALONOX              = 30830,
    NPC_SALRANAX             = 30829,
    NPC_YATHAMON             = 30831,

    //Others
    NPC_MOGRAINE_AS          = 30838,
    NPC_DEATH_GATE_MOG       = 30841,
    NPC_DEATH_GATE_MUN       = 30850,
    NPC_DEATH_GATE_JAD       = 30852,
    NPC_MOGRAINE_DUMMY       = 30844,
    NPC_MUNCH                = 30840,
    NPC_MUNCH_PET            = 30851,
    NPC_JADE                 = 30839,
    NPC_JADE_PET             = 11111, //unknown

    SPELL_SUMMON_PORTAL_ECHO = 57899, //escape
    SPELL_SUMMON_PORTAL_MOG  = 57890, //Helper Portal
    SPELL_SUMMON_PORTAL_MUN  = 57910, //Helper Portal
    SPELL_SUMMON_PORTAL_JAD  = 57916, //Helper Portal
    SPELL_HORN               = 57906,
    SPELL_SUMMON_MUNCH_PET   = 57913,

    SPELL_SUMMON_MOG         = 57892,
    SPELL_SUMMON_MUN         = 57911,
    SPELL_SUMMON_JAD         = 57917,

    //Mograine Spells
    SPELL_OBLITERATE         = 51425,
    SPELL_ICY_TOUCH          = 49909,
    SPELL_DEATH_COIL         = 49895,
    SPELL_BLOOD_STRIKE       = 49930,

    //Talonox Spells
    SPELL_SWARM              = 50284,
    SPELL_EARTH_CRUSH        = 60802,

    //Salranax Spells
    SPELL_FIREBALL           = 15242,
    SPELL_CONE               = 15244,
    SPELL_ARMOR              = 18100,
    SPELL_COUNTER_SPELL      = 15122,

    //Yathamon Spells
    SPELL_SCREAM             = 34322,
    SPELL_WEB                = 4962,
    SPELL_MIND_FLY           = 38243,
    SPELL_POISON             = 61705,

    ITEM_HORN_OF_ACHERUS     = 43206,

    GO_ESCAPE_PORTAL_ECHO    = 192907,
};

struct MANGOS_DLL_DECL npc_death_gate_asAI : public ScriptedAI
{
    npc_death_gate_asAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiSummonTimer;

    bool m_bEntryTaken;

    void Reset()
    {
        m_uiSummonTimer = 7000;
        m_bEntryTaken = true;
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (m_creature->IsTemporarySummon())
        {
            TemporarySummon* pSummon = (TemporarySummon*)m_creature;
            if(Unit* pOwner = m_creature->GetMap()->GetUnit(pSummon->GetSummonerGuid()))
                pSummoned->AI()->AttackStart(pOwner);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEntryTaken)
        {
            if (m_uiSummonTimer < uiDiff)
            {
                switch(m_creature->GetEntry())
                {
                    case NPC_DEATH_GATE_MOG:
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_MOG, false);
                        break;
                    case NPC_DEATH_GATE_MUN:
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_MUN, false);
                        break;
                    case NPC_DEATH_GATE_JAD:
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_JAD, false);
                        break;
                }
                m_bEntryTaken = false;
            }
            else
                m_uiSummonTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_death_gate_as(Creature* pCreature)
{
    return new npc_death_gate_asAI(pCreature);
}

struct MANGOS_DLL_DECL npc_death_knight_asAI : public ScriptedAI
{
    npc_death_knight_asAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiBloodStrikeTimer;
    uint32 m_uiIceTouchTimer;
    uint32 m_uiDeathCoilTimer;
    uint32 m_uiObliterateTimer;

    void Reset()
    {
        m_uiBloodStrikeTimer = 2000;
        m_uiIceTouchTimer = 6000;
        m_uiDeathCoilTimer = 12000;
        m_uiObliterateTimer = 9000;
    }

    void Aggro(Unit* pWho)
    {
        if (m_creature->GetEntry() == NPC_MOGRAINE_AS)
            DoScriptText(SAY_MOGRAINE_ARRIVE, m_creature);
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho, 2.0f, urand(0, 360.0f));
        }
    }

    void EnterEvadeMode()
    {
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);

        m_creature->SetLootRecipient(NULL);
        m_creature->CastSpell(m_creature, SPELL_SUMMON_PORTAL_ECHO, false);
        if (m_creature->GetEntry() == NPC_MOGRAINE_AS)
            DoScriptText(SAY_MOGRAINE_EVADE, m_creature);
        m_creature->ForcedDespawn(4000);
    }

    void DoMeleeAttackIfReady()
    {
        //Make sure our attack is ready before checking distance
        if (m_creature->isAttackReady())
        {
            //If we are within range melee the target
            if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
            {
                WeaponAttackType attack = urand(0,1) ? BASE_ATTACK : OFF_ATTACK;
                m_creature->AttackerStateUpdate(m_creature->getVictim(), attack);
                m_creature->resetAttackTimer(attack);
            }  
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBloodStrikeTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_BLOOD_STRIKE);
            m_uiBloodStrikeTimer = urand(2000, 5000);
        }
        else
            m_uiBloodStrikeTimer -= uiDiff;

        if (m_uiIceTouchTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_ICY_TOUCH);
            m_uiIceTouchTimer = urand(5000, 7000);
        }
        else
            m_uiIceTouchTimer -= uiDiff;

        if (m_uiDeathCoilTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_DEATH_COIL);
            m_uiDeathCoilTimer = urand(12000, 15000);
        }
        else
            m_uiDeathCoilTimer -= uiDiff;

        if (m_uiObliterateTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_OBLITERATE);
            m_uiObliterateTimer = urand(9000, 15000);
        }
        else
            m_uiObliterateTimer -= uiDiff;

        if (m_creature->GetEntry() == NPC_MOGRAINE_AS)
            DoMeleeAttackIfReady();
        else
            ScriptedAI::DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_death_knight_as(Creature* pCreature)
{
    return new npc_death_knight_asAI(pCreature);
}

struct MANGOS_DLL_DECL npc_scourge_generals_asAI : public ScriptedAI
{
    npc_scourge_generals_asAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiSpell01Timer;
    uint32 m_uiSpell02Timer;
    uint32 m_uiSpell03Timer;
    uint32 m_uiSpell04Timer;

    bool m_bDeathKnightSummoned;
    bool m_bPetSummoned;

    void Reset()
    {
        m_uiSpell01Timer = 14000;
        m_uiSpell02Timer = 6000;
        m_uiSpell03Timer = 4000;
        m_uiSpell04Timer = 9000;
        m_bDeathKnightSummoned = false;
        m_bPetSummoned = false;
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_HORN)
        {
            if (!m_bPetSummoned && m_bDeathKnightSummoned)
            {
                switch(m_creature->GetEntry())
                {
                    case NPC_TALONOX:
                        if (Creature* pMograine = GetClosestCreatureWithEntry(m_creature, NPC_MOGRAINE_AS, 50.0f))
                            pMograine->CastSpell(pMograine, SPELL_SUMMON_MUNCH_PET, true);
                        break;
                    case NPC_YATHAMON:
                        if (Creature* pJade = GetClosestCreatureWithEntry(m_creature, NPC_JADE, 50.0f))
                            pJade->CastSpell(pJade, SPELL_SUMMON_MUNCH_PET, true);
                        break;
                    case NPC_SALRANAX:
                        if (Creature* pMunch = GetClosestCreatureWithEntry(m_creature, NPC_MUNCH, 50.0f))
                            pMunch->CastSpell(pMunch, SPELL_SUMMON_MUNCH_PET, true);
                        break;
                }
                m_bPetSummoned = true;
            }
            if (!m_bDeathKnightSummoned)
            {
                switch(m_creature->GetEntry())
                {
                    case NPC_TALONOX:
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_PORTAL_MOG, true);
                        break;
                    case NPC_YATHAMON:
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_PORTAL_JAD, true);
                        break;
                    case NPC_SALRANAX:
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_PORTAL_MUN, true);
                        break;
                }
                m_bDeathKnightSummoned = true;
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(m_creature->GetEntry())
        {
            case NPC_TALONOX:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_SWARM);
                    m_uiSpell01Timer = urand(12000, 15000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_EARTH_CRUSH);
                    m_uiSpell02Timer = urand(5000, 9000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;
                break;
            case NPC_YATHAMON:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_MIND_FLY);
                    m_uiSpell01Timer = urand(5500, 9000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_SCREAM, false);
                    m_uiSpell02Timer = urand(12000, 19000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_WEB, false);
                    m_uiSpell03Timer = urand(5500, 9000);
                }
                else
                    m_uiSpell03Timer -= uiDiff;

                if (m_uiSpell04Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_POISON, false);
                    m_uiSpell04Timer = urand(9500, 15000);
                }
                else
                    m_uiSpell04Timer -= uiDiff;
                break;
            case NPC_SALRANAX:
                if (!m_creature->HasAura(SPELL_ARMOR))
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_ARMOR, false);

                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_FIREBALL);
                    m_uiSpell01Timer = urand(3500, 5000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_CONE, false);
                    m_uiSpell02Timer = urand(9000, 19000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature, SPELL_COUNTER_SPELL, false);
                    m_uiSpell03Timer = urand(9000, 19000);
                }
                else
                    m_uiSpell03Timer -= uiDiff;
                break;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_scourge_generals_as(Creature* pCreature)
{
    return new npc_scourge_generals_asAI(pCreature);
}

/*##### QUEST: Time For Answer #####
SDAuthor: MaxXx2021
*/

enum
{
   
    SAY_LICHKING_TA         = -1999450,

    NPC_MATTHIAS             = 32423,
    NPC_LICH_KING_TA         = 32443,
    NPC_SINDRAGOSA           = 32446,

    SPELL_VISION             = 61043, //change phase on value=2

    GO_SINDRAGOSA_BONES      = 193961,

    QUEST_ANSWER_1           = 13360,
    QUEST_ANSWER_2           = 13399,
};

struct MANGOS_DLL_DECL npc_matthias_02AI : public ScriptedAI
{
    npc_matthias_02AI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiStepTimer;
    uint32 m_uiStep;

    uint64 m_uiLichKingGUID;
    uint64 m_uiSindragosaGUID;
    uint64 m_uiBonesGUID;

    bool m_bEventStarted;

    void Reset()
    {
        m_uiStep = 0;
        m_uiStepTimer = 1000;
        m_bEventStarted = false;
        m_uiLichKingGUID = 0;
        m_uiSindragosaGUID = 0;
        m_uiBonesGUID = 0;
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
    }

    void StartEvent()
    {
        m_bEventStarted = true;
        m_uiStep = 1;
        m_uiStepTimer = 10;
    }

    void JumpNextStep(uint32 Timer)
    {
        m_uiStepTimer = Timer;
        m_uiStep++;
    }

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                if (Creature* pLichKing = m_creature->SummonCreature(NPC_LICH_KING_TA, 7862.08f, 961.202f, 450.467f, 1.42f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20000))
                {
                    m_uiLichKingGUID = pLichKing->GetGUID();
                    pLichKing->SetStandState(UNIT_STAND_STATE_KNEEL);
                }
                if (Creature* pSindragosa = m_creature->SummonCreature(NPC_SINDRAGOSA, 7817.37f, 1066.57f, 404.577f, 5.00f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20000))
                {
                    pSindragosa->SetSpeedRate(MOVE_WALK, 4.0f, true);
                    pSindragosa->SetSpeedRate(MOVE_RUN, 4.0f, true);
                    pSindragosa->SetSpeedRate(MOVE_FLIGHT, 4.0f, true);
                    pSindragosa->AddSplineFlag(SPLINEFLAG_FLYING);
                    pSindragosa->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
                    pSindragosa->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
                    m_uiSindragosaGUID = pSindragosa->GetGUID();
                }
                JumpNextStep(2000);
                break;
            case 2:
                if (Creature* pLichKing = m_creature->GetMap()->GetCreature(m_uiLichKingGUID))
                    DoScriptText(SAY_LICHKING_TA, pLichKing);
                if (GameObject* pBones = GetClosestGameObjectWithEntry(m_creature, GO_SINDRAGOSA_BONES, 200.0f))
                {
                    m_uiBonesGUID = pBones->GetGUID();
                    pBones->SetPhaseMask(0, true);
                }
                JumpNextStep(1000);
                break;
            case 3:
                if (Creature* pSindragosa = m_creature->GetMap()->GetCreature(m_uiSindragosaGUID))
                    pSindragosa->GetMotionMaster()->MovePoint(0, 7817.37f, 1068.57f, 494.577f);
                JumpNextStep(5000);
                break;
            case 4:
                if (Creature* pSindragosa = m_creature->GetMap()->GetCreature(m_uiSindragosaGUID))
                    pSindragosa->GetMotionMaster()->MovePoint(0, 7862.08f, 931.202f, 494.467f);
                JumpNextStep(13000);
                break;
            case 5:
                if (GameObject* pBones = m_creature->GetMap()->GetGameObject(m_uiBonesGUID))
                    pBones->SetPhaseMask(2, true);
                Reset();
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEventStarted)
        {
            if (m_uiStepTimer < uiDiff)
                Event();
            else
                m_uiStepTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_matthias_02(Creature* pCreature)
{
    return new npc_matthias_02AI(pCreature);
}

bool QuestAccept_npc_matthias_02(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ANSWER_1 || pQuest->GetQuestId() == QUEST_ANSWER_2)
    {
        pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        pPlayer->CastSpell(pPlayer, SPELL_VISION, true);
        ((npc_matthias_02AI*)pCreature->AI())->StartEvent();
    }
    return true;
}

/*##### QUEST: Battle at Valhalas
SDAuthor: MaxXx2021
*/

enum
{
    NPC_ANNOUNCER          = 31135,

    QUEST_VALHALAS_01      = 13214,
    QUEST_VALHALAS_02      = 13215,
    QUEST_VALHALAS_03      = 13216,
    QUEST_VALHALAS_04      = 13217,
    QUEST_VALHALAS_05      = 13218,
    QUEST_VALHALAS_06      = 13219,

    /*##### Fallen Heroes #####*/

    SAY_ANNOUNCER_FAL01    = -1999460,
    SAY_ANNOUNCER_FAL02    = -1999461,
    SAY_ANNOUNCER_FAL03    = -1999462,
    SAY_ANNOUNCER_FAL04    = -1999463,

    SPELL_BIRTH            = 50142,

    //Rogue
    NPC_ROGUE              = 31194,
   
    SPELL_SINISTER         = 14873,

    //Priest
    NPC_PRIEST             = 31191,

    SPELL_SMITE            = 25054,
    SPELL_HEAL             = 15586,

    //Warrior 01
    NPC_WARRIOR01          = 31192,

    SPELL_CLEAVE_V         = 15496,
    SPELL_WHIRLWIND_V      = 41056,

    //Warrior 02
    NPC_WARRIOR02          = 31193,

    SPELL_MORTAL_STRIKE    = 61041,
    SPELL_KICK_V           = 46182,

    //Warrior 03
    NPC_WARRIOR03          = 31196,

    SPELL_DEMOR            = 61044,
    SPELL_FADE_ARMOR       = 58461,

    //Hunter
    NPC_HUNTER             = 31195,
    
    SPELL_SHOOT            = 15620,
    SPELL_ARCANE_SHOOT     = 34829,
    SPELL_MAGIC_FIELD      = 44475,

    /*##### Khit'trix Dark Master #####*/

    SAY_ANNOUNCER_KIT01    = -1999464,
    SAY_ANNOUNCER_KIT02    = -1999465,
    SAY_ANNOUNCER_KIT03    = -1999466,
    SAY_ANNOUNCER_BOSS01   = -1999467,

    NPC_KHITRIX            = 31222,
 
    SPELL_MIND_FLY_V       = 38243,
    SPELL_SCREAM_V         = 22884,
    SPELL_SUMMON_SPIDER    = 61055,

    NPC_SPIDER             = 32484,

    SPELL_POISON_V         = 744,

    /*##### Sigrid Iceborn #####*/

    SAY_ANNOUNCER_SIG01    = -1999468,
    SAY_ANNOUNCER_BOSS02   = -1999469,
    SAY_ANNOUNCER_BOSS03   = -1999470,
    SAY_ANNOUNCER_SIG02    = -1999471,

    NPC_SIGRID             = 31242,
    NPC_SIGRID_VEHICLE     = 30159,

    SPELL_THROW            = 61168,
    SPELL_FROST_WEAPON     = 61165,
    SPELL_FREEZE           = 61170,
    SPELL_KNOCK_BACK       = 57635,

    /*##### Carnage #####*/

    SAY_ANNOUNCER_CAR01    = -1999472,
    SAY_ANNOUNCER_CAR02    = -1999473,
    SAY_ANNOUNCER_CAR03    = -1999474,

    NPC_CARNAGE            = 31271,

    SPELL_SMASH            = 61070,
    SPELL_STOMP            = 61065,

    /*##### Thane Banahogg #####*/

    SAY_ANNOUNCER_THA01    = -1999475,
    SAY_ANNOUNCER_THA02    = -1999476,
    SAY_ANNOUNCER_BOSS04   = -1999477,
    SAY_ANNOUNCER_BOSS05   = -1999478,
    SAY_ANNOUNCER_BOSS06   = -1999479,
    SAY_ANNOUNCER_THA03    = -1999480,

    NPC_THANE              = 31277,

    SPELL_WHIRLWIND_T      = 61139,
    SPELL_PUNT             = 61133,
    SPELL_MORTAL_STRIKE_T  = 13737,
    SPELL_LEAP_T           = 61134,
    SPELL_EXECUTE          = 61140,

    /*##### Prince Sandoval #####*/

    SAY_ANNOUNCER_PRI01    = -1999481,
    SAY_ANNOUNCER_PRI02    = -1999482,
    SAY_ANNOUNCER_PRI03    = -1999483,
    SAY_ANNOUNCER_BOSS07   = -1999484,
    SAY_ANNOUNCER_BOSS08   = -1999485,
    SAY_ANNOUNCER_BOSS09   = -1999486,
    SAY_ANNOUNCER_PRI04    = -1999487,

    NPC_PRINCE             = 14688,

    SPELL_ORB              = 61144,
    SPELL_ORB_CHAIN        = 61150, // need dummy effect 61149
    SPELL_ORB_DAMAGE       = 61145,
    SPELL_FIRE_STRIKE      = 61162,
    SPELL_FIRE_NOVA        = 61163,
};

#define CENTER_X           8216.25f
#define CENTER_Y           3516.23f
#define CENTER_Z           625.161f

static uint32 FallenHeroesData[6][1] = 
{
    {NPC_HUNTER},
    {NPC_ROGUE},
    {NPC_PRIEST},
    {NPC_WARRIOR01},
    {NPC_WARRIOR02},
    {NPC_WARRIOR03},
};

struct MANGOS_DLL_DECL npc_valhalas_announcerAI : public ScriptedAI
{
    npc_valhalas_announcerAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint8 m_uiBossCount;

    uint32 m_uiQuestEntry;
    uint32 m_uiStepTimer;
    uint32 m_uiStep;

    uint64 m_uiArenaBossGUID[6];
    uint64 m_uiPlayerGUID;

    bool m_bEventStarted;

    void Reset()
    {
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        m_bEventStarted = false;
        m_uiQuestEntry = 0;
        m_uiStepTimer = 1000;
        m_uiStep = 0;
        m_uiBossCount = 0;
        m_uiPlayerGUID = 0;
        for (uint8 i = 0; i < 6; i++)
            m_uiArenaBossGUID[i] = 0;
    }

    void StartEvent(uint32 EventId, uint32 QuestId, uint64 PlayerId)
    {
        m_uiQuestEntry = QuestId;
        m_uiPlayerGUID = PlayerId;
        m_uiStep = EventId;
        m_uiStepTimer = 500;
        m_bEventStarted = true;
    }

    void SummonedCreatureDespawn(Creature* pSummon)
    {
        if (m_uiArenaBossGUID[0] == pSummon->GetGUID())
            m_creature->AI()->EnterEvadeMode();
    }

    void SummonedCreatureJustDied(Creature* pCreature)
    {
        switch(m_uiQuestEntry)
        {
            case QUEST_VALHALAS_01:
                m_uiBossCount++;
                if (m_uiBossCount == 6)
                {
                    if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                        if (pPlayer->IsInWorld())
                            pPlayer->GroupEventHappens(QUEST_VALHALAS_01, m_creature);
                    DoScriptText(SAY_ANNOUNCER_FAL04, m_creature);
                    m_creature->AI()->EnterEvadeMode();
                }
                break;
            case QUEST_VALHALAS_02:
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                    if (pPlayer->IsInWorld())
                        pPlayer->GroupEventHappens(QUEST_VALHALAS_02, m_creature);
                DoScriptText(SAY_ANNOUNCER_KIT03, m_creature);
                m_creature->AI()->EnterEvadeMode();
                break;
            case QUEST_VALHALAS_03:
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                    if (pPlayer->IsInWorld())
                        pPlayer->GroupEventHappens(QUEST_VALHALAS_03, m_creature);
                DoScriptText(SAY_ANNOUNCER_SIG02, m_creature);
                m_creature->AI()->EnterEvadeMode();
                break;
            case QUEST_VALHALAS_04:
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                    if (pPlayer->IsInWorld())
                        pPlayer->GroupEventHappens(QUEST_VALHALAS_04, m_creature);
                DoScriptText(SAY_ANNOUNCER_CAR03, m_creature);
                m_creature->AI()->EnterEvadeMode();
                break;
            case QUEST_VALHALAS_05:
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                    if (pPlayer->IsInWorld())
                        pPlayer->GroupEventHappens(QUEST_VALHALAS_05, m_creature);
                DoScriptText(SAY_ANNOUNCER_THA03, m_creature);
                m_creature->AI()->EnterEvadeMode();
                break;
            case QUEST_VALHALAS_06:
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                    if (pPlayer->IsInWorld())
                        pPlayer->GroupEventHappens(QUEST_VALHALAS_06, m_creature);
                DoScriptText(SAY_ANNOUNCER_PRI04, m_creature);
                m_creature->AI()->EnterEvadeMode();
                break;
        }
    }

    void JustSummoned(Creature* pSummon)
    {
        if (pSummon->GetEntry() == NPC_SIGRID)
            if (Creature* vDrake = m_creature->SummonCreature(NPC_SIGRID_VEHICLE, pSummon->GetPositionX(), pSummon->GetPositionY(), pSummon->GetPositionZ(), pSummon->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000))
            {
                pSummon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                AddFlags(vDrake);
                m_uiArenaBossGUID[1] = vDrake->GetGUID();
                pSummon->EnterVehicle(vDrake->GetVehicleKit(), 0);
            }
    }

    void AddFlags(Creature* pUnit)
    {
        pUnit->SetSpeedRate(MOVE_RUN, 3.0f, true);
        pUnit->SetSpeedRate(MOVE_WALK, 3.0f, true);
        pUnit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pUnit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        pUnit->AddSplineFlag(SPLINEFLAG_FLYING);
        pUnit->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
        pUnit->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
    }

    void JumpNextStep(uint32 Timer)
    {
        m_uiStepTimer = Timer;
        m_uiStep++;
    }

    void QuestEvent01()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_ANNOUNCER_FAL01, m_creature);
                JumpNextStep(7000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+15.0f, m_creature->GetPositionZ()+15.0f);
                JumpNextStep(5000);
                break;
            case 3:
                DoScriptText(SAY_ANNOUNCER_FAL02, m_creature);
                JumpNextStep(9000);
                break;
            case 4:
                DoScriptText(SAY_ANNOUNCER_FAL03, m_creature);
                for (uint8 i = 0; i < 6; i++)
                    if (Creature* pBoss = m_creature->SummonCreature(FallenHeroesData[i][0], (CENTER_X+30)-urand(0, 60), (CENTER_Y+30)-urand(0, 60), CENTER_Z, (urand(0, 6)), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                        m_uiArenaBossGUID[i] = pBoss->GetGUID();
                JumpNextStep(10000);
                break;
            case 5:
                m_creature->MonsterTextEmote("The Fallen Heroes of Valhalas emerge from the ground to do battle once more!", 0, true);
                JumpNextStep(1000);
                break;    
            case 6:
                for (uint8 i = 0; i < 6; i++)
                    if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[i]))
                    {
                        pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        if (Unit* pPlayer = m_creature->GetMap()->GetUnit(m_uiPlayerGUID))
                            if (pPlayer->IsInWorld())
                                pBoss->AI()->AttackStart(pPlayer);
                    }
                m_bEventStarted = false;
                JumpNextStep(1000);
                break;   
        }
    }

    void QuestEvent02()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_ANNOUNCER_KIT01, m_creature);
                JumpNextStep(7000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+15.0f, m_creature->GetPositionZ()+15.0f);
                JumpNextStep(5000);
                break;
            case 3:
                DoScriptText(SAY_ANNOUNCER_KIT02, m_creature);
                JumpNextStep(9000);
                break;
            case 4:
                m_creature->MonsterTextEmote("Khit'rix the Dark Master skitters into Valhalas from the southeast!", 0, true);
                if (Creature* pBoss = m_creature->SummonCreature(NPC_KHITRIX, 8143.728f, 3483.506f, 626.696f, 0.22f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                {
                    pBoss->GetMotionMaster()->MovePoint(0, 8180.940f, 3493.068f, 625.459f);
                    m_uiArenaBossGUID[0] = pBoss->GetGUID();
                }
                JumpNextStep(2000);
                break;
            case 5:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                    DoScriptText(SAY_ANNOUNCER_BOSS01, pBoss);
                JumpNextStep(8000);
                break;
            case 6:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Unit* pPlayer = m_creature->GetMap()->GetUnit(m_uiPlayerGUID))
                        if (pPlayer->IsInWorld())
                            pBoss->AI()->AttackStart(pPlayer);
                }
                m_bEventStarted = false;
                JumpNextStep(1000);
                break; 
        }
    }

    void QuestEvent03()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_ANNOUNCER_SIG01, m_creature);
                JumpNextStep(7000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+15.0f, m_creature->GetPositionZ()+15.0f);
                if (Creature* pBoss = m_creature->SummonCreature(NPC_SIGRID, 8169.7375f, 3449.213f, 685.122f, 1.05f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                    m_uiArenaBossGUID[0] = pBoss->GetGUID();
                JumpNextStep(1000);
                break;
            case 3:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[1]))
                    pBoss->GetMotionMaster()->MovePoint(0, 8182.291f, 3469.072f, 665.345f);
                JumpNextStep(3000);
                break;
            case 4:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                    DoScriptText(SAY_ANNOUNCER_BOSS02, pBoss);
                JumpNextStep(6000);
                break;
            case 5:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[1]))
                    pBoss->GetMotionMaster()->MovePoint(0, 8200.202f, 3494.298f, 632.256f);
                JumpNextStep(8000);
                break;
            case 6:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                    DoScriptText(SAY_ANNOUNCER_BOSS03, pBoss);
                JumpNextStep(1000);
                break;
            case 7:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    pBoss->ExitVehicle();
                    pBoss->MonsterJump(8204.613f, 3491.435f, 625.548f, pBoss->GetOrientation(), 500, 10.0f);
                }
                JumpNextStep(3000);
                break;
            case 8:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Unit* pPlayer = m_creature->GetMap()->GetUnit(m_uiPlayerGUID))
                        if (pPlayer->IsInWorld())
                            pBoss->AI()->AttackStart(pPlayer);
                }
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[1]))
                    pBoss->GetMotionMaster()->MovePoint(0, 8182.291f, 3469.072f, 665.345f);
                m_bEventStarted = false;
                JumpNextStep(1000);
                break;
        }
    }

    void QuestEvent04()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_ANNOUNCER_CAR01, m_creature);
                JumpNextStep(7000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+15.0f, m_creature->GetPositionZ()+15.0f);
                JumpNextStep(5000);
                break;
            case 3:
                DoScriptText(SAY_ANNOUNCER_CAR02, m_creature);
                m_creature->MonsterTextEmote("Lumbering in from the south, the smell of Carnage precedes him!", 0, true);
                if (Creature* pBoss = m_creature->SummonCreature(NPC_CARNAGE, 8143.728f, 3483.506f, 626.696f, 0.22f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                {
                    pBoss->GetMotionMaster()->MovePoint(0, 8180.940f, 3493.068f, 625.459f);
                    m_uiArenaBossGUID[0] = pBoss->GetGUID();
                }
                JumpNextStep(10000);
                break;
            case 4:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Unit* pPlayer = m_creature->GetMap()->GetUnit(m_uiPlayerGUID))
                        if (pPlayer->IsInWorld())
                            pBoss->AI()->AttackStart(pPlayer);
                }
                m_bEventStarted = false;
                JumpNextStep(1000);
                break;
        }
    }

    void QuestEvent05()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_ANNOUNCER_THA01, m_creature);
                JumpNextStep(7000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+15.0f, m_creature->GetPositionZ()+15.0f);
                JumpNextStep(5000);
                break;
            case 3:
                DoScriptText(SAY_ANNOUNCER_THA02, m_creature);
                m_creature->MonsterTextEmote("Thane Banahogg appears upon the overlook to the southeast!", 0, true);
                if (Creature* pBoss = m_creature->SummonCreature(NPC_THANE, 8147.110f, 3460.080f, 670.918f, 0.78f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                {
                    DoScriptText(SAY_ANNOUNCER_BOSS04, pBoss);
                    m_uiArenaBossGUID[0] = pBoss->GetGUID();
                }
                JumpNextStep(7000);
                break;
            case 4:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                    pBoss->MonsterJump(8186.144f, 3490.466f, 625.342f, pBoss->GetOrientation(), 2000, 50.0f);
                JumpNextStep(3000);
                break;
            case 5:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    DoScriptText(SAY_ANNOUNCER_BOSS05, pBoss);
                    pBoss->GetMotionMaster()->MovePoint(0, 8193.870f, 3496.298f, 625.061f);
                }
                JumpNextStep(3000);
                break;
            case 6:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                    DoScriptText(SAY_ANNOUNCER_BOSS06, pBoss);
                JumpNextStep(3000);
                break;
            case 7:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Unit* pPlayer = m_creature->GetMap()->GetUnit(m_uiPlayerGUID))
                        if (pPlayer->IsInWorld())
                            pBoss->AI()->AttackStart(pPlayer);
                }
                m_bEventStarted = false;
                JumpNextStep(1000);
                break;
        }
    }

    void QuestEvent06()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_ANNOUNCER_PRI01, m_creature);
                JumpNextStep(5000);
                break;
            case 2:
                m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+15.0f, m_creature->GetPositionZ()+15.0f);
                JumpNextStep(5000);
                break;
            case 3:
                DoScriptText(SAY_ANNOUNCER_PRI02, m_creature);
                JumpNextStep(7000);
                break;
            case 4:
                DoScriptText(SAY_ANNOUNCER_PRI03, m_creature);
                m_creature->MonsterTextEmote("Without warning, Prince Sandoval magically appears within Valhalas!", 0, true);
                if (Creature* pBoss = m_creature->SummonCreature(NPC_PRINCE, 8186.144f, 3490.466f, 625.342f, 0.78f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                    m_uiArenaBossGUID[0] = pBoss->GetGUID();
                JumpNextStep(4000);
                break;
            case 5:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    pBoss->GetMotionMaster()->MovePoint(0, 8193.870f, 3496.298f, 625.061f);
                    DoScriptText(SAY_ANNOUNCER_BOSS07, pBoss);
                }
                JumpNextStep(6000);
                break;
            case 6:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                    DoScriptText(SAY_ANNOUNCER_BOSS08, pBoss);
                JumpNextStep(9000);
                break;
            case 7:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                    DoScriptText(SAY_ANNOUNCER_BOSS09, pBoss);
                JumpNextStep(4000);
                break;
            case 8:
                if (Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiArenaBossGUID[0]))
                {
                    pBoss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Unit* pPlayer = m_creature->GetMap()->GetUnit(m_uiPlayerGUID))
                        if (pPlayer->IsInWorld())
                            pBoss->AI()->AttackStart(pPlayer);
                }
                m_bEventStarted = false;
                JumpNextStep(1000);
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEventStarted)
        {
            if (m_uiStepTimer < uiDiff)
            {
                switch(m_uiQuestEntry)
                {
                    case QUEST_VALHALAS_01:
                        QuestEvent01();
                        break;
                    case QUEST_VALHALAS_02:
                        QuestEvent02();
                        break;
                    case QUEST_VALHALAS_03:
                        QuestEvent03();
                        break;
                    case QUEST_VALHALAS_04:
                        QuestEvent04();
                        break;
                    case QUEST_VALHALAS_05:
                        QuestEvent05();
                        break;
                    case QUEST_VALHALAS_06:
                        QuestEvent06();
                        break;
                }
            }
            else
                m_uiStepTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_valhalas_announcer(Creature* pCreature)
{
    return new npc_valhalas_announcerAI(pCreature);
}

bool QuestAccept_npc_valhalas_announcer(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_VALHALAS_01 || pQuest->GetQuestId() == QUEST_VALHALAS_02 || pQuest->GetQuestId() == QUEST_VALHALAS_03 || pQuest->GetQuestId() == QUEST_VALHALAS_04 || pQuest->GetQuestId() == QUEST_VALHALAS_05 || pQuest->GetQuestId() == QUEST_VALHALAS_06)
    {
        pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        ((npc_valhalas_announcerAI*)pCreature->AI())->StartEvent(1, pQuest->GetQuestId(), pPlayer->GetGUID());
    }
    return true;
}

struct MANGOS_DLL_DECL npc_fallen_warriors_bvAI : public ScriptedAI
{
    npc_fallen_warriors_bvAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiSpell01Timer;
    uint32 m_uiSpell02Timer;
    uint32 m_uiSpell03Timer;

    void Reset()
    {
        m_uiSpell01Timer = 2000;
        m_uiSpell02Timer = 6000;
        m_uiSpell03Timer = 9000;
        m_creature->SetRespawnDelay(DAY);
        m_creature->CastSpell(m_creature, SPELL_BIRTH, false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn();
    }

    void AttackStart(Unit* pWho)
    {
        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;
 
        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho, 2.0f, urand(0, 359));
        }
    }

    void DoMeleeAttackIfReady()
    {
        //Make sure our attack is ready before checking distance
        if (m_creature->isAttackReady())
        {
            //If we are within range melee the target
            if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
            {
                WeaponAttackType attack = urand(0,1) ? BASE_ATTACK : OFF_ATTACK;
                m_creature->AttackerStateUpdate(m_creature->getVictim(), attack);
                m_creature->resetAttackTimer(attack);
            }  
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(m_creature->GetEntry())
        {
            case NPC_ROGUE:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_SINISTER);
                    m_uiSpell01Timer = urand(3000, 6000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                DoMeleeAttackIfReady();
                break;
            case NPC_PRIEST:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_SMITE);
                    m_uiSpell01Timer = urand(3000, 6000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    if (m_creature->GetHealthPercent() < 40)
                    {
                        m_creature->CastSpell(m_creature, SPELL_HEAL, false);
                        m_uiSpell02Timer = urand(10000, 15000);
                    }
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_HUNTER:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_SHOOT);
                    m_uiSpell01Timer = urand(3000, 6000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_ARCANE_SHOOT, false);
                    m_uiSpell02Timer = urand(6000, 9000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_MAGIC_FIELD, false);
                    m_uiSpell03Timer = urand(15000, 19000);
                }
                else
                    m_uiSpell03Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_WARRIOR01:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_CLEAVE_V);
                    m_uiSpell01Timer = urand(5000, 9000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature, SPELL_WHIRLWIND_V, false);
                    m_uiSpell02Timer = urand(9000, 15000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_WARRIOR02:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_MORTAL_STRIKE);
                    m_uiSpell01Timer = urand(5000, 9000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_KICK_V, false);
                    m_uiSpell02Timer = urand(9000, 15000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_WARRIOR03:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_FADE_ARMOR);
                    m_uiSpell01Timer = urand(5000, 9000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature, SPELL_DEMOR, false);
                    m_uiSpell02Timer = urand(9000, 15000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
        }
    }
};

CreatureAI* GetAI_npc_fallen_warriors_bv(Creature* pCreature)
{
    return new npc_fallen_warriors_bvAI(pCreature);
}

struct MANGOS_DLL_DECL npc_valhalas_championsAI : public ScriptedAI
{
    npc_valhalas_championsAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiSpell01Timer;
    uint32 m_uiSpell02Timer;
    uint32 m_uiSpell03Timer;
    uint32 m_uiSpell04Timer;
    uint32 m_uiChangeTacticTimer;

    bool m_bIsLandPhase;

    void Reset()
    {
        m_uiSpell01Timer = 2000;
        m_uiSpell02Timer = 6000;
        m_uiSpell03Timer = 9000;
        m_uiSpell04Timer = 1000;
        m_uiChangeTacticTimer = 1000;
        m_bIsLandPhase = true;
        m_creature->SetRespawnDelay(DAY);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        if (m_creature->GetEntry() == NPC_SIGRID)
            SetCombatMovement(false);
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn();
    }

    void JustSummoned(Creature* pSummon)
    {
        pSummon->setFaction(14);
        if (m_creature->getVictim())
            pSummon->AI()->AttackStart(m_creature->getVictim());
    }

    void AttackStart(Unit* pWho)
    {
        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;
 
        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho, 2.0f, urand(0, 359));
        }
    }

    void DoMeleeAttackIfReady()
    {
        //Make sure our attack is ready before checking distance
        if (m_creature->isAttackReady())
        {
            //If we are within range melee the target
            if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
            {
                WeaponAttackType attack = urand(0,1) ? BASE_ATTACK : OFF_ATTACK;
                m_creature->AttackerStateUpdate(m_creature->getVictim(), attack);
                m_creature->resetAttackTimer(attack);
            }  
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(m_creature->GetEntry())
        {
            case NPC_KHITRIX:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_MIND_FLY_V);
                    m_uiSpell01Timer = urand(6000, 9000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature, SPELL_SCREAM_V, false);
                    m_uiSpell02Timer = urand(16000, 19000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature, SPELL_SUMMON_SPIDER, false);
                    m_uiSpell03Timer = 30000;
                }
                else
                    m_uiSpell03Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_SPIDER:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_POISON_V);
                    m_uiSpell01Timer = urand(15000, 25000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_SIGRID:
                if (!m_creature->HasAura(SPELL_FROST_WEAPON))
                    m_creature->CastSpell(m_creature, SPELL_FROST_WEAPON, false);

                if (m_creature->HasAura(SPELL_FREEZE))
                    m_creature->RemoveAurasDueToSpell(SPELL_FREEZE);

                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_THROW);
                    m_uiSpell01Timer = urand(4000, 6000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_FREEZE, false);
                    m_uiSpell02Timer = urand(14000, 19000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    if (m_creature->GetDistance2d(m_creature->getVictim()) < 5.0f)
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_KNOCK_BACK) == CAST_OK)
                            m_uiSpell03Timer = 20000;
                    }
                }
                else
                    m_uiSpell03Timer -= uiDiff;

                if (m_uiChangeTacticTimer < uiDiff)
                {
                    if (!m_creature->hasUnitState(UNIT_STAT_STUNNED || UNIT_STAT_ROOT) && m_creature->getVictim()->HasAura(SPELL_FREEZE) && m_creature->GetDistance2d(m_creature->getVictim()) < 5.0f && m_uiSpell03Timer > 4000)
                    {
                        float X, Y, Z;
                        m_creature->GetClosePoint(X, Y, Z, m_creature->GetObjectBoundingRadius(), 10.0f, urand(0, 6.0f));
                        m_creature->UpdateAllowedPositionZ(X, Y, Z);
                        m_creature->GetMotionMaster()->MovementExpired(false);
                        m_creature->GetMotionMaster()->MovePoint(0, X, Y, Z);
                        m_uiChangeTacticTimer = 7000;
                    }
                }
                else
                    m_uiChangeTacticTimer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_CARNAGE:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_SMASH);
                    m_uiSpell01Timer = urand(6000, 9000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_STOMP, false);
                    m_uiSpell02Timer = urand(16000, 19000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_THANE:
                if (m_uiSpell01Timer < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_MORTAL_STRIKE_T);
                    m_uiSpell01Timer = urand(7000, 11000);
                }
                else
                    m_uiSpell01Timer -= uiDiff;

                if (m_uiSpell02Timer < uiDiff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_PUNT, false);
                    m_uiSpell02Timer = urand(9000, 15000);
                }
                else
                    m_uiSpell02Timer -= uiDiff;

                if (m_uiSpell03Timer < uiDiff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 1))
                        m_creature->CastSpell(pTarget, SPELL_LEAP_T, true);
                    m_creature->CastSpell(m_creature, SPELL_WHIRLWIND_T, false);
                    m_uiSpell03Timer = urand(11000, 19000);
                }
                else
                    m_uiSpell03Timer -= uiDiff;

                if (m_uiSpell04Timer < uiDiff)
                {
                    if (m_creature->getVictim()->GetHealthPercent() < 19)
                        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_EXECUTE, false) == CAST_OK)
                            m_uiSpell04Timer = 10000;
                }
                else
                    m_uiSpell04Timer -= uiDiff;

                ScriptedAI::DoMeleeAttackIfReady();
                break;
            case NPC_PRINCE:
                if (m_bIsLandPhase)
                {
                    if (m_uiSpell01Timer < uiDiff)
                    {
                        DoCast(m_creature->getVictim(), SPELL_FIRE_STRIKE);
                        m_uiSpell01Timer = urand(7000, 11000);
                    }
                    else
                        m_uiSpell01Timer -= uiDiff;

                    if (m_uiSpell02Timer < uiDiff)
                    {
                        DoCast(m_creature->getVictim(), SPELL_FIRE_NOVA);
                        m_uiSpell02Timer = urand(9000, 15000);
                    }
                    else
                        m_uiSpell02Timer -= uiDiff;

                    if (m_uiSpell03Timer < uiDiff)
                    {
                        m_bIsLandPhase = false;
                        SetCombatMovement(false);
                        m_creature->GetMotionMaster()->Clear(false);
                        m_creature->GetMotionMaster()->MoveIdle();
                        m_creature->StopMoving();
                        m_creature->CastSpell(m_creature, SPELL_ORB, false);
                        m_uiSpell04Timer = 1500;
                        m_uiSpell02Timer = 30000;
                        m_uiSpell03Timer = 32000;
                    }
                    else
                        m_uiSpell03Timer -= uiDiff;

                    DoMeleeAttackIfReady();
                }
                else
                {
                    if (m_uiSpell04Timer < uiDiff)
                    {
                        m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
                        m_creature->CastSpell(m_creature, SPELL_ORB_DAMAGE, false);
                        m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY()+1, m_creature->GetPositionZ()+12); 
                        m_uiSpell04Timer = 45000;
                    }
                    else
                        m_uiSpell04Timer -= uiDiff;

                    if (m_uiSpell02Timer < uiDiff)
                    {
                        float X, Y, Z;
                        X = m_creature->GetPositionX();
                        Y = m_creature->GetPositionY()-1;
                        Z = m_creature->GetPositionZ()+3;
                        m_creature->UpdateAllowedPositionZ(X, Y, Z);
                        m_creature->GetMotionMaster()->MovePoint(0, X, Y, Z); 
                        m_uiSpell02Timer = 6000;
                    }
                    else
                        m_uiSpell02Timer -= uiDiff;

                    if (m_uiSpell03Timer < uiDiff)
                    {
                        m_bIsLandPhase = true;
                        SetCombatMovement(true);
                        m_creature->RemoveSplineFlag(SPLINEFLAG_FLYING);
                        m_creature->GetMotionMaster()->MovementExpired(false);
                        m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                        m_creature->RemoveAurasDueToSpell(SPELL_ORB);
                        m_creature->RemoveAurasDueToSpell(SPELL_ORB_DAMAGE);
                        m_uiSpell04Timer = 1000;
                        m_uiSpell03Timer = 30000;
                        m_uiSpell02Timer = 5000;
                    }
                    else
                        m_uiSpell03Timer -= uiDiff;
                }
                break;
        }
    }
};

CreatureAI* GetAI_npc_valhalas_champions(Creature* pCreature)
{
    return new npc_valhalas_championsAI(pCreature);
}

/*##### QUEST: Not-So-Honorable Combat #####
SDAuthor: MaxXx2021
*/

enum
{
    SAY_ISKALDER_NC_01          = -1999490,
    SAY_VARDMADRA_NC_02         = -1999491,
    SAY_VARDMADRA_NC_03         = -1999492,
    SAY_VARDMADRA_NC_04         = -1999493,
    SAY_VARDMADRA_NC_05         = -1999494,
    SAY_LADY_NIGHTWOODS_NC_06   = -1999495,
    SAY_VARDMADRA_NC_07         = -1999496,
    SAY_VARDMADRA_NC_08         = -1999497,

    NPC_POSSESSED_ISKALDER      = 30924,
    NPC_VARDMADRA_I             = 30945,
    NPC_LADY_NIGHTWOODS         = 30955,
  
    SPELL_CLEAVE_I              = 15496,
    SPELL_LEAP_I                = 60108,
    SPELL_HEROIC_STRIKE_I       = 57846,
    SPELL_ANCIENT               = 60121,
    SPELL_INTO_SOUL             = 25745, //cast on vardmadra
    SPELL_CONTROLL              = 58102,

    GO_CAMP_OF_ICECROWN         = 193024,

    QUEST_HORROBLE_COMBAT       = 13137,
};

struct MANGOS_DLL_DECL npc_vardmadra_ncAI : public ScriptedAI
{
    npc_vardmadra_ncAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiStepTimer;
    uint32 m_uiStep;

    uint64 m_uiIskalderGUID;
    uint64 m_uiLadyGUID;

    bool m_bEventStarted;

    void Reset()
    {
        m_uiStepTimer = 1000;
        m_uiStep = 0;
        m_bEventStarted = false;
        m_uiIskalderGUID = 0;
        m_uiLadyGUID = 0;
        m_creature->SetSpeedRate(MOVE_RUN, 3.0f, true);
        m_creature->SetSpeedRate(MOVE_WALK, 3.0f, true);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
    }

    void StartEvent(uint64 GUID)
    {
        m_uiIskalderGUID = GUID;
        m_bEventStarted = true;
        m_uiStep = 1;
        m_uiStepTimer = 10;
    }

    void JumpNextStep(uint32 Timer)
    {
        m_uiStepTimer = Timer;
        m_uiStep++;
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType == POINT_MOTION_TYPE && uiPointId == 1)
            m_uiStep = 3;
    }

    void AttackStart(Unit* pWho) {}

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                if (Creature* pIskalder = m_creature->GetMap()->GetCreature(m_uiIskalderGUID))
                {
                    float X, Y, Z, fAng;
                    fAng = m_creature->GetAngle(pIskalder);
                    X = pIskalder->GetPositionX()-5*cos(fAng);
                    Y = pIskalder->GetPositionY()-5*sin(fAng);
                    Z = pIskalder->GetPositionZ()+5;
                    m_creature->UpdateAllowedPositionZ(X, Y, Z);
                    m_creature->GetMotionMaster()->MovePoint(1, X, Y, Z+8);
                } 
                JumpNextStep(10);
                break;
            case 3:
                DoScriptText(SAY_VARDMADRA_NC_04, m_creature);
                JumpNextStep(4000);
                break;
            case 4:
                DoScriptText(SAY_VARDMADRA_NC_05, m_creature);
                JumpNextStep(7000);
                break;
            case 5:
                if (Creature* pIskalder = m_creature->GetMap()->GetCreature(m_uiIskalderGUID))
                    if (Creature* pLady = m_creature->SummonCreature(NPC_LADY_NIGHTWOODS, pIskalder->GetPositionX(), pIskalder->GetPositionY(), pIskalder->GetPositionZ(), 1.432f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 14000))
                    {
                        m_uiLadyGUID = pLady->GetGUID();
                        pLady->AddSplineFlag(SPLINEFLAG_FLYING);
                        pLady->GetMotionMaster()->MovePoint(0, pLady->GetPositionX()+1, pLady->GetPositionY()+1, pLady->GetPositionZ()+8);
                    }
                JumpNextStep(2000);
                break;
           case 6:
                if (Creature* pLady = m_creature->GetMap()->GetCreature(m_uiLadyGUID))
                    DoScriptText(SAY_LADY_NIGHTWOODS_NC_06, pLady);
                JumpNextStep(5000);
                break;
           case 7:
                DoScriptText(SAY_VARDMADRA_NC_07, m_creature);
                JumpNextStep(6000);
                break;
           case 8:
                if (Creature* pLady = m_creature->GetMap()->GetCreature(m_uiLadyGUID))
                    pLady->CastSpell(m_creature, SPELL_INTO_SOUL, false);
                JumpNextStep(2000);
                break;
           case 9:
                DoScriptText(SAY_VARDMADRA_NC_08, m_creature);
                JumpNextStep(6000);
                break;
           case 10:
                m_creature->ForcedDespawn();
                JumpNextStep(6000);
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEventStarted)
        {
            if (m_uiStepTimer < uiDiff)
                Event();
            else
                m_uiStepTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_vardmadra_nc(Creature* pCreature)
{
    return new npc_vardmadra_ncAI(pCreature);
}

struct MANGOS_DLL_DECL npc_possessed_iskalderAI : public ScriptedAI
{
    npc_possessed_iskalderAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiCleaveTimer;
    uint32 m_uiStrikeTimer;
    uint32 m_uiLeapTimer;
    uint32 m_uiCourseTimer;
    uint32 m_uiStepTimer;
    uint32 m_uiStep;

    bool m_bEventStarted;

    void Reset()
    {
        m_uiCleaveTimer = 2000;
        m_uiStrikeTimer = 5000;
        m_uiLeapTimer = 10000;
        m_uiCourseTimer = 5000;
        m_uiStepTimer = 1000;
        m_uiStep = 1;
        m_creature->CastSpell(m_creature, SPELL_CONTROLL, false);
        m_creature->SetRespawnDelay(DAY);
        m_bEventStarted = true;
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn();
        if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA_I, 130.0f))
            pVardmadra->ForcedDespawn();
    }

    void JustDied(Unit* pKiller)
    {
        if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA_I, 130.0f))
            ((npc_vardmadra_ncAI*)pVardmadra->AI())->StartEvent(m_creature->GetGUID());
    }

    void JumpNextStep(uint32 Timer)
    {
        m_uiStepTimer = Timer;
        m_uiStep++;
    }

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                DoScriptText(SAY_ISKALDER_NC_01, m_creature);
                JumpNextStep(6000);
                break;
            case 2:
                if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA_I, 130.0f))
                    DoScriptText(SAY_VARDMADRA_NC_02, pVardmadra);
                JumpNextStep(8000);
                break;
            case 3:
                if (Creature* pVardmadra = GetClosestCreatureWithEntry(m_creature, NPC_VARDMADRA_I, 130.0f))
                    DoScriptText(SAY_VARDMADRA_NC_03, pVardmadra);
                JumpNextStep(1000);
                m_bEventStarted = false;
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bEventStarted)
        {
            if (m_uiStepTimer < uiDiff)
                Event();
            else
                m_uiStepTimer -= uiDiff;
        }

        if (m_uiCleaveTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_CLEAVE_I);
            m_uiCleaveTimer = urand(7000, 10000);
        }
        else 
            m_uiCleaveTimer -= uiDiff;

        if (m_uiStrikeTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_HEROIC_STRIKE_I);
            m_uiStrikeTimer = urand(5000, 10000);
        }
        else 
            m_uiStrikeTimer -= uiDiff;

        if (m_uiLeapTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 1))
                m_creature->CastSpell(pTarget, SPELL_LEAP_I, false);
            m_uiLeapTimer = urand(11000, 19000);
        }
        else
            m_uiLeapTimer -= uiDiff;

        if (m_uiCourseTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                m_creature->CastSpell(pTarget, SPELL_ANCIENT, false);
            m_uiCourseTimer = urand(5000, 19000);
        }
        else
            m_uiCourseTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_possessed_iskalder(Creature* pCreature)
{
    return new npc_possessed_iskalderAI(pCreature);
}

bool GOUse_go_icecrown_camp(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_HORROBLE_COMBAT) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->SummonCreature(NPC_VARDMADRA_I, 7215.812f, 3645.861f, 827.589f, 6.10f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10);
        pPlayer->SummonCreature(NPC_POSSESSED_ISKALDER, 7237.033f, 3641.674f, 808.934f, 0.02f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 40000);
    }

    return false;
};

/*##### QUEST: Through the Eye #####
SDAuthor: MaxXx2021
*/

enum
{
    SAY_CULTIST_EYE_01         = -1999500,
    SAY_VARDMADRA_EYE_02       = -1999501,
    SAY_CULTIST_EYE_03         = -1999502,
    SAY_VARDMADRA_EYE_04       = -1999503,
    SAY_CULTIST_EYE_05         = -1999504,
    SAY_VARDMADRA_EYE_06       = -1999505,
    SAY_CULTIST_EYE_07         = -1999506,
    SAY_VARDMADRA_EYE_08       = -1999507,
    SAY_VARDMADRA_EYE_09       = -1999508,
    SAY_CULTIST_EYE_10         = -1999509,


    NPC_IMAGE_OF_VARDMADRA     = 30836,
    NPC_IMAGE_OF_CULTIST       = 30835,
    NPC_KILL_CREDIT_EYE        = 30750,

    SPELL_EYE_VISION           = 57888,

    GO_EYE                     = 192861,

    QUEST_EYE                  = 13121,
};

struct MANGOS_DLL_DECL npc_image_of_vardmadraAI : public ScriptedAI
{
    npc_image_of_vardmadraAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiStepTimer;
    uint32 m_uiStep;

    uint64 m_uiCultistGUID;
    uint64 m_uiPlayerGUID;

    bool m_bEventStarted;

    void Reset()
    {
        m_uiStepTimer = 1000;
        m_uiStep = 0;
        m_bEventStarted = false;
        m_uiCultistGUID = 0;
        m_uiPlayerGUID = 0;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void StartEvent(uint64 GUID)
    {
        m_uiPlayerGUID = GUID;
        m_bEventStarted = true;
        m_uiStep = 1;
        m_uiStepTimer = 10;
    }

    void JumpNextStep(uint32 Timer)
    {
        m_uiStepTimer = Timer;
        m_uiStep++;
    }

    void AttackStart(Unit* pWho) {}

    void SummonedMovementInform(Creature* pSummoned, uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType == POINT_MOTION_TYPE && uiPointId == 1)
            JumpNextStep(10);
    }

    void Event()
    {
        switch(m_uiStep)
        {
            case 1:
                if (Creature* pCultist = m_creature->SummonCreature(NPC_IMAGE_OF_CULTIST, 6817.106f, 3800.885f, 621.070f, 0.96f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 70000))
                {
                    m_uiCultistGUID = pCultist->GetGUID();
                    pCultist->GetMotionMaster()->MovePoint(1, 6828.338f, 3810.988f, 621.070f);
                }
                JumpNextStep(10);
                break;
            case 3:
                if (Creature* pCultist = m_creature->GetMap()->GetCreature(m_uiCultistGUID))
                {
                    pCultist->SetFacingToObject(m_creature);
                    DoScriptText(SAY_CULTIST_EYE_01, pCultist);
                }
                JumpNextStep(2000);
                break;
            case 4:
                DoScriptText(SAY_VARDMADRA_EYE_02, m_creature);
                JumpNextStep(2000);
                break;
            case 5:
                if (Creature* pCultist = m_creature->GetMap()->GetCreature(m_uiCultistGUID))
                    DoScriptText(SAY_CULTIST_EYE_03, pCultist);
                JumpNextStep(9000);
                break;
            case 6:
                DoScriptText(SAY_VARDMADRA_EYE_04, m_creature);
                JumpNextStep(4000);
                break;
            case 7:
                if (Creature* pCultist = m_creature->GetMap()->GetCreature(m_uiCultistGUID))
                    DoScriptText(SAY_CULTIST_EYE_05, pCultist);
                JumpNextStep(11000);
                break;
            case 8:
                DoScriptText(SAY_VARDMADRA_EYE_06, m_creature);
                JumpNextStep(6000);
                break;
            case 9:
                if (Creature* pCultist = m_creature->GetMap()->GetCreature(m_uiCultistGUID))
                    DoScriptText(SAY_CULTIST_EYE_07, pCultist);
                JumpNextStep(5000);
                break;
            case 10:
                DoScriptText(SAY_VARDMADRA_EYE_08, m_creature);
                JumpNextStep(11000);
                break;
            case 11:
                DoScriptText(SAY_VARDMADRA_EYE_09, m_creature);
                JumpNextStep(8000);
                break;
            case 12:
                if (Creature* pCultist = m_creature->GetMap()->GetCreature(m_uiCultistGUID))
                {
                    pCultist->HandleEmoteCommand(2);
                    DoScriptText(SAY_CULTIST_EYE_10, pCultist);
                }
                JumpNextStep(5000);
                break;
            case 13:
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                    if (pPlayer->IsInWorld())
                        pPlayer->GroupEventHappens(QUEST_EYE, m_creature);
                if (Creature* pCultist = m_creature->GetMap()->GetCreature(m_uiCultistGUID))
                    pCultist->GetMotionMaster()->MovePoint(0, 6817.106f, 3800.885f, 621.070f);
                JumpNextStep(5000);
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEventStarted)
        {
            if (m_uiStepTimer < uiDiff)
                Event();
            else
                m_uiStepTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_image_of_vardmadra(Creature* pCreature)
{
    return new npc_image_of_vardmadraAI(pCreature);
}

#define GOSSIP_EVENT_START  "Grasp the Eye of the Lich King and focus your will upon it to scry for important information."
#define GOSSIP_MENU_EVENT   10005

bool GOGossipHello_go_eye_of_the_lichking(Player* pPlayer, GameObject* pGo)
{

    if (pPlayer->isInCombat())
        return true;

    if (!pPlayer->HasAura(SPELL_EYE_VISION) && pPlayer->GetQuestStatus(QUEST_EYE) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_TAXI, GOSSIP_EVENT_START, GOSSIP_SENDER_MAIN, 0);

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_EVENT, pGo->GetGUID());
    return true;
}

bool GOGossipSelect_go_eye_of_the_lichking(Player* pPlayer, GameObject* pGo, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
        return false;

    if (pPlayer->isInCombat())
        return false;

    pPlayer->CastSpell(pPlayer, SPELL_EYE_VISION, false);

    if (Creature* pVardmadra = pPlayer->SummonCreature(NPC_IMAGE_OF_VARDMADRA, 6831.950f, 3817.500f, 621.070f, 4.15f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 70000))
        ((npc_image_of_vardmadraAI*)pVardmadra->AI())->StartEvent(pPlayer->GetGUID());  

    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

/* ### Threat from Above ###*/
 
enum
{
    NPC_CHILLMAW           = 33687,
    NPC_CULTIST            = 33695,
    NPC_SPELL_BOMB         = 34307,
 
    SPELL_WING_BUFFET      = 65260,
    SPELL_FROST_BREATH     = 65248,
    SPELL_THROWN_DYNAMITE  = 65128,
    SPELL_TIME_BOMB        = 65130,
    SPELL_EXPLOSIVE        = 65129, 
    SPELL_FLY              = 59553,
};
 
struct MANGOS_DLL_DECL npc_chillmawAI : public ScriptedAI
{
    npc_chillmawAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        Reset();
    }
 
    uint32 m_uiWingBuffetTimer;
    uint32 m_uiFrostBreathTimer;
    uint64 m_uiCultistSeatGUID[3];
    bool m_bCultistExitFromVehicle[3];
 
    void Reset()
    {
        InitSeat();
        m_creature->SetSpeedRate(MOVE_WALK, 2.0f, true);
        m_creature->SetSpeedRate(MOVE_RUN, 2.0f, true);
        m_creature->SetSpeedRate(MOVE_FLIGHT, 2.0f, true);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
        m_uiWingBuffetTimer = 3000;
        m_uiFrostBreathTimer = 4000;
 
        memset(m_uiCultistSeatGUID, 0, sizeof(m_uiCultistSeatGUID));
        memset(m_bCultistExitFromVehicle, false, sizeof(m_bCultistExitFromVehicle));
    }
 
    void InitSeat()
    {
        for (uint8 i = 0; i < 3; i++)
        {
            if (Creature* pCultist = m_creature->SummonCreature(NPC_CULTIST, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 6000))
            {
                pCultist->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                pCultist->EnterVehicle(m_creature->GetVehicleKit(), i);
                m_uiCultistSeatGUID[i] = pCultist->GetGUID();
            }
        }
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
 
        if (m_creature->GetHealthPercent() < 75.0f)
        {
            if (m_uiWingBuffetTimer < uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_WING_BUFFET);
                m_uiWingBuffetTimer = urand(6000, 10000);
            }
            else
                m_uiWingBuffetTimer -= uiDiff;
        }
 
        if (m_creature->GetHealthPercent() < 50.0f)
        {
            if (m_uiFrostBreathTimer < uiDiff)
            {
                DoCast(m_creature->getVictim(), SPELL_FROST_BREATH);
                m_uiFrostBreathTimer = urand(10000, 15000);
            }
            else
                m_uiFrostBreathTimer -= uiDiff;
        }
 
        if(m_creature->GetHealthPercent() < 75.0f && !m_bCultistExitFromVehicle[0])
        {
            if (Creature* pCultist01 = m_creature->GetMap()->GetCreature(m_uiCultistSeatGUID[0]))
            {
                pCultist01->ExitVehicle();
                pCultist01->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
            m_bCultistExitFromVehicle[0] = true;
        }
 
        if(m_creature->GetHealthPercent() < 50.0f && !m_bCultistExitFromVehicle[1])
        {
            if (Creature* pCultist02 = m_creature->GetMap()->GetCreature(m_uiCultistSeatGUID[1]))
            {
                pCultist02->ExitVehicle();
                pCultist02->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
            m_bCultistExitFromVehicle[1] = true;
        }
 
        if(m_creature->GetHealthPercent() < 25.0f && !m_bCultistExitFromVehicle[2])
        {
            if (Creature* pCultist03 = m_creature->GetMap()->GetCreature(m_uiCultistSeatGUID[2]))
            {
                pCultist03->ExitVehicle();
                pCultist03->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
            m_bCultistExitFromVehicle[2] = true;
        }
 
        DoMeleeAttackIfReady();
    }
};
 
CreatureAI* GetAI_npc_chillmaw(Creature* pCreature)
{
    return new npc_chillmawAI (pCreature);
}
 
struct MANGOS_DLL_DECL npc_cultist_bombardierAI : public ScriptedAI
{
    npc_cultist_bombardierAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }
 
    uint32 m_uiThrownDynamiteTimer;
    uint32 m_uiTimeBombTimer;
 
    void Reset()
    {
        m_uiThrownDynamiteTimer = 5000;
        m_uiTimeBombTimer = 12000;
    }
 
    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_TIME_BOMB)
        {
            if (Creature* pBomb = m_creature->SummonCreature(NPC_SPELL_BOMB, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), pTarget->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 1000))
                pBomb->CastSpell(pBomb, SPELL_EXPLOSIVE, false);
        }
    }
 
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget())
            return;
 
        if (m_uiThrownDynamiteTimer < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, SPELL_THROWN_DYNAMITE);
            m_uiThrownDynamiteTimer = 6000;
        }
        else
            m_uiThrownDynamiteTimer -= uiDiff;
 
        if (m_creature->getVictim())
        {
            if (m_uiTimeBombTimer < uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_TIME_BOMB);
                m_uiTimeBombTimer = 11000;
            }
            else
                m_uiTimeBombTimer -= uiDiff;
 
            DoMeleeAttackIfReady();
        }
    }
};
 
CreatureAI* GetAI_npc_cultist_bombardier(Creature* pCreature)
{
    return new npc_cultist_bombardierAI(pCreature);
}

void AddSC_icecrown()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_chillmaw";
    newscript->GetAI = &GetAI_npc_chillmaw;
    newscript->RegisterSelf();
 
    newscript = new Script;
    newscript->Name = "npc_cultist_bombardier";
    newscript->GetAI = &GetAI_npc_cultist_bombardier;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_arete";
    newscript->pGossipHello = &GossipHello_npc_arete;
    newscript->pGossipSelect = &GossipSelect_npc_arete;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_dame_evniki_kapsalis";
    newscript->pGossipHello = &GossipHello_npc_dame_evniki_kapsalis;
    newscript->pGossipSelect = &GossipSelect_npc_dame_evniki_kapsalis;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_orbaz_bloodbane";
    newscript->GetAI = &GetAI_npc_orbaz_bloodbane;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_darion_mograine_fb";
    newscript->GetAI = &GetAI_npc_darion_mograine_fb;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_hight_admiral_westwind";
    newscript->GetAI = &GetAI_boss_hight_admiral_westwind;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_archbishop_landgren";
    newscript->GetAI = &GetAI_npc_archbishop_landgren;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_lord_commander_arete";
    newscript->GetAI = &GetAI_npc_lord_commander_arete;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_ebon_knight";
    newscript->GetAI = &GetAI_npc_ebon_knight;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tirionTG";
    newscript->GetAI = &GetAI_npc_tirionTG;
    newscript->pGossipHello = &GossipHello_npc_tirionTG;
    newscript->pGossipSelect = &GossipSelect_npc_tirionTG;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_escape_portal";
    newscript->pGOUse = &GOUse_go_escape_portal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_vardmadra";
    newscript->GetAI = &GetAI_npc_vardmadra;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_balargarde";
    newscript->GetAI = &GetAI_npc_balargarde;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_balargarde_horn";
    newscript->pGOUse = &GOUse_go_balargarde_horn;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_death_gate_as";
    newscript->GetAI = &GetAI_npc_death_gate_as;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_death_knight_as";
    newscript->GetAI = &GetAI_npc_death_knight_as;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_scourge_generals_as";
    newscript->GetAI = &GetAI_npc_scourge_generals_as;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_matthias_02";
    newscript->GetAI = &GetAI_npc_matthias_02;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_matthias_02;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_valhalas_announcer";
    newscript->GetAI = &GetAI_npc_valhalas_announcer;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_valhalas_announcer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_fallen_warriors_bv";
    newscript->GetAI = &GetAI_npc_fallen_warriors_bv;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_valhalas_champions";
    newscript->GetAI = &GetAI_npc_valhalas_champions;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_vardmadra_nc";
    newscript->GetAI = &GetAI_npc_vardmadra_nc;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_possessed_iskalder";
    newscript->GetAI = &GetAI_npc_possessed_iskalder;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_icecrown_camp";
    newscript->pGOUse = &GOUse_go_icecrown_camp;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_image_of_vardmadra";
    newscript->GetAI = &GetAI_npc_image_of_vardmadra;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_eye_of_the_lichking";
    newscript->pGossipHelloGO  = &GOGossipHello_go_eye_of_the_lichking;
    newscript->pGossipSelectGO = &GOGossipSelect_go_eye_of_the_lichking;
    newscript->RegisterSelf();
}