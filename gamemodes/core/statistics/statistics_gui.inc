#if defined _inc_statistics_gui
    #undef _inc_statistics_gui
#endif

#if defined _inc_statistics_gui_included
    #endinput
#endif

#define _inc_statistics_gui_included

#include <progress2>

static  
    Text: g_sStatsTopBox,
    Text: g_sStatsBottomBox,
    Text: g_sStatsLogo,
    Text: g_sRobberCount,
    Text: g_sPoliceCount;

static
    PlayerText: g_sPlayerLobbyInfo[MAX_PLAYERS],
    PlayerBar: g_sPlayerHealthBar[MAX_PLAYERS];

Init_StatisticsGui()
{
    g_sStatsLogo = TextDrawCreate(521.000000, 192.000000, "Solarize Police Pursuits");
    TextDrawFont(g_sStatsLogo, 0);
    TextDrawLetterSize(g_sStatsLogo, 0.495833, 2.199999);
    TextDrawTextSize(g_sStatsLogo, 619.500000, 17.000000);
    TextDrawSetOutline(g_sStatsLogo, 1);
    TextDrawSetShadow(g_sStatsLogo, 0);
    TextDrawAlignment(g_sStatsLogo, 1);
    TextDrawColor(g_sStatsLogo, -1);
    TextDrawBackgroundColor(g_sStatsLogo, 255);
    TextDrawBoxColor(g_sStatsLogo, 50);
    TextDrawUseBox(g_sStatsLogo, 0);
    TextDrawSetProportional(g_sStatsLogo, 1);
    TextDrawSetSelectable(g_sStatsLogo, 0);

    g_sStatsTopBox = TextDrawCreate(570.000000, 241.000000, "_");
    TextDrawFont(g_sStatsTopBox, 1);
    TextDrawLetterSize(g_sStatsTopBox, 0.995832, 2.300003);
    TextDrawTextSize(g_sStatsTopBox, 308.500000, 95.000000);
    TextDrawSetOutline(g_sStatsTopBox, 1);
    TextDrawSetShadow(g_sStatsTopBox, 0);
    TextDrawAlignment(g_sStatsTopBox, 2);
    TextDrawColor(g_sStatsTopBox, -1);
    TextDrawBackgroundColor(g_sStatsTopBox, 255);
    TextDrawBoxColor(g_sStatsTopBox, 135);
    TextDrawUseBox(g_sStatsTopBox, 1);
    TextDrawSetProportional(g_sStatsTopBox, 1);
    TextDrawSetSelectable(g_sStatsTopBox, 0);

    g_sStatsBottomBox = TextDrawCreate(570.000000, 271.000000, "_");
    TextDrawFont(g_sStatsBottomBox, 1);
    TextDrawLetterSize(g_sStatsBottomBox, 0.995832, 6.300003);
    TextDrawTextSize(g_sStatsBottomBox, 308.500000, 95.000000);
    TextDrawSetOutline(g_sStatsBottomBox, 1);
    TextDrawSetShadow(g_sStatsBottomBox, 0);
    TextDrawAlignment(g_sStatsBottomBox, 2);
    TextDrawColor(g_sStatsBottomBox, -1);
    TextDrawBackgroundColor(g_sStatsBottomBox, 255);
    TextDrawBoxColor(g_sStatsBottomBox, 135);
    TextDrawUseBox(g_sStatsBottomBox, 1);
    TextDrawSetProportional(g_sStatsBottomBox, 1);
    TextDrawSetSelectable(g_sStatsBottomBox, 0);

    g_sPoliceCount = TextDrawCreate(524.000000, 282.000000, "Police Left: 12");
    TextDrawFont(g_sPoliceCount, 1);
    TextDrawLetterSize(g_sPoliceCount, 0.299997, 1.550001);
    TextDrawTextSize(g_sPoliceCount, 616.000000, 72.000000);
    TextDrawSetOutline(g_sPoliceCount, 1);
    TextDrawSetShadow(g_sPoliceCount, 0);
    TextDrawAlignment(g_sPoliceCount, 1);
    TextDrawColor(g_sPoliceCount, 65535);
    TextDrawBackgroundColor(g_sPoliceCount, 255);
    TextDrawBoxColor(g_sPoliceCount, 50);
    TextDrawUseBox(g_sPoliceCount, 0);
    TextDrawSetProportional(g_sPoliceCount, 1);
    TextDrawSetSelectable(g_sPoliceCount, 0);

    g_sRobberCount = TextDrawCreate(524.000000, 302.000000, "Robber Left: 12");
    TextDrawFont(g_sRobberCount, 1);
    TextDrawLetterSize(g_sRobberCount, 0.279166, 1.450001);
    TextDrawTextSize(g_sRobberCount, 616.000000, 72.000000);
    TextDrawSetOutline(g_sRobberCount, 1);
    TextDrawSetShadow(g_sRobberCount, 0);
    TextDrawAlignment(g_sRobberCount, 1);
    TextDrawColor(g_sRobberCount, -16776961);
    TextDrawBackgroundColor(g_sRobberCount, 255);
    TextDrawBoxColor(g_sRobberCount, 50);
    TextDrawUseBox(g_sRobberCount, 0);
    TextDrawSetProportional(g_sRobberCount, 1);
    TextDrawSetSelectable(g_sRobberCount, 0);
    return 1;
}

