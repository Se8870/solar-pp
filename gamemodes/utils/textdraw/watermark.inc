#if defined _inc_watermark
    #undef _inc_watermark
#endif

#if defined _inc_watermark_included
    #endinput
#endif

#define _inc_watermark_included

static
    Text: g_sPlayerWatermark[3];

stock ShowServerWatermark()
{
    g_sPlayerWatermark[0] = TextDrawCreate(320.000000, 5.000000, "Solarize");
    TextDrawFont(g_sPlayerWatermark[0], 3);
    TextDrawLetterSize(g_sPlayerWatermark[0], 0.574999, 1.750000);
    TextDrawTextSize(g_sPlayerWatermark[0], 400.000000, 17.000000);
    TextDrawSetOutline(g_sPlayerWatermark[0], 1);
    TextDrawSetShadow(g_sPlayerWatermark[0], 0);
    TextDrawAlignment(g_sPlayerWatermark[0], 2);
    TextDrawColor(g_sPlayerWatermark[0], -764862721);
    TextDrawBackgroundColor(g_sPlayerWatermark[0], 255);
    TextDrawBoxColor(g_sPlayerWatermark[0], 50);
    TextDrawUseBox(g_sPlayerWatermark[0], 0);
    TextDrawSetProportional(g_sPlayerWatermark[0], 1);
    TextDrawSetSelectable(g_sPlayerWatermark[0], 0);

    g_sPlayerWatermark[1] = TextDrawCreate(281.000000, 22.000000, "Police");
    TextDrawFont(g_sPlayerWatermark[1], 3);
    TextDrawLetterSize(g_sPlayerWatermark[1], 0.574999, 1.750000);
    TextDrawTextSize(g_sPlayerWatermark[1], 400.000000, 17.000000);
    TextDrawSetOutline(g_sPlayerWatermark[1], 1);
    TextDrawSetShadow(g_sPlayerWatermark[1], 0);
    TextDrawAlignment(g_sPlayerWatermark[1], 2);
    TextDrawColor(g_sPlayerWatermark[1], -1);
    TextDrawBackgroundColor(g_sPlayerWatermark[1], 255);
    TextDrawBoxColor(g_sPlayerWatermark[1], 50);
    TextDrawUseBox(g_sPlayerWatermark[1], 0);
    TextDrawSetProportional(g_sPlayerWatermark[1], 1);
    TextDrawSetSelectable(g_sPlayerWatermark[1], 0);

    g_sPlayerWatermark[2] = TextDrawCreate(355.000000, 22.000000, "Pursuit");
    TextDrawFont(g_sPlayerWatermark[2], 3);
    TextDrawLetterSize(g_sPlayerWatermark[2], 0.574999, 1.750000);
    TextDrawTextSize(g_sPlayerWatermark[2], 400.000000, 17.000000);
    TextDrawSetOutline(g_sPlayerWatermark[2], 1);
    TextDrawSetShadow(g_sPlayerWatermark[2], 0);
    TextDrawAlignment(g_sPlayerWatermark[2], 2);
    TextDrawColor(g_sPlayerWatermark[2], -1);
    TextDrawBackgroundColor(g_sPlayerWatermark[2], 255);
    TextDrawBoxColor(g_sPlayerWatermark[2], 50);
    TextDrawUseBox(g_sPlayerWatermark[2], 0);
    TextDrawSetProportional(g_sPlayerWatermark[2], 1);
    TextDrawSetSelectable(g_sPlayerWatermark[2], 0);
    return 1;
}

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
    ShowServerWatermark();

    for(new i = 0; i < 3; i++)
    {
        TextDrawShowForPlayer(playerid, g_sPlayerWatermark[i]);
    }    
    return Y_HOOKS_CONTINUE_RETURN_1;

}