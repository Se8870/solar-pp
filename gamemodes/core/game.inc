
#if defined _inc_game
    #undef _inc_game
#endif
 
#if defined _inc_game_included
    #endinput
#endif

#define _inc_game_included

#define GAME_STATUS_PREPARING   0
#define GAME_STATUS_STARTING    1

static
    bool:g_sPlayerInGame[MAX_PLAYERS];

//#include <YSI_Coding\y_hooks>

#include <YSI_Coding\y_timers>
task CoreTimer[1000]()
{
    static
        gameStatus[MAX_LOBBY], remainderTime[MAX_LOBBY], bool:timerInit;

    // Must been on loop, because we want to fetch all lobbies. Creating each individual timer for lobby is also good
    // But maybe comming soon.
    for (new i; i < MAX_LOBBY; i ++)
    {
        if (gameStatus[i] == GAME_STATUS_PREPARING)
        {
            if (remainderTime[i] < 0 && CountPlayerInLobby(i) < 4)
            {
                remainderTime[i] = RandomMinMax(10, 30);

                // continue if init, else just loop and continue.
                if (!timerInit) {
                    printf("Timer init passed.");
                    timerInit = true;
                    continue;
                }

                Group:Group_SetBalanced(Group_GetRandom, Group:g0, Group:g1, Group:...)

                foreach (new j : GroupMember[GetLobbyGroupId(i)])
                {
                    // It's actually showing up to 8 seconds, the timer is a lie.
                    GameTextForPlayer(j, "Game cannot started due to lack of players.", 1000, 1);
                }
                continue;
            }

            // Start counting down from 5 to 0, dunno why but i kinda like it tough.
            if (remainderTime[i] < 6)
            {
                // Fetch any player from each lobbies to count down
                foreach (new j : GroupMember[GetLobbyGroupId(i)])
                {
                    GameTextForPlayer(j, va_return("Game starting in: %d seconds.", remainderTime[i]), 1000, 6);
                }
            }

            // Decrement if anything above is done
            remainderTime[i] --;
            return 1;
        }
        if (gameStatus[i] == GAME_STATUS_STARTING)
        {
            // Comming Soon
        }
    }
    return 1;
}