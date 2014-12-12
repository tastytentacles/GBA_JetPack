/*	   ____                            ___           _ _ _ _               
	  / __ \  /\/\   __ _ _ __ __ _   /   \_____   _(_) | (_) ___ _ __ ___ 
	 / / _` |/    \ / _` | '__/ _` | / /\ / _ \ \ / / | | | |/ _ \ '__/ __|
	| | (_| / /\/\ \ (_| | | | (_| |/ /_//  __/\ V /| | | | |  __/ |  \__ \
	 \ \__,_\/    \/\__,_|_|  \__, /___,' \___| \_/ |_|_|_|_|\___|_|  |___/
	  \____/                     |_|                                       
*/

#include "dagon.h"

void invoke() {
	// establish relevlent io and bg memmory
	ushort* cp1 = (ushort*) 0x4000000;	// i/o part 1
	ushort* cp2 = (ushort*) 0x4000004;	// i/o part 2
	ushort* bgc0 = (ushort*) 0x4000008;	// bg controll part 1
	ushort* bgc1 = (ushort*) 0x400000A;	// bg controll part 2
	ushort* bgc2 = (ushort*) 0x400000C;	// bg controll part 3
	ushort* bgc3 = (ushort*) 0x400000E;	// bg controll part 4
	ushort* tc = (ushort*) 0x4000102;	// timer controll
	cp1[0] = ((1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12));
	cp2[0] = ((1 << 3));
	bgc0[0] = ((10 << 8));
	bgc1[0] = ((2 << 0) | (11 << 8));
	bgc2[0] = ((2 << 0) | (12 << 8));
	bgc3[0] = ((2 << 0) | (13 << 8));
	tc[0] = ((1 << 7));

	cp1 = cp2 = NULL;
	free(cp1);
	free(cp2);
	bgc0 = bgc1 = bgc2 = NULL;
	free(bgc0);
	free(bgc1);
	free(bgc2);

	// establish palet
	unsigned short* pp = (unsigned short*) 0x5000000;	// tile memmory palet block
	unsigned short* spp = (unsigned short*) 0x5000200;	// obj tile memmory palet block

	// palatte 1
	spp[1] = pp[1] = RGB5(8, 8, 8);			// gray
	spp[2] = pp[2] = RGB5(15, 15, 31);		// blue 1
	spp[3] = pp[3] = RGB5(10, 10, 31);		// blue 2
	spp[4] = pp[4] = RGB5(5, 5, 31);		// blue 3
	spp[5] = pp[5] = RGB5(20, 31, 20);		// green 1
	spp[6] = pp[6] = RGB5(10, 31, 10);		// green 2
	spp[7] = pp[7] = RGB5(0, 31, 0);		// green 3
	spp[8] = RGB5(28, 14, 0);				// orange 1
	spp[9] = RGB5(24, 10, 0);				// orange 2
	spp[10] = RGB5(20, 6, 0);				// orange 3
	spp[11] = RGB5(28, 28, 28);				// white 1
	spp[12] = RGB5(20, 20, 20);				// white 2
	spp[13] = RGB5(10, 10, 10);				// white 3
	spp[14] = pp[14] = RGB5(31, 0, 0);		// red 1
	spp[15] = pp[15] = RGB5(16, 0, 0);		// red 2

	pp[8] = RGB5(25, 25, 31);				// sky blue 1
	pp[9] = RGB5(20, 20, 31);				// sky blue 2
	pp[10] = RGB5(15, 15, 31);				// sky blue 3
	pp[11] = RGB5(10, 10, 31);				// sky blue 4

	pp = (unsigned short*) 0x5000020;		// palette 2 pointer

	pp[1] = RGB5(31, 31, 31);				// white 1
	pp[3] = RGB5(31, 26, 0);				// yellow 1
	pp[4] = RGB5(27, 22, 0);				// yellow 2
	pp[8] = RGB5(25, 25, 31);				// sky blue 1
	pp[9] = RGB5(20, 20, 31);				// sky blue 2
	pp[10] = RGB5(15, 15, 31);				// sky blue 3
	pp[11] = RGB5(10, 10, 31);				// sky blue 4
	pp[14] = RGB5(31, 0, 0);				// red 1


	pp = NULL;
	free(pp);
	spp = NULL;
	free(spp);

	// read in sprites from sprite importer output file
	extern unsigned int omegaSprite[4096];
	unsigned int* sp = (unsigned int*) 0x06000000;
	int n;
	for (n = 0; n < 2048; n++) {
		sp[n] = omegaSprite[n];
	}
	sp = (unsigned int*) 0x06010000;
	for (n = 0; n < 2048; n++) {
		sp[n] = omegaSprite[n + 2048];
	}
	sp = NULL;
	free(sp);
}

