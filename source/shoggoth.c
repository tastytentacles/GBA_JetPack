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
		case 0 : gameStack[tIndex] = _token; break;
		case 1 : bulletStack[tIndex] = _token; break;
		case 2 : particalStack[tIndex] = _token; break;
	}
}

void t_setSprite(int tIndex, int stackID, int tSIndex, int tSSize, int tSShape) {
	token* _hand;
	switch (stackID) {
		case 0 : _hand = &gameStack[tIndex]; break;
		case 1 : _hand = &bulletStack[tIndex]; break;
		case 2 : _hand = &particalStack[tIndex]; break;
		default : _hand = NULL; break;
	}

	_hand->_obj._sprite._index = tSIndex;
	_hand->_obj._sprite._size = tSSize;
	_hand->_obj._sprite._shape = tSShape;
}

void t_addScript(int tIndex, int stackID, void (*tScript)) {
	token* _hand;
	switch (stackID) {
		case 0 : _hand = &gameStack[tIndex]; break;
		case 1 : _hand = &bulletStack[tIndex]; break;
		case 2 : _hand = &particalStack[tIndex]; break;
		default : _hand = NULL; break;
	}

	_hand->_script = tScript;
}

void setMapPoint(int _x, int _y, int tIndex, int palette, int memBlock) {
	unsigned short* ap = (unsigned short*) 0x06000000;
	ap = ap + (0x400 * memBlock);
	int _n = (_y * 32) + _x;
	ap[_n] = ((tIndex << 0) | (palette << 12));
	ap = NULL;
	free(ap);
}

// legacy, needs rerighting
void setMapBox(int _x, int _y, int _width, int _height, int tIndex, int palette, int memBlock) {
	int nx, ny;
	for (nx = 0; nx < _width; nx++) {
		for (ny = 0; ny < _height; ny++) {
			setMapPoint(_x + nx, _y + ny, tIndex, palette, memBlock);
		}
	}
}

void setMapPoint_L(int _x, int _y, tileProfile* _tile, int palette, int memBlock) {
	unsigned short* ap = (unsigned short*) 0x06000000;
	ap = ap + (0x400 * memBlock);
	int nx, ny;
	for (ny = 0; ny < _tile->_height; ny++) {
		for (nx = 0; nx <_tile->_width; nx++) {
			int _n = ((_y + ny) * 32) + (_x + nx);
			unsigned int index = ((_tile->_y + ny) * 32) + (_tile->_x + nx);
			ap[_n] = ((index << 0) | (palette << 12));
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
	int _swapStackLen[] = {16, 48, 64};
	token* _swapStack[] = {gameStack, bulletStack, particalStack};

	int n, i;
	for (i = 0; i < 3; i++) {
		for (n = 0; n < _swapStackLen[i]; n++) {
			_swapStack[i][n]._pos._x += _swapStack[i][n]._vec._speedx;
			_swapStack[i][n]._pos._y += _swapStack[i][n]._vec._speedy;

			if (_swapStack[i][n]._script != NULL) {
				_swapStack[i][n]._script(&_swapStack[i][n]); // exicute obj script
			}

			// right changes to obj into memmory
			if (_swapStack[i][n]._obj._pointer != 0) {
				_hand = (unsigned char*) _swapStack[i][n]._obj._pointer;
				_hand[0] = ((slashRound(_swapStack[i][n]._pos._y) << 0) |
					(_swapStack[i][n]._obj._sprite._shape << 14));
				_hand[1] = ((slashRound(_swapStack[i][n]._pos._x) << 0) |
					(_swapStack[i][n]._obj._sprite._size << 14));
				_hand[2] = ((_swapStack[i][n]._obj._sprite._index << 0));
			}
		}
	}
	_hand = NULL;
	free(_hand);
}
