/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#include "azathoth.h"

float speedInhibitor = 1.5;
void playerScript(token* __self) {
	scanKeys();
	// u16 keyDown = KeysDown();
	// u16 keyUp = KeysUp();

	// __self->_vec._speedx += (keyDown >> 7);
	__self->_vec._speedx += 0.05;
}