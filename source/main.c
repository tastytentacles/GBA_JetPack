
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token token;
struct token {
	void			(*_script)(token*);
	void			(*_addTag)(token*);
	void			(*_callTag)(token*, char);

	char			tagMap[8];
	token*			map[8];
};

token newToken();

void addTag(token* _target, char _tag);
void callTag(char _tag);

void invoke();
void create_eSpace();
void game_logic();

int main(void) {
	irqInit();
	irqEnable(IRQ_VBLANK);
	invoke();
	while (1) 
	{
		token firstPoint = newToken();

		VBlankIntrWait();
	}
}


token newToken() {
	token _token;
	_token._addTag = addTag;
	_token._callTag = callTag;
	return _token;
}

void addTag(token* _target, char _tag) {

}

void callTag(char _tag) {

}


void create_eSpace(token* comandPoint) {

}

void game_logic() {

}

void invoke() {
	unsigned short* cp1 = (unsigned short*) 0x4000000;
	unsigned short* cp2 = (unsigned short*) 0x4000004;
	unsigned short* cp3 = (unsigned short*) 0x4000008;
	cp1[0] = ((0 << 6) | (1 << 8) | (1 << 9) | (1 << 10) | (1 << 12));
	cp2[0] = ((1 << 3));
	cp3[0] = ((10 << 8));

	cp1 = NULL;
	free(cp1);
	cp2 = NULL;
	free(cp2);
	cp3 = NULL;
	free(cp3);
}