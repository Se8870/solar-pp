
#if defined _inc_game_commands
    #undef _inc_game_commands
#endif

#if defined _inc_game_commands_included
    #endinput
#endif

#define _inc_game_commands_included

#include <YSI_Visual\y_commands>

// Cuff command
COMMAND__ cuff(playerid, string:args[], help)
{
    if (help)
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "HELP: This command used for cuff");
        return 1;
    }

    if (!IsPlayerInGame(playerid) || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || GetPlayerGroupTeam(playerid) != GROUP_TEAM_POLICE)
        return 1;

    new targetid;
    if (sscanf(args, "r", targetid))
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "USAGE: /cuff <playerid/PartOfName>");
        return 1;
    }

    if (targetid == INVALID_PLAYER_ID || GetPlayerGroupTeam(targetid) != GROUP_TEAM_ROBBERS)
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "ERROR: You cannot cuff player that is not part of robbers team.");
        return 1;
    }

    new Float:playerOldPosX, Float:playerOldPosY, Float:playerOldPosZ;
    GetPlayerPos(playerid, playerOldPosX, playerOldPosY, playerOldPosZ);

    SetTimerEx(#OnPlayerCuff, 5000, false, "ifff", playerid, playerOldPosX, playerOldPosY, playerOldPosZ);
    return 1;
}

forward OnPlayerCuff(playerid, Float:x, Float:y, Float:z);
public OnPlayerCuff(playerid, Float:x, Float:y, Float:z)
{

    if (GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.0)
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "Your distance from target is far away");
        return 0;
    }

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
    PutPlayerInCuffedTeam(playerid);
    //ResetPlayerWeapons(playerid);

    SendClientMessage(playerid, 0xFFFFFFAA, "You have been cuffed");
    return 1;
}

COMMAND__ uncuff(playerid, string:args[], help)
{
    if (help)
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "HELP: This command used for cuff, use \"/cuff <playerid>\" if you wish to uncuff someone");
        return 1;
    }

    new targetid;
    sscanf(args, "R(0xFFFF)", targetid);

    if (targetid == INVALID_PLAYER_ID)
        targetid = playerid;

    if (!IsPlayerInGame(targetid) || GetPlayerState(targetid) != PLAYER_STATE_ONFOOT || GetPlayerGroupTeam(targetid) != GROUP_TEAM_ROBBERS)
        return 0;


    new Float:playerOldPosX, Float:playerOldPosY, Float:playerOldPosZ;
    GetPlayerPos(targetid, playerOldPosX, playerOldPosY, playerOldPosZ);

    SetTimerEx(#OnPlayerTryToBreakCuff, 5000, false, "ifff", targetid, playerOldPosX, playerOldPosY, playerOldPosZ);
    return 1;
}

forward OnPlayerTryToBreakCuff(playerid, Float:x, Float:y, Float:z);
public OnPlayerTryToBreakCuff(playerid, Float:x, Float:y, Float:z)
{

    if (GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.0)
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "Break cuff failed, you moved.");
        return 0;
    }

    if (random(2) == 1) // 50 : 50 chance
    {
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        PutPlayerInRobberTeam(playerid);

        SendClientMessage(playerid, 0xFFFFFFAA, "Break cuff succedeed!");
    }
    else
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "Break cuff failed!");
    }
    return 1;

}
