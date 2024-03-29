
#if defined _inc_lobby_gui
    #undef _inc_lobby_gui
#endif

#if defined _inc_lobby_gui_included
    #endinput
#endif

#define _inc_lobby_gui_included

#include <YSI_Server\y_colors>
#include <YSI_Visual\y_dialog>

ShowLobbyMenuForPlayer(playerid)
{
    new 
        szLobbyList[512]; // max lobby name * max lobby + additional line

    format(szLobbyList, sizeof(szLobbyList), "Lobby Name\tMax Player(s)\n");

    for (new Lobby:i = Lobby:0; i < MAX_LOBBY; i ++)
    {
        new szLobbyName[MAX_LOBBY_NAME];
    
        GetLobbyName(i, szLobbyName);
        format(szLobbyList, sizeof(szLobbyList), "%s%s\t%d/"#MAX_PLAYER_IN_LOBBY"\n", szLobbyList, szLobbyName, GetPlayerLobbyCount(i));
    }

    inline Dialog_LobbyMenuResponse(response, listitem, string:inputtext[])
    {
        #pragma unused inputtext
        
        if (!response) 
            return Kick(playerid);

        if (!PutPlayerInLobby(playerid, Lobby:listitem))
        {
            SendClientMessage(playerid, X11_TOMATO, "ERROR: This lobby is full.");
            ShowLobbyMenuForPlayer(playerid);
        }
        else
        {
            SendClientMessage(playerid, X11_LIGHTBLUE, "SERVER:"WHITE" Successfully joined the lobby.");
        }
    }

    Dialog_ShowCallback(playerid, using inline Dialog_LobbyMenuResponse, DIALOG_STYLE_TABLIST_HEADERS, "Solarize Roleplay | Lobby Menu", szLobbyList, "Select", "Exit");
    return 1;
}
