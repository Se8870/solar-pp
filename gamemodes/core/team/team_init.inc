#if defined _inc_team_init
    #undef _inc_team_init
#endif

#if defined _inc_team_init_included
    #endinput
#endif

#define _inc_team_init_included

#include <YSI_Players\y_groups>
#include <utils\common>

static
    Group:g_sGroupRobbers,
    Group:g_sGroupPolice,
    Group:g_sGroupCuffed,
    g_sPlayerCurrentTeam[MAX_PLAYERS];

Init_Team()
{
    // Team 0, team 1, and team 2. Makes total of 3 teams.
    SetTeamCount(3);
    
    g_sGroupRobbers = Group_Create("Police Team");
    g_sGroupPolice = Group_Create("Robber Team");
    g_sGroupCuffed = Group_Create("Cuffed Team");

    // Set each group colors
    //Group_SetColor(g_sGroupRobbers, 0xFF0000FF);
    //Group_SetColor(g_sGroupPolice, 0x0000FFFF);
    print("Module \"teams.inc\"... OK");
    return 1;
}

Group:GetGroupTeamId(team)
{
    if (team == GROUP_TEAM_ROBBERS)
        return (g_sGroupRobbers);
    
    if (team == GROUP_TEAM_POLICE)
        return (g_sGroupPolice);
    
    if (team == GROUP_TEAM_CUFFED)
        return (g_sGroupCuffed);

    return Group:-1;
}

GetGroupTeamMemberCount(team)
{
    // Give false return if the team out of range.
    if (team == GROUP_TEAM_ROBBERS)
        return Group_GetCount(g_sGroupRobbers);
    
    if (team == GROUP_TEAM_POLICE)
        return Group_GetCount(g_sGroupPolice);

    if (team == GROUP_TEAM_CUFFED)
        return Group_GetCount(g_sGroupCuffed);

    return -1;
}

ResetPlayerGroupTeam(playerid)
{
    // Reset all teams
    Group_SetPlayer(g_sGroupRobbers, playerid, false);
    Group_SetPlayer(g_sGroupPolice, playerid, false);
    Group_SetPlayer(g_sGroupCuffed, playerid, false);

    // Reset their colors too
    SetPlayerColor(playerid, 0xFFFFFFFF);
    return 1;
}

GetPlayerGroupTeam(playerid)
{
    return g_sPlayerCurrentTeam[playerid];
}

PutPlayerInRobberTeam(playerid)
{
    ResetPlayerGroupTeam(playerid);

    SetPlayerSkin(playerid, 152);
    SetPlayerColor(playerid, 0xFF0000FF);
    UpdateNameTagColorForPlayer(playerid, 0xFF0000FF);

    Group_SetPlayer(g_sGroupRobbers, playerid, true);
    g_sPlayerCurrentTeam[playerid] = GROUP_TEAM_ROBBERS;
    return 1;
}

PutPlayerInPoliceTeam(playerid)
{
    ResetPlayerGroupTeam(playerid);

    SetPlayerSkin(playerid, 246);
    SetPlayerColor(playerid, 0x0000FFFF);
    UpdateNameTagColorForPlayer(playerid, 0x0000FFFF);

    Group_SetPlayer(g_sGroupPolice, playerid, true);
    g_sPlayerCurrentTeam[playerid] = GROUP_TEAM_POLICE;
    return 1;
}

PutPlayerInCuffedTeam(playerid)
{
    ResetPlayerGroupTeam(playerid);

    SetPlayerSkin(playerid, 152);
    SetPlayerColor(playerid, 0x0000FFFF);
    UpdateNameTagColorForPlayer(playerid, 0x0000FFFF);

    Group_SetPlayer(g_sGroupCuffed, playerid, true);
    g_sPlayerCurrentTeam[playerid] = GROUP_TEAM_CUFFED;
    return 1;
}
