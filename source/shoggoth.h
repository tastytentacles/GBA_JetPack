/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#ifndef _SHOGGOTH_
#define _SHOGGOTH_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point2D point2D;
typedef struct simpleVec2D simpleVec2D;
typedef struct tileProfile tileProfile;
typedef struct objHandle objHandle;
typedef struct spriteHandle spriteHandle;
// animated sprite handle
typedef struct token token;

struct point2D
{
	float			_x;
	float			_y;
};

struct simpleVec2D
{
	float			_speedx;
	float			_speedy;	
};

struct tileProfile
{
	int				_x;
	int				_y;
	int				_width;
	int				_height;
};

struct spriteHandle
{
	int				_index;
	int				_size;
	int				_shape;
};

// animated sprite handle

struct objHandle
{
	int				_pointer;
	
	// bool			_animated;
	spriteHandle	_sprite;
	// animated sprite handle
};

struct token {
	point2D			_pos;
	simpleVec2D		_vec;
	objHandle		_obj;
	void			(*_script)(token *);
};

token gameStack[16];
void newToken();
void t_setSprite(int tIndex, int tSIndex, int tSSize, int tSShape);
void t_addScript(int tIndex, void (*tScript));
void setMapPoint(int _x, int _y, int tIndex, int memBlock);
void setMapPoint_L(int _x, int _y, tileProfile* _tile, int memBlock);
void setMapBox(int _x, int _y, int _width, int _height, int tIndex, int memBlock);
unsigned int slashRound(float q);
void callTokenStack();
#endif