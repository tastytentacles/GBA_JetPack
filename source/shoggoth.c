/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#include "shoggoth.h"

uint playerScore = 0;
uint playerLife = 10;
uint gameState = 0;
uint mobCount = 0;

int id[3] = {0, 16, 64};
int _swapStackLen[] = {16, 48, 64};
token* _swapStack[] = {gameStack, bulletStack, particalStack};

uint sortToken(int stackID) {
	int n;
	int _out = 0;
	for (n = 0; n < _swapStackLen[stackID]; n++) {
		if (_swapStack[stackID][n]._state == 0) {
			_out = n;
			break;
		}
		_out = _swapStackLen[stackID];
	}
	return _out;
}

unsigned int slashRound(float q) {
	float p1 = (q - (unsigned int) q);
	unsigned int a;
	if (p1 < 0.5) { a = q; }
	else {a = q + 1; }
	return a;
}

void newToken(int tIndex, int stackID, int tx, int ty) {
	token _token = {
		._state = 2,

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
				._shape = 0,
				._offset = {
					._x = 0,
					._y = 0
				}
			}
		}
	};

	switch (stackID) {
		case 0 : gameStack[tIndex] = _token; break;
		case 1 : bulletStack[tIndex] = _token; break;
		case 2 : particalStack[tIndex] = _token; break;
	}
}

uint sortAddToken(int stackID, int _x, int _y) {
	uint tStackID = sortToken(stackID);
	newToken(tStackID, stackID, _x, _y);
	return tStackID;
}

void killToken(int tIndex, int stackID) {
	ushort* cleanPointer = (ushort*) _swapStack[stackID][tIndex]._obj._pointer;
	cleanPointer[0] = 0;
	cleanPointer[1] = 0;
	cleanPointer[2] = 0;
	token _blankToken = {};
	_swapStack[stackID][tIndex] = _blankToken;
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

void t_setSpriteOffset(uint tIndex, uint stackID, int _x, int _y) {
	_swapStack[stackID][tIndex]._obj._sprite._offset._x = _x;
	_swapStack[stackID][tIndex]._obj._sprite._offset._y = _y;
}

void t_setBbox(uint tIndex, uint stackID, uint _x, uint _y, uint _width, uint _height){
	_swapStack[stackID][tIndex]._bbox._x = _x;
	_swapStack[stackID][tIndex]._bbox._y = _y;
	_swapStack[stackID][tIndex]._bbox._width = _width;
	_swapStack[stackID][tIndex]._bbox._height = _height;
}

void t_setFirePoint(uint tIndex, uint stackID, int _x, int _y) {
	_swapStack[stackID][tIndex]._firePos._x = _x;
	_swapStack[stackID][tIndex]._firePos._y = _y;
}

void setMapPoint(int _x, int _y, int tIndex, int palette, int memBlock) {
	unsigned short* ap = (unsigned short*) 0x06000000;
	ap = ap + (0x400 * memBlock);
	int _n = (_y * 32) + _x;
	ap[_n] = ((tIndex << 0) | (palette << 12));
	ap = NULL;
	free(ap);
}

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

void drawNumber(int _x, int _y, uint _numb, int _displayLen, int memBlock){
	int n;
	uint _readhead = 0;
	for (n = 0; n < _displayLen; n++) {
		uint _box = _numb / (_readhead ^ 10);
		setMapPoint(_x + n, _y, 9 + _box, 1, memBlock);
		_readhead += 1;
	}
}

bool checkHitBox(uint _x, uint _y, uint _width, uint _height) {
	bool _out = false;
	int n;
	for (n = 0; n < 48; n++) {
		if (_swapStack[1][n]._state == 2) {
			if (_swapStack[1][n]._pos._x > _x &&
				_swapStack[1][n]._pos._x < _x + _width &&
				_swapStack[1][n]._pos._y > _y &&
				_swapStack[1][n]._pos._y < _y + _height) {
				_out = true;
				_swapStack[1][n]._state = 1;
				break;
			}
		}
	}
	return _out;
}



extern void playerScript(token* __self);
void addPlayer() {
	if (_swapStack[0][0]._state == 0) {
		newToken(0, 0, 240, 80);
		t_setSprite(0, 0, 1, 0, 1);
		t_addScript(0, 0, playerScript);
		t_setBbox(0, 0, 0, 2, 16, 4);
		t_setFirePoint(0, 0, 16, 4);
	}
}

extern void missileScript(token* __self);
void addMissile(int _x, int _y) {
	uint tID = sortAddToken(1, _x, _y);
	t_setSprite(tID, 1, 32, 0, 0);
	t_addScript(tID, 1, missileScript);
	bulletStack[tID]._vec._speedx = 2;
	t_setSpriteOffset(tID, 1, 0, 4);
}

extern void smokeScript(token* __self);
void addSmoke(int _x, int _y) {
	uint tID = sortAddToken(2, _x, _y);
	t_setSprite(tID, 2, 32, 0, 0);
	t_addScript(tID, 2, smokeScript);
	t_setSpriteOffset(tID, 2, 4, 4);
}

extern void mobScript(token* __self);
void addMOB() {
	unsigned char* timeSpace = (unsigned char*) 0x4000100;
	srand(timeSpace[0]);
	uint tID = sortAddToken(0, 240, (rand() % 100) + 20);
	t_setFirePoint(tID, 0, -8, 0);
	t_setSprite(tID, 0, 4, 1, 0);
	t_setSpriteOffset(tID, 0, 8, 8);
	t_addScript(tID, 0, mobScript);
}

extern void eBallScript(token* __self);
void addEBall(uint _x, uint _y) {
	uint tID = sortAddToken(1, _x, _y);
	// t_setSprite(tID, 1, 100, 0, 0);
	t_addScript(tID, 1, eBallScript);
	bulletStack[tID]._vec._speedx = -1.45;
	t_setSpriteOffset(tID, 1, 4, 4);
}


void callTokenStack() {
	unsigned short* _hand;
	int n, i;
	for (i = 0; i < 3; i++) {
		for (n = 0; n < _swapStackLen[i]; n++) {
			if (_swapStack[i][n]._state == 1)
				{ killToken(n, i); }

			_swapStack[i][n]._pos._x += _swapStack[i][n]._vec._speedx;
			_swapStack[i][n]._pos._y += _swapStack[i][n]._vec._speedy;

			if (_swapStack[i][n]._script != NULL) {
				_swapStack[i][n]._script(&_swapStack[i][n]); // exicute obj script
			}

			// right changes to obj into memmory
			if (_swapStack[i][n]._obj._pointer != 0) {
				_hand = (unsigned short*) _swapStack[i][n]._obj._pointer;
				_hand[0] = ((slashRound(_swapStack[i][n]._pos._y -
					_swapStack[i][n]._obj._sprite._offset._y) << 0) |
					(_swapStack[i][n]._obj._sprite._shape << 14));
				_hand[1] = ((slashRound(_swapStack[i][n]._pos._x -
					_swapStack[i][n]._obj._sprite._offset._x) << 0) |
					(_swapStack[i][n]._obj._sprite._size << 14));
				_hand[2] = ((_swapStack[i][n]._obj._sprite._index << 0) | (1 << 10));
			}
		}
	}
	_hand = NULL;
	free(_hand);
}