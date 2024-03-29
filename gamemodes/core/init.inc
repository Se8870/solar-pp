#if defined _inc_init
    #undef _inc_init
#endif

#if defined _inc_init_included
    #endinput
#endif

#define _inc_init_included

// This shit keep bragging about literal array lmao
#pragma warning disable 214
#pragma warning disable 239

// AC Config
#define     AC_USE_AMMUNATIONS          false
#define     AC_USE_RESTAURANTS          false
#define     AC_USE_VENDING_MACHINES     false
#define     AC_USE_TUNING_GARAGES       false
#define     AC_USE_PAYNSPRAY            false

#define     AC_USE_CASINOS              false
#define     AC_USE_NPC                  false

#define     AC_MAX_CONNECTS_FROM_IP     5
#define     AC_MAX_RCON_LOGIN_ATTEMPT   0
#define     AC_MAX_PING                 2000

// I place this here because there is unknown error, of course i suspect nex-ac is the culprit.
// But until it's fixed, it stays here
#include <sscanf2>
#include <YSI_Visual\y_dialog>
#include <nex-ac>

#include <streamer>

#include <lobby>
#include <team>
#include <game>

#include <statistics>

#include <utils\textdraw\watermark>

static
	Text3D:g_sPlayerTextName[MAX_PLAYERS];

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    new
        moduleCount;

	print("Configuring ingame environment...");
	
	DisableInteriorEnterExits();
	UsePlayerPedAnims();
	EnableStuntBonusForAll(false);
	SetWorldTime(00);
	AllowAdminTeleport(false);

    // Init each module.
    print("Initializing module...");
    
    // Count how many modules are loaded.
    if (Init_Lobby()) moduleCount ++;
    if (Init_Team()) moduleCount ++;
    if (Init_Game()) moduleCount ++;
	if (Init_Statistics()) moduleCount ++;

    // Print the result.
    printf("Loaded %d modules.", moduleCount);
    return 1;
}

UpdateNameTagColorForPlayer(playerid, color)
{
	Update3DTextLabelText(g_sPlayerTextName[playerid], color, va_return("%s", ReturnPlayerName(playerid)));
	return 1;
}

hook OnPlayerConnect(playerid)
{
	SetPlayerColor(playerid, 0xFFFFFF);
	g_sPlayerTextName[playerid] = CreateDynamic3DTextLabel(va_return("%s", ReturnPlayerName(playerid)), 0xFFFFFFFF, 0.0, 0.0, 0.4, 10.0, playerid, INVALID_VEHICLE_ID, 0, -1, -1);
	//Streamer_ToggleIdleUpdate(playerid, true);
	return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
	// If the player just joined.
	if (!IsPlayerLoggedIn(playerid) && !IsPlayerKicked(playerid))
	{
		// Set corresponding time
		SetPlayerTime(playerid, 12, 00);
		
        // This bug, never toggle
        EnableHealthBarForPlayer(playerid, false);

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

hook OnPlayerDisconnect(playerid, reason)
{
	if (IsValidDynamic3DTextLabel(g_sPlayerTextName[playerid]))
		DestroyDynamic3DTextLabel(g_sPlayerTextName[playerid]);

	return 1;
}
