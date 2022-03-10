
#if defined _inc_map_sapd_included
    #endinput
#endif

#define _inc_map_sapd_included

static
    PlayerText:g_sPlayerTextMessage[MAX_PLAYERS];

stock ShowMessageTextDrawToPlayer(playerid, const message[], bool:cache = true)
{
    // Create textdraw here.
    if (!g_sPlayerTextMessage[playerid])
    {
        g_sPlayerTextMessage[playerid] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "Hello World");
        // ...
    }

    // Show it here
    PlayerTextDrawShow(playerid, g_sPlayerTextMessage[playerid]);
    return 1;
}
