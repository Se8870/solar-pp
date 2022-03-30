
#if defined _inc_game_init
    #undef _inc_game_init
#endif

#if defined _inc_game_init_included
    #endinput
#endif

#define _inc_game_init_included

#include <YSI_Data\y_foreach>
#include <utils\vehicles>

static
    g_sRobbersVehicle,
    g_sPoliceVehicles[2 char];

static
     Iterator:QueuePlayer[MAX_LOBBY]<MAX_PLAYERS>;

Init_Game()
{
    Iter_Init(QueuePlayer);
    print("Module \"game.inc\"... OK");
    return 1;
}

PrepareGameForLobbyId(Lobby:id)
{
    foreach (new pid : GroupMember(GetLobbyGroupId(id)))
    {
        Iter_Add(QueuePlayer[id], pid);
        SetPlayerInGame(pid, true);
    }
}

// Poorly written algoritm, many thanks to Y_less to give much idea.
SpreadPlayers(Lobby:id) // ID = lobbyid
{
    new 
        count = (Iter_Count(QueuePlayer[id])) / GAME_MIN_REQUIRED_PLAYERS;

    // Declare pid for later use
    new pid;

    while (count--)
    {
        pid = Iter_Random(QueuePlayer[id]);

        if (!IsValidVehicle(g_sRobbersVehicle)) 
        {
            g_sRobbersVehicle = CreateVehicle(421, 1555.2266, -1627.7550, 13.3828, 90.0, 3, 3, -1);
        }

        PutPlayerInVehicle(pid, g_sRobbersVehicle, GetVehicleNextSeat(g_sRobbersVehicle, 0));
        GivePlayerWeapon(pid, 24, 10000);

        PutPlayerInRobberTeam(pid);

        Iter_Remove(QueuePlayer[id], pid);
    }

    // Initialize our police vehicle before going to put them
    // It's required to avoid much fucking pain
    g_sPoliceVehicles{0} = CreateVehicle(490, 1572.7791, -1625.1616, 13.3828, 90.0, -1, -1, -1);

    // Always check if the count more than 2 leftovers.
    if (Iter_Count(QueuePlayer[id]) > 2)
    {
        g_sPoliceVehicles{1} = CreateVehicle(490, 1572.7791, -1625.1616, 13.3828, 90.0, -1, -1, -1);
    }

    foreach (pid : QueuePlayer[id])
    {
        // Create seperate seats.
        new 
            nextSeatA = GetVehicleNextSeat(g_sPoliceVehicles{0}, 0);

        /* NOTE:
            This is matter because first when the `count` is 0, it's just trying to set the leftover
            to the primary car, after the count already at 3 or more, it would be balanced if the 
            left less than right but if it's equal, then seat A would be filled until full.
            
            Though this algoritm has it's own limitation which only have 2 cars atm.
            I'm too lazy to add more car becuase it's just for fun project and not intended
            for seriousness.
        */
        if (count > 2)
        {   
            new
                nextSeatB = GetVehicleNextSeat(g_sPoliceVehicles{1}, 0);

            if (nextSeatA > nextSeatB)
            {
                PutPlayerInVehicle(pid, g_sPoliceVehicles{1}, nextSeatB);
                continue; // We skip after set the vehicle to generate next person.
            }
        }
        PutPlayerInVehicle(pid, g_sPoliceVehicles{0}, nextSeatA);
        PutPlayerInPoliceTeam(pid);

        GivePlayerWeapon(pid, 24, 10000);
        count ++;
    }
    Iter_Clear(QueuePlayer[id]);
    return 1;
}
