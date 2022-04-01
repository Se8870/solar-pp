#if defined _inc_statistics_init
    #undef _inc_statistics_init
#endif

#if defined _inc_statistics_init_included
    #endinput
#endif

#define _inc_statistics_init_included

Init_Statistics()
{
    Init_StatisticsGui();
}

#include <YSI_Coding\y_hooks>
hook OnPlayerJoinedLobby(playerid)
{
    ShowServerStatisticsForPlayer(playerid);
}

hook OnGamePreparing(Lobby:id)
{
    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        UpdateInGameStatisticsForPlayer(pid);
    }
    return 1;
}

hook OnGameEnded(Lobby:id)
{
    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        UpdateLobbyStatisticsForPlayer(pid);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    ResetServerStatisticsForPlayer(playerid);
    return 1;
}