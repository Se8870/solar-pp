#if defined _inc_game_timer
    #undef _inc_game_timer
#endif

#if defined _inc_game_timer_included
    #endinput
#endif

#define _inc_game_timer_included

#include <YSI_Coding\y_timers>
#include <YSI_Core\y_utils>

task Game_CoreTimer[1000]()
{
    static 
        e_LOBBY_GAME_STATUS:gameStatusPerLobby[MAX_LOBBY char], 
        lobbyRemainderTime[MAX_LOBBY char],
        gameRemainderTime[MAX_LOBBY char];

    // Handle all lobby whenever possible
    for (new Lobby:i = Lobby:0; i < MAX_LOBBY; i ++)
    {
        if (gameStatusPerLobby{i} == GAME_STATUS_QUEUE)
        {
            if (lobbyRemainderTime{i} < 1)
            {
               gameStatusPerLobby{i} = GAME_STATUS_PREPARING;
            }

            // After above checking, we check again if it's still below 5 but not 0
            if (lobbyRemainderTime{i} < 6 && lobbyRemainderTime{i} != 0)
            {
                // Fetch any player from each lobbies to count down
                foreach (new j : GroupMember(GetLobbyGroupId(i)))
                {
                    GameTextForPlayer(j, va_return("Game starting in: %d seconds.", lobbyRemainderTime{i}), 1000, 6);
                }
            }
            lobbyRemainderTime{i} --;
        }
        else if (gameStatusPerLobby{i} == GAME_STATUS_PREPARING)
        {
            if (GetPlayerLobbyCount(i) < 4)
            {
                // Send message for ALL people from the lobby
                SendCurrentLobbyMessage(i, "Game cannot started due to lack of players.", 1000, 1);
                
                // Reset the timer, skip to the next lobby.
                lobbyRemainderTime{i} = RandomMinMax(30, 50);
                gameStatusPerLobby{i} = GAME_STATUS_QUEUE;
                continue;
            }
            else
            {
                foreach (new j : GroupMember(GetLobbyGroupId(i)))
                {
                    PutPlayerInQueue(j, i);
                }
                SpreadPlayersInLobby(i);

                gameRemainderTime{i} = GAME_PLAYTIME;
                gameStatusPerLobby{i} = GAME_STATUS_MONITORING;
                continue;
            }
        }
        else if (gameStatusPerLobby{i} == GAME_STATUS_MONITORING)
        {
            // UwU
            if (--gameRemainderTime{i} < 1)
            {
                gameStatusPerLobby{i} = GAME_STATUS_ENDING;
                continue;
            }

            if (gameRemainderTime{i} < 599)
            {
                if(GetGroupTeamMemberCount(GROUP_TEAM_ROBBERS) == 0 || GetGroupTeamMemberCount(GROUP_TEAM_POLICE) == 0)
                {
                    printf("The game is about to end for some reason!");
                    gameStatusPerLobby{i} = GAME_STATUS_ENDING;
                    continue;
                }

                if (GetGroupTeamMemberCount(GROUP_TEAM_CUFFED) > GetGroupTeamMemberCount(GROUP_TEAM_ROBBERS))
                {
                    gameStatusPerLobby{i} = GAME_STATUS_ENDING;
                    continue;
                }
            }
        }
        else if (gameStatusPerLobby{i} == GAME_STATUS_ENDING)
        {
            // Call our callback
            CallLocalFunction(#OnGameEnded, "i", _:i);

            // Reset the timer, skip to the next lobby.
            lobbyRemainderTime{i} = RandomMinMax(30, 50);
            gameStatusPerLobby{i} = GAME_STATUS_QUEUE;
        }
    }
    return 1;
}
