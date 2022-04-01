
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
    bool:g_sPlayerInGame[MAX_PLAYERS char],
    bool:g_sPlayerRobberShotFirst[MAX_PLAYERS char],
    Text3D:g_sPlayerHealthBar[MAX_PLAYERS],
    Text3D:g_sPlayerTextName[MAX_PLAYERS];

static stock
    gsc_szPlayerHealthBar[][] = {
        "In a brink of death",
        "|",
        "||",
        "|||",
        "||||",
        "|||||",
        "||||||",
        "|||||||",
        "||||||||",
        "|||||||||",
        "||||||||||"
    };

ResetPlayerGame(playerid)
{
    if (g_sPlayerInGame{playerid} == false)
        return 0;

    g_sPlayerInGame{playerid} = false;
    ResetPlayerGroupTeam(playerid);
    return 1;
}

IsPlayerInGame(playerid)
{
    return g_sPlayerInGame{playerid};
}

// This function seems impossible to be hooked with, since y_hooks only works
// if you call the function using Call(Local/Remote)Function or SetTimer(Ex)
public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
    // This matters for avoiding fucking false positive results
    if (!g_sPlayerInGame{playerid}) return false;

    if (GetPlayerGroupTeam(playerid) == GROUP_TEAM_ROBBERS && !g_sPlayerRobberShotFirst{playerid}) return false;
    
    // disables damage if the weapon is tazer
	if (weapon == 23 && GetPlayerGroupTeam(playerid) == GROUP_TEAM_POLICE) 
    {
        amount = 0.0;
    }
    return true;
}

forward OnPlayerUnfreeze(playerid);
public OnPlayerUnfreeze(playerid)
{
    TogglePlayerControllable(playerid, true);
    return 1;
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
    g_sPlayerInGame{playerid} = false;
    return 1;
}

hook OnGamePreparing(Lobby:id)
{
    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        g_sPlayerHealthBar[pid] = CreateDynamic3DTextLabel(va_return("[{FF00FF}%s{FFFFFF}]", ReturnPlayerHealthBar(pid)), 0xFFFFFFFF,  0.0, 0.0, 0.1, 10.0, pid, INVALID_VEHICLE_ID, 0, -1, -1);
        g_sPlayerTextName[pid] = CreateDynamic3DTextLabel(va_return("%s", ReturnPlayerName(pid)), GetPlayerColor(pid), 0.0, 0.0, 0.2, 10.0, pid, INVALID_VEHICLE_ID, 0, -1, -1);
        
        // This bug, never toggle
        // EnableHealthBarForPlayer(pid, true);
    }
    return 1;
}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart)
{
    PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
    PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);

    UpdateDynamic3DTextLabelText(g_sPlayerHealthBar[playerid], 0xFFFFFFFF, va_return("[{FF00FF}%s{FFFFFF}]", ReturnPlayerHealthBar(playerid)));    
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (newstate == PLAYER_STATE_WASTED)
    {
        ResetPlayerGroupTeam(playerid);
        PutPlayerInCurrentLobby(playerid);
        g_sPlayerInGame{playerid} = false;
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    SendDeathMessage(killerid, playerid, reason);
    return 1;
}

static ReturnPlayerHealthBar(playerid)
{
    new Float:playerHealth, szReturnHealth[24];
    GetPlayerHealth(playerid, playerHealth);

    strcopy(szReturnHealth, gsc_szPlayerHealthBar[floatround(playerHealth) / 10], 24);
    return szReturnHealth;
}