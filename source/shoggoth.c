#include "shoggoth.h"

void newToken(int tIndex, int tx, int ty) {
	token _token = {
		._pos = {
			._xf = tx,
			._yf = ty,
			._x = tx,
			._y = ty
		}
	};

	gameStack[tIndex] = _token;
}