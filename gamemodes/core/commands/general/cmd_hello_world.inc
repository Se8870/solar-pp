
YCMD:hello_world(playerid, string:args[], help)
{
    if (help)
    {
        SendClientMessage(playerid, 0xFFFFFFAA, "Hello World, nothing else");
        return 1;
    }

    SendClientMessage(playerid, 0xFFFFFFAA, "Hello World!");
    return 1;
}