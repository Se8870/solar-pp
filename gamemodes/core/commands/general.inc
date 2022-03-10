#if defined _inc_general_command_included
    #endinput
#endif

#define _inc_general_command_included

#include <YSI_Visual\y_commands>
#include <sscanf2>

YCMD:help(playerid, string:params[], help)
{
    SendClientMessage(playerid, 0xFFFFFFAA, "/lobby, /spec");
    return 1;
}

YCMD:spec(playerid, string:params[], help)
{
    SendClientMessage(playerid, 0xFFFFFFAA, "Comming soon");
    return 1;
}

YCMD:lobby(playerid, string:params[], help)
{
    if (help)
        return SendClientMessage(playerid, 0xFFFFFFAA, "Use join <lobby id> or leave!");

    new cmdCategory[24], cmdValue[128];
    if (sscanf(params, "s[24]S()[128]", cmdCategory, cmdValue))
        return SendClientMessage(playerid, 0xFFFFFFAA, "/lobby [join/now/leave]");

    if (!strcmp(cmdCategory, "join", true))
    {
        new lobbyid;
        if (sscanf(cmdValue, "i", lobbyid))
            return SendClientMessage(playerid, 0xFFFFFFAA, "/lobby [join] <lobby id>");
        
        if (!(0 <= lobbyid <= 2))
            return SendClientMessage(playerid, 0xFFFFFFAA, "Invalid lobby ids");
    
        JoinLobby(playerid, lobbyid);
        SendClientMessage(playerid, 0xFFFFFFAA, "Joining lobbys");
        return 1;
    }
    else if (!strcmp(cmdCategory, "now", true))
    {
        new lobbyName[32], lobbyId, playerCount;
        GetPlayerLobbyInfo(playerid, lobbyName, lobbyId, playerCount);

        Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Solarize Police Pursuit - Current Lobby", va_return("You're now in lobby %s (%d)\nWith %d players", lobbyName, lobbyId, playerCount), "Close", "");
        return 1;
    }
    else if (!strcmp(cmdCategory, "leave", true))
    {
        PutPlayerInLobbyMenu(playerid);
        SendClientMessage(playerid, 0xFFFFFFAA, "Leaving lobbys");
        return 1;
    }
    SendClientMessage(playerid, 0xFFFFFFAA, "Invalid command category");
    return 1;
}  