ShowServerStatisticsForPlayer(playerid)
{
    g_sPlayerLobbyInfo[playerid] = CreatePlayerTextDraw(playerid, 524.000000, 292.000000, "Lobby: Archeus");
    PlayerTextDrawFont(playerid, g_sPlayerLobbyInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, g_sPlayerLobbyInfo[playerid], 0.279166, 1.450001);
    PlayerTextDrawTextSize(playerid, g_sPlayerLobbyInfo[playerid], 616.000000, 72.000000);
    PlayerTextDrawSetOutline(playerid, g_sPlayerLobbyInfo[playerid], 1);
    PlayerTextDrawSetShadow(playerid, g_sPlayerLobbyInfo[playerid], 0);
    PlayerTextDrawAlignment(playerid, g_sPlayerLobbyInfo[playerid], 1);
    PlayerTextDrawColor(playerid, g_sPlayerLobbyInfo[playerid], -16776961);
    PlayerTextDrawBackgroundColor(playerid, g_sPlayerLobbyInfo[playerid], 255);
    PlayerTextDrawBoxColor(playerid, g_sPlayerLobbyInfo[playerid], 50);
    PlayerTextDrawUseBox(playerid, g_sPlayerLobbyInfo[playerid], 0);
    PlayerTextDrawSetProportional(playerid, g_sPlayerLobbyInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, g_sPlayerLobbyInfo[playerid], 0); 

    new Float:playerHealth;
    GetPlayerHealth(playerid, playerHealth);

    g_sPlayerHealthBar[playerid] = CreatePlayerProgressBar(playerid, 525.000000, 244.000000, 92.500000, 15.000000, -1962934017, 100.000000, 0);
    SetPlayerProgressBarValue(playerid, g_sPlayerHealthBar[playerid], playerHealth);

    // 1. Logo
    TextDrawShowForPlayer(playerid, g_sStatsLogo);

    // 2. Top box for healths
    TextDrawShowForPlayer(playerid, g_sStatsTopBox);
    ShowPlayerProgressBar(playerid, g_sPlayerHealthBar[playerid]);

    // 2. Bottom box with lobby status or game status
    TextDrawShowForPlayer(playerid, g_sStatsBottomBox);

    if (IsPlayerInGame(playerid))
    {
        UpdateInGameStatisticsForPlayer(playerid);
    }
    else if (GetPlayerCurrentLobby(playerid) != INVALID_LOBBY_ID)
    {
        UpdateLobbyStatisticsForPlayer(playerid);
    }
    return 1;
}

ResetServerStatisticsForPlayer(playerid)
{
    DestroyPlayerProgressBar(playerid, g_sPlayerHealthBar[playerid]);
    PlayerTextDrawDestroy(playerid, g_sPlayerLobbyInfo[playerid]);

    // 1. Logo
    TextDrawHideForPlayer(playerid, g_sStatsLogo);

    // 2. Top box for healths
    TextDrawHideForPlayer(playerid, g_sStatsTopBox);

    // 2. Bottom box with lobby status or game status
    TextDrawHideForPlayer(playerid, g_sStatsBottomBox);

    if (IsPlayerInGame(playerid))
    {
        TextDrawHideForPlayer(playerid, g_sPoliceCount);
        TextDrawHideForPlayer(playerid, g_sRobberCount);
    }
    return 1;
}

UpdateLobbyStatisticsForPlayer(playerid)
{
    if (GetPlayerCurrentLobby(playerid) == INVALID_LOBBY_ID) 
        return 0;

    if (IsPlayerInGame(playerid)) 
        return 0;

    TextDrawHideForPlayer(playerid, g_sPoliceCount);
    TextDrawHideForPlayer(playerid, g_sRobberCount);

    PlayerTextDrawHide(playerid, g_sPlayerLobbyInfo[playerid]);

    new szLobbyName[MAX_LOBBY_NAME];
    GetCurrentLobbyName(playerid, szLobbyName, MAX_LOBBY_NAME);
    PlayerTextDrawSetString(playerid, g_sPlayerLobbyInfo[playerid],  va_return("Lobby: %s", szLobbyName));

    PlayerTextDrawShow(playerid, g_sPlayerLobbyInfo[playerid]);
    return 1;
}

UpdateInGameStatisticsForPlayer(playerid)
{
    if (!IsPlayerInGame(playerid)) return 0;

    PlayerTextDrawHide(playerid, g_sPlayerLobbyInfo[playerid]);

    TextDrawHideForPlayer(playerid, g_sPoliceCount);
    TextDrawHideForPlayer(playerid, g_sRobberCount);

    TextDrawSetString(g_sPoliceCount, va_return("Police Left: %d", GetGroupTeamMemberCount(GROUP_TEAM_POLICE)));
    TextDrawSetString(g_sRobberCount, va_return("Robber Left: %d", GetGroupTeamMemberCount(GROUP_TEAM_ROBBERS)));

    TextDrawShowForPlayer(playerid, g_sPoliceCount);
    TextDrawShowForPlayer(playerid, g_sRobberCount);
    return 1;
}
