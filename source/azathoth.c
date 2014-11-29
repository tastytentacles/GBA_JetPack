#include "azathoth.h"

callTokenStack();

float speedInhibitor = 1.5;
void playerScript(token* __self) {
	scanKeys();
	unsigned int keyDown = KeysDown();
	unsigned int keyUp = KeysUp();

	// __self._vec._speedx += (KeysDown() >> 7);
}