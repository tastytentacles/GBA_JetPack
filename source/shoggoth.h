/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#ifndef _SHOGGOTH_
#define _SHOGGOTH_

#include <gba_input.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct token token;

typedef struct point2D
{
	float			_x;
	float			_y;
} point2D;

typedef struct bbox
{
	int				_x;
	int				_y;
	int				_width;
	int				_height;
} bbox;

typedef struct simpleVec2D
{
	float			_speedx;
	float			_speedy;	
} simpleVec2D;

typedef struct tileProfile
{
	int				_x;
	int				_y;
	int				_width;
	int				_height;
} tileProfile;

typedef struct spriteHandle
{
	int				_index;
	int				_size;
	int				_shape;
	point2D			_offset;
} spriteHandle;

// animated sprite handle

typedef struct objHandle
{
	int				_pointer;
	
	// bool			_animated;
	spriteHandle	_sprite;
	// animated sprite handle
} objHandle;

/*
	------ state key ------
		0	=	null
		1	=	dead
		2	=	alive
*/
struct token {
	point2D			_pos;
	point2D			_firePos;
	simpleVec2D		_vec;
	bbox			_bbox;
	objHandle		_obj;


	char			_state;
	uint 			_tick;
	void			(*_script)(token *);
};

uint playerScore;
uint playerLife;

/*
	------ game state key ------
		0	=	tital screen
		1	=	tital screen -> game screen
		2	=	game screen
		3	=	player dies -> dead player screen
		4	=	player dead
*/
uint gameState;

int id[3];

token gameStack[16];
token bulletStack[48];
token particalStack[64];

uint sortToken(int stackID);
uint slashRound(float q);

void newToken(int tIndex, int stackID, int tx, int ty);
uint sortAddToken(int stackID, int _x, int _y);
void killToken(int tIndex, int stackID);
void t_setSprite(int tIndex, int stackID, int tSIndex, int tSSize, int tSShape);
void t_addScript(int tIndex, int stackID, void (*tScript));
void t_setSpriteOffset(uint tIndex, uint stackID, int _x, int _y);
void t_setBbox(uint tIndex, uint stackID, uint _x, uint _y, uint _width, uint _height);
void t_setFirePoint(uint tIndex, uint stackID, int _x, int _y);
void setMapPoint(int _x, int _y, int tIndex, int palette, int memBlock);
void setMapPoint_L(int _x, int _y, tileProfile* _tile, int palette, int memBlock);
void setMapBox(int _x, int _y, int _width, int _height, int tIndex, int palette, int memBlock);
void drawNumber(int _x, int _y, uint _numb, int _displayLen, int memBlock);

void addPlayer();
void addMissile(int _x, int _y);
void addSmoke(int _x, int _y);
void addMOB();
void addEBall();


void callTokenStack();
#endif