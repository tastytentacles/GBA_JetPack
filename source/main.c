
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>

#include "shoggoth.h"

void invoke();
void game_logic();

int main(void) {
	irqInit();
	irqEnable(IRQ_VBLANK);
	invoke();

	newToken(0, 10, 10);

	while (1) 
	{
		callTokenStack();
		VBlankIntrWait();
	}
}


void game_logic() {
	int n;
	int nx = 16;
	for (n = 0; n < nx; n++) {

	}
}

void invoke() {
	// establish relevlent io and bg memmory
	unsigned short* cp1 = (unsigned short*) 0x4000000;	// i/o part 1
	unsigned short* cp2 = (unsigned short*) 0x4000004;	// i/o part 2
	unsigned short* cp3 = (unsigned short*) 0x4000008;	// i/o part 3
	cp1[0] = ((1 << 8) | (1 << 9) | (1 << 10) | (1 << 12));
	cp2[0] = ((1 << 3));
	cp3[0] = ((10 << 8));

	cp1 = NULL;
	free(cp1);
	cp2 = NULL;
	free(cp2);
	cp3 = NULL;
	free(cp3);

	// establish palet
	unsigned short* pp = (unsigned short*) 0x5000000;	// tile memmory block
	unsigned short* spp = (unsigned short*) 0x5000200;	// obj tile memmory block

	spp[1] = pp[1] = RGB5(8, 8, 8);			// gray
	spp[2] = pp[2] = RGB5(15, 15, 31);		// blue 1
	spp[3] = pp[3] = RGB5(10, 10, 31);		// blue 2
	spp[4] = pp[4] = RGB5(5, 5, 31);		// blue 3
	spp[5] = pp[5] = RGB5(15, 31, 15);		// green 1
	spp[6] = pp[6] = RGB5(10, 31, 10);		// green 2
	spp[7] = pp[7] = RGB5(5, 31, 5);		// green 3
	spp[8] = pp[8] = RGB5(28, 14, 0);		// orange 1
	spp[9] = pp[9] = RGB5(24, 10, 0);		// orange 2
	spp[10] = pp[10] = RGB5(20, 6, 0);		// orange 3
	spp[11] = pp[11] = RGB5(28, 28, 28);	// white 1
	spp[12] = pp[12] = RGB5(20, 20, 20);	// white 2
	spp[13] = pp[13] = RGB5(10, 10, 10);	// white 3
	spp[14] = pp[14] = RGB5(31, 0, 0);		// red 1
	spp[15] = pp[15] = RGB5(16, 0, 0);		// red 2

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