/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

// #include <gba_input.h>
#include "azathoth.h"

float speedInhibitor = 1.5;
float shipSpeed = 0.25;
float shipFriction = 0.85;

bool dpad_up = false;
bool dpad_down = false;
bool dpad_left = false;
bool dpad_right = false;
void playerScript(token* __self) {
	scanKeys();
	u16 keyDown = keysDown();
	u16 keyUp = keysUp();
	// u16 keyHeld = keysHeld();

	if (keyDown & KEY_RIGHT)
		{ dpad_right = true; }
	if (keyDown & KEY_LEFT)
		{ dpad_left = true; }
	if (keyDown & KEY_UP)
		{ dpad_up = true; }
	if (keyDown & KEY_DOWN)
		{ dpad_down = true; }

	if (keyUp & KEY_RIGHT)
		{ dpad_right = false; }
	if (keyUp & KEY_LEFT)
		{ dpad_left = false; }
	if (keyUp & KEY_UP)
		{ dpad_up = false; }
	if (keyUp & KEY_DOWN)
		{ dpad_down = false; }

	if (keyDown & KEY_A) {
		addMissile(__self->_pos._x, __self->_pos._y);
	}

	__self->_vec._speedy += (dpad_down - dpad_up) * shipSpeed;
	__self->_vec._speedx += (dpad_right - dpad_left) * shipSpeed;

	if (__self->_vec._speedx > 0.01 ||
		__self->_vec._speedx < -0.01) {
		__self->_vec._speedx *= shipFriction;
	}
	else {
		__self->_vec._speedx = 0;
	}

	if (__self->_vec._speedy > 0.01 ||
		__self->_vec._speedy < -0.01) {
		__self->_vec._speedy *= shipFriction;
	}
	else {
		__self->_vec._speedy = 0;
	}
}

void missileScript(token* __self) {
	if (__self->_pos._x > 240) {
		__self->_state = 1;
	}
}

void smokeScript(token* __self) {

}