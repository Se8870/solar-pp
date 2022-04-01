/*
	Solarize Police Pursuits v0.0.1
	Created by: Kirima2nd aka Se8870

	About:
		This solar-pp just for april fools joke, not intended to be fully fledged pursuits
		It have basics pp that you can use, i cannot guaranteed would be work 100% but yea
		This has been nice project for me, because of me keeping resetting this shit when
		imo the structure seems shit, but here we are!

	Features:
		- No login/Register
		- No saving system
		- Great lobby system
		- Basic Police Pursuits
		- Follows UNIX Philisophy that says 
			"Make each program do one thing well".
			"To do a new job, build afresh rather than complicate old programs by adding new 'features'."

	Contributors:
		- Kirima2nd
		- Abielfrl
*/

#include <a_samp>

// RESERVED FOR TEH GREATEST ANTI CHEAT start

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

#include <YSI_Visual\y_dialog>
#include <streamer>
#include <nex-ac>

// RESERVED FOR TEH GREATEST ANTI CHEAT end

#include <init>

main() 
{
	printf("Solarize Police Pursuits");
	printf("Made by: Kirima2nd");
	return 1;
}
