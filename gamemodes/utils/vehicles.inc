/*
    Lite version of EVF.inc
*/
#if defined _inc_vehicle
    #undef _inc_vehicle
#endif

#if defined _INC_spp_module_vehicle_utils
    #endinput
#endif

#define _INC_spp_module_vehicle_utils

#include <YSI_Data\y_foreach>

//          Name                Value
#define     INVALID_SEAT_ID     0xFFF

#define GetVehicleSeats(%0) GetVehicleModelSeats(GetVehicleModel(%0))
stock GetVehicleModelSeats(modelid)
{
    static const s_VehicleSeats[] =
	{
		4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2, 1, 4, 4, 4, 2,
		1, 7, 1, 2, 2, 0, 2, 7, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 0, 0, 2, 1, 1, 1, 2, 2, 2, 4,
		4, 2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2, 2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2,
		2, 4, 2, 4, 1, 2, 2, 2, 4, 4, 2, 2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2,
		1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 7, 7, 1, 4, 2, 2, 2, 2, 2, 4, 4,
		2, 2, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2,
		4, 4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 7, 2, 2, 1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 2, 0, 0, 0,
		4, 0, 0
	};
	return (modelid < 400 || modelid > 611) ? (0) : (s_VehicleSeats[(modelid - 400)]);
}

stock IsVehicleSeatOccupied(vehicleid, seatid)
{
    if (!IsValidVehicle(vehicleid))
        return 0;
    
    foreach (new i : Player)
    {
        if (IsPlayerInVehicle(i, vehicleid) && GetPlayerVehicleSeat(i) == seatid)
            return 1;
    }
    return 0;
}

stock GetVehicleNextSeat(vehicleid, passenger = 1)
{
    new seats = GetVehicleSeats(vehicleid);

    if (!seats)
        return INVALID_SEAT_ID;

    for (new i = passenger; i < seats; i ++)
    {
        if (!IsVehicleSeatOccupied(vehicleid, i))
            return i;
    }
    return INVALID_SEAT_ID;
}
