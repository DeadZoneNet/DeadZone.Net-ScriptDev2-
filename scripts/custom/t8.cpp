#include "precompiled.h"
 
bool GossipHello_npc_vendor_armor(Player* pPlayer, Creature* pCreature)
{
    if(pPlayer->getLevel() < 80)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay("You must be 80 level", LANG_UNIVERSAL);
        return false;
    }
 
    switch(pPlayer->getClass())
    {
        case CLASS_WARRIOR:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_PALADIN:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_HUNTER:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_ROGUE:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_PRIEST:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_DEATH_KNIGHT:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_SHAMAN:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_MAGE:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_WARLOCK:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
        case CLASS_DRUID:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me tier 8 set, please.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            break;
    }
    pPlayer->SEND_GOSSIP_MENU(3961,pCreature->GetGUID());
    return true;
}
 
bool GossipSelect_npc_vendor_armor(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
    return true;
}
 
void AddSC_npc_vendor_armor()
{
    Script* pNewScript;
 
    pNewScript = new Script;
    pNewScript->Name = "npc_vendor_armor";
    pNewScript->pGossipHello = &GossipHello_npc_vendor_armor;
    pNewScript->pGossipSelect = &GossipSelect_npc_vendor_armor;
    pNewScript->RegisterSelf();
}