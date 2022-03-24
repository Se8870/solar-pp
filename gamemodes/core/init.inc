#if defined _inc_init
    #undef _inc_init
#endif

#if defined _inc_init_included
    #endinput
#endif

#define _inc_init_included

#include <lobby>
#include <team>
#include <game>

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    new
        moduleCount;

    // Init each module.
    print("Initializing module...");
    
    // Count how many modules are loaded.
    if (Init_Lobby()) moduleCount ++;
    if (Init_Team()) moduleCount ++;
    if (Init_Game()) moduleCount ++;

    // Print the result.
    printf("Loaded %d modules.", moduleCount);
    return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
	// If the player just joined.
	if (!IsPlayerLoggedIn(playerid) && !IsPlayerKicked(playerid))
	{
		// Set corresponding time
		SetPlayerTime(playerid, 12, 00);
		
		// Toggle spectate and show the menus.
		TogglePlayerSpectating(playerid, true);
		ShowLobbyMenuForPlayer(playerid);	
		return 1;
	}

	// If the player has joined, but pressed F4 or smth.
	if (IsPlayerLoggedIn(playerid) && !IsPlayerKicked(playerid) && GetPlayerCurrentLobby(playerid) != INVALID_LOBBY_ID)
	{
		PutPlayerInCurrentLobby(playerid);
		return 1;
	}
	return 1;
}