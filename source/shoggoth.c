/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#include "shoggoth.h"

void newToken(int tIndex, int tx, int ty) {
	token _token = {
		._pos = {
			._x = tx,
			._y = ty
		},

		._vec = {
			._speedx = 0,
			._speedy = 0
		},

		._obj = {
			._pointer = 0x07000000 + (8 * tIndex),

			._sprite = {
				._index = 0,
				._size = 0,
				._shape = 1
			}
		}
	};

	gameStack[tIndex] = _token;
}

void t_addScript(int tIndex, void (*tScript)) {
	gameStack[tIndex]._script = tScript;
}

// temp
unsigned int slashRound(float q) {
	float p1 = (q - (unsigned int) q);
	unsigned int a;
	if (p1 < 0.5) { a = q; }
	else {a = q + 1; }
	return a;
}
// temp

void callTokenStack() {
	unsigned short* _hand;
	int n;
	for (n = 0; n < 16; n++) {
		gameStack[n]._pos._x += gameStack[n]._vec._speedx;
		gameStack[n]._pos._y += gameStack[n]._vec._speedy;

		if (gameStack[n]._script != NULL) {
			gameStack[n]._script(&gameStack[n]); // exicute obj script
		}

		// right changes to obj into memmory
		if (gameStack[n]._obj._pointer != 0) {
			_hand = (unsigned char*) gameStack[n]._obj._pointer;
			_hand[0] = ((slashRound(gameStack[n]._pos._y) << 0) | (gameStack[n]._obj._sprite._shape << 14));
			_hand[1] = ((slashRound(gameStack[n]._pos._x) << 0) | (gameStack[n]._obj._sprite._size << 14));
			_hand[2] = ((gameStack[n]._obj._sprite._index << 0));
		}
	}
}
