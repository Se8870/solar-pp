
#if defined _inc_teams
    #undef _inc_teams
#endif
 
#if defined _inc_teams_included
    #endinput
#endif

#define _inc_teams_included

enum e_PLAYER_TEAMS {
    TEAM_NEUTRAL = 1,
    TEAM_POLICE,
    TEAM_ROBBER
};

static
    Group:g_sPlayerTeams[e_PLAYER_TEAMS];

JoinTeam(playerid, e_PLAYER_TEAMS:teamid)
{
    new e_PLAYER_TEAMS:currentTeam = e_PLAYER_TEAMS:GetPlayerTeam(playerid);
    if (teamid > e_PLAYER_TEAMS:3 || teamid == currentTeam) 
        return 0;

    LeaveTeam(playerid);
    SetPlayerTeam(playerid, _:teamid);

    Group_SetPlayer(g_sPlayerTeams[teamid], playerid, true);
    printf("Joining team: %d", _:teamid);
    return 1;
}

Group:GetCurrentTeam(playerid)
{
    new e_PLAYER_TEAMS:currentTeam = e_PLAYER_TEAMS:GetPlayerTeam(playerid);
    return (g_sPlayerTeams[currentTeam]);
}

LeaveTeam(playerid)
{
    new e_PLAYER_TEAMS:currentTeam = e_PLAYER_TEAMS:GetPlayerTeam(playerid);
    if (currentTeam != TEAM_NEUTRAL)
        return 0;

    SetPlayerTeam(playerid, TEAM_NEUTRAL);
    return 1;
}