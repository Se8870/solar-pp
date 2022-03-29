#if defined _inc_lobby_msg
    #undef _inc_lobby_msg
#endif

#if defined _inc_lobby_msg_included
    #endinput
#endif

#define _inc_lobby_msg_included

SendCurrentLobbyMessage(Lobby:id, const string:message[], {Float, bool, _}:...)
{
    if (id == INVALID_LOBBY_ID) 
        return 0;

    if (GetPlayerLobbyCount(id) == 0) 
        return 0;

    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        //va_SendClientMessage(playerid, color, message, ___(3));
        va_GameTextForPlayer(pid, message, 1000, 1, ___(2));
    }
    return 1;
}
