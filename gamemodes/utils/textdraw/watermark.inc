static
    Text:g_sPlayerWatermark[MAX_PLAYERS][3];

stock ShowServerWatermark(playerid)
{
    g_sPlayerWatermark[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 5.000000, "Solarize");
    PlayerTextDrawFont(playerid, g_sPlayerWatermark[playerid][0], 3);
    PlayerTextDrawLetterSize(playerid, g_sPlayerWatermark[playerid][0], 0.574999, 1.750000);
    PlayerTextDrawTextSize(playerid, g_sPlayerWatermark[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, g_sPlayerWatermark[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, g_sPlayerWatermark[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, g_sPlayerWatermark[playerid][0], 2);
    PlayerTextDrawColor(playerid, g_sPlayerWatermark[playerid][0], -764862721);
    PlayerTextDrawBackgroundColor(playerid, g_sPlayerWatermark[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, g_sPlayerWatermark[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, g_sPlayerWatermark[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, g_sPlayerWatermark[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, g_sPlayerWatermark[playerid][0], 0);

    g_sPlayerWatermark[playerid][1] = CreatePlayerTextDraw(playerid, 281.000000, 22.000000, "Police");
    PlayerTextDrawFont(playerid, g_sPlayerWatermark[playerid][1], 3);
    PlayerTextDrawLetterSize(playerid, g_sPlayerWatermark[playerid][1], 0.574999, 1.750000);
    PlayerTextDrawTextSize(playerid, g_sPlayerWatermark[playerid][1], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, g_sPlayerWatermark[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, g_sPlayerWatermark[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, g_sPlayerWatermark[playerid][1], 2);
    PlayerTextDrawColor(playerid, g_sPlayerWatermark[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, g_sPlayerWatermark[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, g_sPlayerWatermark[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, g_sPlayerWatermark[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, g_sPlayerWatermark[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, g_sPlayerWatermark[playerid][1], 0);

    g_sPlayerWatermark[playerid][2] = CreatePlayerTextDraw(playerid, 355.000000, 22.000000, "Pursuit");
    PlayerTextDrawFont(playerid, g_sPlayerWatermark[playerid][2], 3);
    PlayerTextDrawLetterSize(playerid, g_sPlayerWatermark[playerid][2], 0.574999, 1.750000);
    PlayerTextDrawTextSize(playerid, g_sPlayerWatermark[playerid][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, g_sPlayerWatermark[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, g_sPlayerWatermark[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, g_sPlayerWatermark[playerid][2], 2);
    PlayerTextDrawColor(playerid, g_sPlayerWatermark[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, g_sPlayerWatermark[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, g_sPlayerWatermark[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, g_sPlayerWatermark[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, g_sPlayerWatermark[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, g_sPlayerWatermark[playerid][2], 0);
    return 1;
}

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
    ShowServerWatermark(playerid);

    for(new i = 0; i < 3; i++)
    {
        PlayerTextDrawShow(playerid, g_sPlayerWatermark[playerid][i]);
    }    
    return 1;

}