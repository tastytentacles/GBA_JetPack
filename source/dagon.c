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
	unsigned short* cp1 = (unsigned short*) 0x4000000;	// i/o part 1
	unsigned short* cp2 = (unsigned short*) 0x4000004;	// i/o part 2
	unsigned short* bgc0 = (unsigned short*) 0x4000008;	// bg controll part 1
	unsigned short* bgc1 = (unsigned short*) 0x400000A;	// bg controll part 2
	unsigned short* bgc2 = (unsigned short*) 0x400000C;	// bg controll part 3
	unsigned short* bgc3 = (unsigned short*) 0x400000E;	// bg controll part 4
	cp1[0] = ((1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 12));
	cp2[0] = ((1 << 3));
	bgc0[0] = ((10 << 8));
	bgc1[0] = ((2 << 0) | (11 << 8));
	bgc2[0] = ((2 << 0) | (12 << 8));
	bgc3[0] = ((2 << 0) | (13 << 8));

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

	// palatte 2
	pp = (unsigned short*) 0x5000020;

	pp[1] = RGB5(0, 0, 0);
	pp[1] = RGB5(31, 31, 31);
	pp[8] = RGB5(25, 25, 31);				// sky blue 1
	pp[9] = RGB5(20, 20, 31);				// sky blue 2
	pp[10] = RGB5(15, 15, 31);				// sky blue 3
	pp[11] = RGB5(10, 10, 31);				// sky blue 4

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
	tileProfile scoreText = {9, 1, 5, 1};
	
	int n;
	for (n = 0; n < 8; n++)
		{ setMapPoint_L(n * 4, 16, &bigMount, 0, 12); }

	for (n = 0; n < 16; n++)
		{ setMapPoint_L(n * 2, 17, &smallMount, 0, 11); }

	for (n = 0; n < 16; n++)
		{ setMapPoint_L(n * 2, 18, &ground, 0, 11); }

	setMapPoint_L(1, 1, &scoreText, 1, 10);

	newToken(0, 0, 32, 32);
	t_setSprite(0, 0, 1, 0, 1);
	t_addScript(0, 0, playerScript);

	sortAddToken(0, 10, 10);
	sortAddToken(0, 20, 10);
	sortAddToken(0, 30, 10);
	sortAddToken(0, 40, 10);

	killToken(1, 0);

	sortAddToken(0, 55, 55);
}

void game_logic() {
	callTokenStack();
	bgScroll();
}

float bg_speed[] = {1.25, 0.65, 0.1};
float bg_pos[] = {0.0, 0.0, 0.0};
void bgScroll() {
	// unsigned short* bg0 = (unsigned short*) 0x4000010;
	unsigned short* bg1 = (unsigned short*) 0x4000014;
	unsigned short* bg2 = (unsigned short*) 0x4000018;
	unsigned short* bg3 = (unsigned short*) 0x400001C;

	int n;
	for (n = 0; n < 3; n++) {
		bg_pos[n] += bg_speed[n];

		if (bg_pos[n] > 256) {
			bg_pos[n] = 0;
		}
	}
	
	// bg0[0] = slashRound(bg_pos[0]);
	bg1[0] = slashRound(bg_pos[0]);
	bg2[0] = slashRound(bg_pos[1]);
	bg3[0] = slashRound(bg_pos[2]);
}