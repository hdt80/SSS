// =================================
// Includes
// =================================
#define SSS_DO_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include "render/Window.h"
#include "util/Logger.h"

// =================================
// Main
// =================================
int main(int argc, char* argv[]) {
	try {
    	Window w("Engineering", 1024, 768);
    	w.start();
	} catch (...) {
		printf("Oh dear: %s\n", SDL_GetError());
	}
    return 0;
}