/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#include "shoggoth.h"

int id[3] = {0, 16, 64};

void newToken(int tIndex, int stackID, int tx, int ty) {
	token _token = {
		._pos = {
			._x = tx,
			._y = ty
		},

		._firePos = {
			._x = 0,
			._y = 0
		},

		._vec = {
			._speedx = 0,
			._speedy = 0
		},

		._obj = {
			._pointer = 0x07000000 + (8 * (tIndex + id[stackID])),

			._sprite = {
				._index = 0,
				._size = 0,
				._shape = 0
			}
		}
	};

	switch (stackID) {
		case 0 :
			gameStack[tIndex] = _token;
			break;

		case 1 :
			bulletStack[tIndex] = _token;
			break;

		case 2 :
			particalStack[tIndex] = _token;
			break;
	}
}

void t_setSprite(int tIndex, int stackID, int tSIndex, int tSSize, int tSShape) {
	switch (stackID) {
		case 0 :
			gameStack[tIndex]._obj._sprite._index = tSIndex;
			gameStack[tIndex]._obj._sprite._size = tSSize;
			gameStack[tIndex]._obj._sprite._shape = tSShape;
			break;

		case 1 :
			bulletStack[tIndex]._obj._sprite._index = tSIndex;
			bulletStack[tIndex]._obj._sprite._size = tSSize;
			bulletStack[tIndex]._obj._sprite._shape = tSShape;
			break;

		case 2 :
			particalStack[tIndex]._obj._sprite._index = tSIndex;
			particalStack[tIndex]._obj._sprite._size = tSSize;
			particalStack[tIndex]._obj._sprite._shape = tSShape;
			break;
	}
}

void t_addScript(int tIndex, int stackID, void (*tScript)) {
	switch (stackID) {
		case 0 :
			gameStack[tIndex]._script = tScript;
			break;

		case 1 :
			bulletStack[tIndex]._script = tScript;
			break;

		case 2 :
			particalStack[tIndex]._script = tScript;
			break;
	}
}

void setMapPoint(int _x, int _y, int tIndex, int memBlock) {
	unsigned short* ap = (unsigned short*) 0x06000000;
	ap = ap + (0x400 * memBlock);
	int _n = (_y * 32) + _x;
	ap[_n] = tIndex;
	ap = NULL;
	free(ap);
}

// legacy, needs rerighting
void setMapBox(int _x, int _y, int _width, int _height, int tIndex, int memBlock) {
	int nx, ny;
	for (nx = 0; nx < _width; nx++) {
		for (ny = 0; ny < _height; ny++) {
			setMapPoint(_x + nx, _y + ny, tIndex, memBlock);
		}
	}
}

void setMapPoint_L(int _x, int _y, tileProfile* _tile, int memBlock) {
	unsigned short* ap = (unsigned short*) 0x06000000;
	ap = ap + (0x400 * memBlock);
	int nx, ny;
	for (ny = 0; ny < _tile->_height; ny++) {
		for (nx = 0; nx <_tile->_width; nx++) {
			int _n = ((_y + ny) * 32) + (_x + nx);
			ap[_n] = ((_tile->_y + ny) * 32) + (_tile->_x + nx);
		}
	}
	ap = NULL;
	free(ap);
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
			_hand[0] = ((slashRound(gameStack[n]._pos._y) << 0) |
				(gameStack[n]._obj._sprite._shape << 14));
			_hand[1] = ((slashRound(gameStack[n]._pos._x) << 0) |
				(gameStack[n]._obj._sprite._size << 14));
			_hand[2] = ((gameStack[n]._obj._sprite._index << 0));
		}
	}

	for (n = 0; n < 48; n++) {
		bulletStack[n]._pos._x += bulletStack[n]._vec._speedx;
		bulletStack[n]._pos._y += bulletStack[n]._vec._speedy;

		if (bulletStack[n]._script != NULL) {
			bulletStack[n]._script(&bulletStack[n]); // exicute obj script
		}

		// right changes to obj into memmory
		if (bulletStack[n]._obj._pointer != 0) {
			_hand = (unsigned char*) bulletStack[n]._obj._pointer;
			_hand[0] = ((slashRound(bulletStack[n]._pos._y) << 0) |
				(bulletStack[n]._obj._sprite._shape << 14));
			_hand[1] = ((slashRound(bulletStack[n]._pos._x) << 0) |
				(bulletStack[n]._obj._sprite._size << 14));
			_hand[2] = ((bulletStack[n]._obj._sprite._index << 0));
		}
	}

	for (n = 0; n < 64; n++) {
		particalStack[n]._pos._x += particalStack[n]._vec._speedx;
		particalStack[n]._pos._y += particalStack[n]._vec._speedy;

		if (particalStack[n]._script != NULL) {
			particalStack[n]._script(&particalStack[n]); // exicute obj script
		}

		// right changes to obj into memmory
		if (particalStack[n]._obj._pointer != 0) {
			_hand = (unsigned char*) particalStack[n]._obj._pointer;
			_hand[0] = ((slashRound(particalStack[n]._pos._y) << 0) |
				(particalStack[n]._obj._sprite._shape << 14));
			_hand[1] = ((slashRound(particalStack[n]._pos._x) << 0) |
				(particalStack[n]._obj._sprite._size << 14));
			_hand[2] = ((particalStack[n]._obj._sprite._index << 0));
		}
	}
	_hand = NULL;
	free(_hand);
}