void game_init() {
	// ###################################################################################
	// ################################################################# background set ##
	// ###################################################################################

	setMapBox(0, 16, 32, 2, 6, 1, 13);
	setMapBox(0, 14, 32, 2, 38, 1, 13);
	setMapBox(0, 12, 32, 2, 70, 1, 13);
	setMapBox(0, 10, 32, 2, 7, 1, 13);
	setMapBox(0, 8, 32, 2, 39, 1, 13);
	setMapBox(0, 6, 32, 2, 71, 1, 13);
	setMapBox(0, 4, 32, 2, 8, 1, 13);
	setMapBox(0, 2, 32, 2, 40, 1, 13);
	setMapBox(0, 0, 32, 2, 72, 1, 13);

	tileProfile smallMount = {1, 0, 2, 1};
	tileProfile bigMount = {2, 1, 4, 3};
	tileProfile ground = {0, 1, 2, 2};
	
	int n;
	for (n = 0; n < 8; n++)
		{ setMapPoint_L(n * 4, 16, &bigMount, 0, 12); }

	for (n = 0; n < 16; n++)
		{ setMapPoint_L(n * 2, 17, &smallMount, 0, 11); }

	for (n = 0; n < 16; n++)
		{ setMapPoint_L(n * 2, 18, &ground, 0, 11); }

	// ###################################################################################
	// ################################################################# background set ##
	// ###################################################################################
}

uint titleState = 0;
float titleY = 0;
float titleSpeed = 0;

uint spawnTick = 0;
void game_logic() {
	callTokenStack();
	bgScroll();
	
	if (gameState == 0) {
		titleScript();
	}

	if (gameState == 1) {
		addPlayer();
	}

	if (gameState == 2){
		tileProfile scoreText = {9, 1, 5, 1};
		setMapPoint_L(1, 1, &scoreText, 1, 10);
		drawNumber(8, 1, playerScore, 8, 10);
		if (playerScore < 13370)
			{ playerScore++; }

		if (spawnTick > 100/* && mobCount < 15*/) {
			addMOB();
			mobCount += 1;
			spawnTick = 0;
		}
		else { spawnTick += 1; }
	}

	if (gameState == 3) {
		titleState = 0;
		titleY = 0;
		titleSpeed = 0;

		uint nx, ny;
		for (ny = 0; ny < 32; ny++) {
			for (nx = 0; nx < 32; nx++) {
				setMapPoint(nx, ny, 0, 0, 10);
			}
		}
	}
}

float bg_speed[] = {1.25, 0.65, 0.1};
float bg_pos[] = {0.0, 0.0, 0.0};
void bgScroll() {
	ushort* bg1 = (ushort*) 0x4000014;
	ushort* bg2 = (ushort*) 0x4000018;
	ushort* bg3 = (ushort*) 0x400001C;

	int n;
	for (n = 0; n < 3; n++) {
		bg_pos[n] += bg_speed[n];

		if (bg_pos[n] > 256) {
			bg_pos[n] = 0;
		}
	}
	
	bg1[0] = slashRound(bg_pos[0]);
	bg2[0] = slashRound(bg_pos[1]);
	bg3[0] = slashRound(bg_pos[2]);
}

/*
	------ title state key ------
		0	=	inishalise
		1	=	idle
		2	=	pressed start
		3	=	clear bg layer
*/
void titleScript() {
	if (titleState == 0) {
		tileProfile title = {20, 0, 12, 8};
		setMapPoint_L(9, 4, &title, 1, 10);
		titleState = 1;
	}

	if (titleState == 1) {
		scanKeys();
		u16 keyDown = keysDown();

		if (keyDown & KEY_START) {
			titleState = 2;
		}
	}

	ushort* tc = (ushort*) 0x4000012;
	if (titleState == 2) {
		if (titleY > 100) {
			titleState = 3;
		}
		else {
			titleSpeed += 0.1;
			titleY += titleSpeed;
			tc[0] = slashRound(titleY);
		}
	}

	if (titleState == 3) {
		tc[0] = 0;
		uint nx, ny;
		for (ny = 0; ny < 32; ny++) {
			for (nx = 0; nx < 32; nx++) {
				setMapPoint(nx, ny, 0, 0, 10);
			}
		}
		gameState = 1;
	}
}