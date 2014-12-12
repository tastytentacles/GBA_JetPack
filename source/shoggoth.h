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

// structures for obj handling
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

typedef struct objHandle
{
	int				_pointer;	
	spriteHandle	_sprite;
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
	uint 			_tick2;
	bool			_swich;
	bool			_swich2;
	void			(*_script)(token *);
};
// structures for obj handling

uint playerScore;
uint bestScore;
// uint playerLife;
uint mobCount;

/*
	------ game state key ------
		0	=	title screen
		1	=	title screen -> game screen
		2	=	game screen
		3	=	player dies -> dead player screen
		4	=	player dead
*/
uint gameState;

int id[3]; // int for object sorting system

token gameStack[16]; // stack of active entitys in game 
token bulletStack[48]; // stack of bullets in game
token particalStack[64]; // stack of particulars in game

uint sortToken(int stackID);
/*
	function gets first empty token slot in stack selected by ID,
	if no slot is available it returns the length of the stack.
*/
uint slashRound(float q);
/*
	sloppy round function to get around strange rounding error when shifting bits
*/

void newToken(int tIndex, int stackID, int tx, int ty);
/*
	adds token at index in stack, also at set x and y position
*/
uint sortAddToken(int stackID, int _x, int _y);
/*
	adds token in first available slot in stack and at set x and y
*/
void killToken(int tIndex, int stackID);
/*
	removes and blanks obj memory for token at index on stack
*/
void t_setSprite(int tIndex, int stackID, int tSIndex, int tSSize, int tSShape);
/*
	set the sprite index, size and shape of an obj at index in stack
*/
void t_addScript(int tIndex, int stackID, void (*tScript));
/*
	adds script to an obj at index in stack
*/
void t_setSpriteOffset(uint tIndex, uint stackID, int _x, int _y);
/*
	sets sprite offset by set x and y of obj of index in stack
*/
void t_setBbox(uint tIndex, uint stackID, uint _x, uint _y, uint _width, uint _height);
/*
	set bounding box of index in stack, bounding boxes are not properly worked into engine and are only used for screen limiters
*/
void t_setFirePoint(uint tIndex, uint stackID, int _x, int _y);
/*
	set point at which bullets will be fired from
*/
void setMapPoint(int _x, int _y, int tIndex, int palette, int memBlock);
/*
	set a single tile at x and y of memory block
*/
void setMapPoint_L(int _x, int _y, tileProfile* _tile, int palette, int memBlock);
/*
	draw a sprite that is larger then 1 tile to a memory block

	uses a custom structure called tileprofile that contains the x and y concordances of
	the sprite in memory and with width and hight of the sprite
*/
void setMapBox(int _x, int _y, int _width, int _height, int tIndex, int palette, int memBlock);
/*
	set a block of tiles to one tile
*/
void drawNumber(int _x, int _y, uint _numb, int _displayLen, int memBlock);
/*
	draw a number to a memory block
*/

bool checkHitBox(uint _x, uint _y, uint _width, uint _height);
/*
	check of anything in the bullet stack is inside the stated box

	note: used as solution to compensate for lacking engine wide hit boxes
*/

void addPlayer();					// pre-made function for adding players
void addMissile(int _x, int _y);	// pre-made function for adding missiles
void addSmoke(int _x, int _y);		// pre-made function for adding smoke practicals
void addMOB();						// pre-made function for adding MOBs
void addEBall(uint _x, uint _y);	// pre-made function for adding energy balls


void callTokenStack();
/*
	called once every logic tick and sorts all stacks and handles physics and obj logic
*/
#endif