
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
    Text3D:g_sRobberStatus[MAX_PLAYERS];

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

IsPlayerInGame(playerid)
{
    return g_sPlayerInGame{playerid};
}

// This function seems impossible to be hooked with, since y_hooks only works
// if you call the function using Call(Local/Remote)Function or SetTimer(Ex)
public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart)
{
    // This matters for avoiding fucking false positive results
    if (!g_sPlayerInGame{playerid}) 
        return false;

    if (issuerid != INVALID_PLAYER_ID)
    {
        // disables damage if the weapon is tazer
        if (weapon == 23 && GetPlayerGroupTeam(issuerid) == GROUP_TEAM_POLICE) 
        {
            PlayerPlaySound(playerid, 6003, 0.0, 0.0, 0.0);
            TogglePlayerControllable(playerid, false);
            
            // Preload anim
            ApplyAnimation(playerid, "CRACK", "null", 4.0, 0, 0, 0, 1, 0, 1);
            ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);

            GameTextForPlayer(playerid, "~r~stunned~w~", 3000, 5);

            SetTimerEx(#OnPlayerUnfreeze, 3000, false, "i", playerid);
            return false;
        }
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
hook OnGameModeInit() 
{
    SetVehiclePassengerDamage(true);
    SetDisableSyncBugs(true);
    ShowNameTags(false);
    SetCustomVendingMachines(false);
    SetKnifeSync(true);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    va_SendClientMessageToAll(0xFFFFFFAA, "Player %s(%d) Leaves the game", ReturnPlayerName(playerid), playerid);

    if (IsValidDynamic3DTextLabel(g_sPlayerHealthBar[playerid]))
        DestroyDynamic3DTextLabel(g_sPlayerHealthBar[playerid]);

    if (IsValidDynamic3DTextLabel(g_sRobberStatus[playerid]))
        DestroyDynamic3DTextLabel(g_sRobberStatus[playerid]);

    ResetPlayerGroupTeam(playerid);
    g_sPlayerInGame{playerid} = false;
    return 1;
}

hook OnGamePreparing(Lobby:id)
{
    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        if (GetPlayerGroupTeam(pid) == GROUP_TEAM_ROBBERS)
        {
            g_sRobberStatus[pid] = CreateDynamic3DTextLabel("(( Cannot be shooted ))", 0xFFFFFFFF,  0.0, 0.0, 0.3, 10.0, pid, INVALID_VEHICLE_ID, 0, -1, -1);
        }
        g_sPlayerHealthBar[pid] = CreateDynamic3DTextLabel(va_return("[{FF00FF}%s{FFFFFF}]", ReturnPlayerHealthBar(pid)), 0xFFFFFFFF,  0.0, 0.0, 0.1, 10.0, pid, INVALID_VEHICLE_ID, 0, -1, -1);
        g_sPlayerInGame{pid} = true;
    }
    return 1;
}

hook OnGameEnded(Lobby:id)
{
    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        if (IsValidDynamic3DTextLabel(g_sPlayerHealthBar[pid]))
            DestroyDynamic3DTextLabel(g_sPlayerHealthBar[pid]);
    
        if (IsValidDynamic3DTextLabel(g_sRobberStatus[pid]))
            DestroyDynamic3DTextLabel(g_sRobberStatus[pid]);

        ResetPlayerGroupTeam(pid);
        PutPlayerInCurrentLobby(pid);
        g_sPlayerInGame{pid} = false;
    }
    return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if (hitid != INVALID_PLAYER_ID)
    {
        printf("hitid = %d | playerid = %d", hitid, playerid);
        if (!g_sPlayerRobberShotFirst{playerid} && GetPlayerGroupTeam(hitid) == GROUP_TEAM_POLICE)
        {
            if (IsValidDynamic3DTextLabel(g_sRobberStatus[playerid]))
                DestroyDynamic3DTextLabel(g_sRobberStatus[playerid]);

            printf("Removing robber status");
            g_sPlayerRobberShotFirst{playerid} = true;
            return true;
        }

        if (!g_sPlayerRobberShotFirst{hitid} && GetPlayerGroupTeam(playerid) == GROUP_TEAM_POLICE) 
        {
            printf("Police attempt to shoot robber who doesn't shot first");
            return false;
        }
    }
    return true;

}

hook OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart)
{
    PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
    PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);

    UpdateDynamic3DTextLabelText(g_sPlayerHealthBar[playerid], 0xFFFFFFFF, va_return("[{FF00FF}%s{FFFFFF}]", ReturnPlayerHealthBar(playerid)));    
    return 1;
}

hook OnPlayerDeathFinished(playerid)
{
    ResetPlayerGroupTeam(playerid);
    PutPlayerInCurrentLobby(playerid);
    g_sPlayerInGame{playerid} = false;
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
