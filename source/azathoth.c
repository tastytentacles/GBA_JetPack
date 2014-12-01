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
float shipFriction = 0.95;

bool dpad_up = false;
bool dpad_down = false;
bool dpad_left = false;
bool dpad_right = false;
void playerScript(token* __self) {
	scanKeys();
	u16 keyDown = keysDown();
	u16 keyUp = keysUp();


	switch (keyDown) {
		case KEY_UP :
			dpad_up = true;
			break;

		case KEY_DOWN :
			dpad_down = true;
			break;
	}

	switch (keyDown) {
		case KEY_LEFT :
			dpad_left = true;
			break;

		case KEY_RIGHT :
			dpad_right = true;
			break;
	}

	switch (keyUp) {
		case KEY_UP :
			dpad_up = false;
			break;

		case KEY_DOWN :
			dpad_down = false;
			break;
	}

	switch (keyUp) {
		case KEY_LEFT :
			dpad_left = false;
			break;

		case KEY_RIGHT :
			dpad_right = false;
			break;
	}


	__self->_vec._speedy += (dpad_down - dpad_up) * shipSpeed;
	__self->_vec._speedx += (dpad_right - dpad_left) * shipSpeed;


	if (__self->_vec._speedx > 0.01 || __self->_vec._speedx < -0.01) {
		__self->_vec._speedx *= shipFriction;
	}
	else {
		__self->_vec._speedx = 0;
	}

	if (__self->_vec._speedy > 0.01 || __self->_vec._speedy < -0.01) {
		__self->_vec._speedy *= shipFriction;
	}
	else {
		__self->_vec._speedy = 0;
	}
}