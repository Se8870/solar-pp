
#if defined _inc_game_monitor
    #undef _inc_game_monitor
#endif

#if defined _inc_game_monitor_included
    #endinput
#endif

#define _inc_game_monitor_included

#include <streamer>
#include <weapon-config>

static
    bool:g_sPlayerInGame[MAX_PLAYERS],
    bool:g_sPlayerRobberShotFirst[MAX_PLAYERS];

// This function seems impossible to be hooked with, since y_hooks only works
// if you call the function using Call(Local/Remote)Function or SetTimer(Ex)
public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
    // This matters for avoiding fucking false positive results
    if (!g_sPlayerInGame[playerid]) return true;
    if (GetPlayerGroupTeam(playerid) == GROUP_TEAM_ROBBERS && !g_sPlayerRobberShotFirst[playerid]) return false;
    return true;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit() {
    SetVehiclePassengerDamage(true);
    SetDisableSyncBugs(true);
    ShowNameTags(false);
    SetCustomVendingMachines(false);
    SetKnifeSync(true);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    g_sPlayerInGame[playerid] = false;
    return 1;
}

hook OnGamePreparing(Lobby:id)
{
    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        CreateDynamic3DTextLabel(va_return("%s", ReturnPlayerName(pid)), GetPlayerColor(pid), 0.0, 0.0, 0.3, 10.0, pid, INVALID_VEHICLE_ID, 0, -1, -1);
        EnableHealthBarForPlayer(pid, true);
    }
    return 1;
}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart)
{
    PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
    PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (newstate == PLAYER_STATE_WASTED)
    {
        ResetPlayerGroupTeam(playerid);
        PutPlayerInCurrentLobby(playerid);
        g_sPlayerInGame[playerid] = false;
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    SendDeathMessage(killerid, playerid, reason);
    return 1;
}
