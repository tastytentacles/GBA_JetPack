/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#ifndef _DAGON_
#define _DAGON_

#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include "shoggoth.h"
#include "azathoth.h"

void invoke(); // sets up palettes and I/O flags
void game_init(); // draws background to memory
void game_logic(); // called every logic tick and handles game logic

float bg_speed[3];
float bg_pos[3];
void bgScroll(); // handles background parallax effect
void titleScript(); // handles title screen logic
#endif