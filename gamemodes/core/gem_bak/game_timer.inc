#if defined _inc_game_timer
    #undef _inc_game_timer
#endif

#if defined _inc_game_timer_included
    #endinput
#endif

#define _inc_game_timer_included

#include <YSI_Coding\y_timers>

static
    g_sLobbyRemainderTime[MAX_LOBBY char],
    g_sGameRemainderTime[MAX_LOBBY char];

task GameUpdate[1000]()
{
    for (new Lobby:i = Lobby:0; i < MAX_LOBBY; i ++)
    {
        if (GetLobbyGameStatus(i) == GAME_STATUS_QUEUE)
        {
            if (g_sLobbyRemainderTime{i} < 1)
            {
                SetLobbyGameStatus(i, GAME_STATUS_PREPARING);
            }

            // After above checking, we check again if it's still below 5 but not 0
            if (g_sLobbyRemainderTime{i} < 6 && g_sLobbyRemainderTime{i} != 0)
            {
                // Fetch any player from each lobbies to count down
                foreach (new j : GroupMember(GetLobbyGroupId(i)))
                {
                    GameTextForPlayer(j, va_return("Game starting in: %d seconds.", g_sLobbyRemainderTime{i}), 1000, 6);
                }
            }
            g_sLobbyRemainderTime{i} --;
        }
        else if (GetLobbyGameStatus(i) == GAME_STATUS_PREPARING)
        {
            if (GetPlayerLobbyCount(i) < 4)
            {
                // Send message for ALL people from the lobby
                SendCurrentLobbyMessage(i, "Game cannot started due to lack of players.", 1000, 1);
                
                // Reset the timer, skip to the next lobby.
                g_sLobbyRemainderTime{i} = RandomMinMax(30, 50);
                SetLobbyGameStatus(i, GAME_STATUS_QUEUE);
                continue;
            }
            else
            {
                PrepareGameForLobbyId(i);
                SpreadPlayers(i);

                // Setting up the status before we begin.
                g_sGameRemainderTime{i} = 600; // 10 minute playtime
                SetLobbyGameStatus(i, GAME_STATUS_MONITORING);
                continue;
            }
        }
        else if (GetLobbyGameStatus(i) == GAME_STATUS_MONITORING)
        {
            // Do stuff here
            if (g_sGameRemainderTime{i} < 1)
            {
                SetLobbyGameStatus(i, GAME_STATUS_ENDING);
                continue;
            }

            if (GetGroupTeamMemberCount(GROUP_TEAM_ROBBERS) == 0 || GetGroupTeamMemberCount(GROUP_TEAM_POLICE) == 0)
            {
                SetLobbyGameStatus(i, GAME_STATUS_ENDING);
                continue;
            }
            
            g_sGameRemainderTime{i} --;
        }
        else if (GetLobbyGameStatus(i) == GAME_STATUS_ENDING)
        {
            foreach (new pid : GroupMember(GetLobbyGroupId(i)))
            {
                // Put back to lobby if it's alreay ingame.
                if (!ResetPlayerGame(pid))
                    continue;

                PutPlayerInCurrentLobby(pid);
            }

            SetLobbyGameStatus(i, GAME_STATUS_QUEUE);
        }
    }
    return 1;
}
