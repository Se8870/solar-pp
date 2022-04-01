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
    Group:g_sGroupLists[3];

Init_Team()
{
    // Team 0, team 1, and team 2. Makes total of 3 teams.
    SetTeamCount(3);
    
    g_sGroupLists[GROUP_TEAM_POLICE] = Group_Create("Police Team");
    g_sGroupLists[GROUP_TEAM_ROBBERS] = Group_Create("Robber Team");

    // Set each group colors
    Group_SetColor(g_sGroupLists[GROUP_TEAM_POLICE], 0x19639FFF);
    Group_SetColor(g_sGroupLists[GROUP_TEAM_ROBBERS], 0xFF0000FF);
    print("Module \"teams.inc\"... OK");
    return 1;
}

Group:GetGroupTeamId(team)
{
    return (g_sGroupLists[team]);
}

GetGroupTeamMemberCount(team)
{
    // Give false return if the team out of range.
    if (team != GROUP_TEAM_ROBBERS && team != GROUP_TEAM_POLICE)
        return 0;
        
    return (Group_GetCount(g_sGroupLists[team]));
}

ResetPlayerGroupTeam(playerid)
{
    // Reset all teams
    Group_SetPlayer(g_sGroupLists[GROUP_TEAM_ROBBERS], playerid, false);
    Group_SetPlayer(g_sGroupLists[GROUP_TEAM_POLICE], playerid, false);

    // Reset their colors too
    SetPlayerColor(playerid, 0xFFFFFFFF);
    return 1;
}

GetPlayerGroupTeam(playerid)
{
    return (Group_GetPlayer(g_sGroupLists[GROUP_TEAM_ROBBERS], playerid) ? GROUP_TEAM_ROBBERS : GROUP_TEAM_POLICE);
}

PutPlayerInRobberTeam(playerid)
{
    SetPlayerSkin(playerid, 152);
    SetPlayerColor(playerid, 0xFF0000FF);
    return SetPlayerGroupTeam(playerid, GROUP_TEAM_ROBBERS, true);
}

PutPlayerInPoliceTeam(playerid)
{
    SetPlayerSkin(playerid, 246);
    SetPlayerColor(playerid, 0x19639FFF);
    return SetPlayerGroupTeam(playerid, GROUP_TEAM_POLICE, true);
}

static SetPlayerGroupTeam(playerid, team, bool:toggle)
{
    // Give false return if the team out of range.
    if (team != GROUP_TEAM_ROBBERS && team != GROUP_TEAM_POLICE)
        return 0;

    // Skip if the same group has been set to player.
    if (GetPlayerGroupTeam(playerid) == team && toggle == true)
        return 1;

    // Set corresponding group.
    ResetPlayerGroupTeam(playerid);
    Group_SetPlayer(g_sGroupLists[team], playerid, toggle);

    // Set team 
    SetPlayerTeam(playerid, team);
    return 1;
}