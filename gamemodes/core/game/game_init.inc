#if defined _inc_game_init
    #undef _inc_game_init
#endif

#if defined _inc_game_init_included
    #endinput
#endif

#define _inc_game_init_included

#include <YSI_Data\y_iterate>
#include <utils\vehicles>

static
    g_sRobbersVehicles,
    g_sPoliceVehiclesA,
    g_sPoliceVehiclesB,
    Iterator:QueuePlayer[MAX_LOBBY]<MAX_PLAYERS>;

Init_Game()
{
    // Need to be in sync before we can use it.
    Iter_Init(QueuePlayer);

    print("Module \"game.inc\"... OK");
    return 1;
}

PutPlayerInQueue(playerid, Lobby:id)
{
    if (NOT_IN_RANGE(_:id, 0, _:MAX_LOBBY) || id == INVALID_LOBBY_ID)
        return 0;

    Iter_Add(QueuePlayer[id], playerid);
    return 1;
}

/*
    I presented to you, the MOST COMPLICATED SHIT I'VE EVER WRITE FOR THIS SHIT
    Big thanks for y_less for giving me the basics of how spreading this works.
*/
SpreadPlayersInLobby(Lobby:id)
{
    if (NOT_IN_RANGE(_:id, 0, _:MAX_LOBBY) || id == INVALID_LOBBY_ID)
        return 0;

    new 
        pid,
        countRobber = Iter_Count(QueuePlayer[id]) / 2;

    while (countRobber--)
    {
        pid = Iter_Random(QueuePlayer[id]);
        
        // Create the vehicle if not have
        if (!IsValidVehicle(g_sRobbersVehicles))
        {
            g_sRobbersVehicles = CreateVehicle(421, 1555.2266, -1627.7550, 13.3828, 90.0, 3, 3, -1);
            SetVehicleVirtualWorld(g_sRobbersVehicles, _:id + GAME_BASE_WORLD_ID);
        }

        SetPlayerInterior(pid, 0);
        SetPlayerVirtualWorld(pid, _:id + GAME_BASE_WORLD_ID);
        PutPlayerInVehicle(pid, g_sRobbersVehicles, GetVehicleNextSeat(g_sRobbersVehicles, 0));

        // We remove the player from queue
        Iter_Remove(QueuePlayer[id], pid);

        // Add it to the robber team
        PutPlayerInRobberTeam(pid);

        // And set the guns
        GivePlayerWeapon(pid, 30, 5000);
        GivePlayerWeapon(pid, 25, 5000);
        GivePlayerWeapon(pid, 24, 5000);
        GivePlayerWeapon(pid, 1, 1);

        printf("The player %d should be in robbers car", pid);
    }

    new leftoverCount;
    foreach (pid : QueuePlayer[id])
    {
        if (!IsValidVehicle(g_sPoliceVehiclesA))
        {
            g_sPoliceVehiclesA = CreateVehicle(596, 1572.8396, -1630.3389, 13.3828, 90.0, -1, -1, -1);
            SetVehicleVirtualWorld(g_sPoliceVehiclesA, _:id + GAME_BASE_WORLD_ID);
        }
        else if (!IsValidVehicle(g_sPoliceVehiclesB) && leftoverCount > 2)
        {
            g_sPoliceVehiclesA = CreateVehicle(596, 1572.7791, -1625.1616, 13.3828, 90.0, -1, -1, -1);
            SetVehicleVirtualWorld(g_sPoliceVehiclesA, _:id + GAME_BASE_WORLD_ID);
        }

        // Set stuff first
        SetPlayerInterior(pid, 0);
        SetPlayerVirtualWorld(pid, _:id + GAME_BASE_WORLD_ID);

         // Create seperate seats.
        new 
            nextSeatA = GetVehicleNextSeat(g_sPoliceVehiclesA, 0);

        /* NOTE:
            This is matter because first when the `leftoverCount` is 0, it's just trying to set the leftover
            to the primary car, after the count already at 3 or more, it would be balanced if the 
            left less than right but if it's equal, then seat A would be filled until full.
            
            Though this algoritm has it's own limitation which only have 2 cars atm.
            I'm too lazy to add more car becuase it's just for fun project and not intended
            for seriousness.
        */
        if (leftoverCount > 2)
        {   
            new
                nextSeatB = GetVehicleNextSeat(g_sPoliceVehiclesB, 0);

            if (nextSeatA > nextSeatB)
            {
                PutPlayerInVehicle(pid, g_sPoliceVehiclesB, nextSeatB);
            }
            else
            {
                PutPlayerInVehicle(pid, g_sPoliceVehiclesA, nextSeatA);
            }
        }
        
        // Finally we can set the rest of them to police team
        PutPlayerInPoliceTeam(pid);
        
        // Set the gun too!
        GivePlayerWeapon(pid, 31, 5000);
        GivePlayerWeapon(pid, 23, 5000);
        GivePlayerWeapon(pid, 3, 1);

        printf("The player %d should in the police car", pid);
        leftoverCount ++;
    }
    Iter_Clear(QueuePlayer[id]);
    CallLocalFunction(#OnGamePreparing, "i", _:id);
    return 1;
}
