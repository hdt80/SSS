#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include <string>
#include <thread>
#include <chrono>

#include "SDL.h"
#include "SDL_ttf.h"

#include "power_comps/Reactor.h"
#include "power_comps/FixPanel.h"

#include "util/Logger.h"
#include "render/Renderer.h"
#include "network/Connection.h"

// Define some magic values up here for "Ease of Use"
// All these values are ratios, weeeeeees
#define REACTOR_X      0.0
#define REACTOR_Y      0.0
#define REACTOR_WIDTH  0.25
#define REACTOR_HEIGHT 1.0

#define POWER_CELL_X      0.75
#define POWER_CELL_Y      0.0
#define POWER_CELL_WIDTH  0.25
#define POWER_CELL_HEIGHT 1.0

#define FIX_PANEL_X      0.25
#define FIX_PANEL_Y      0.0
#define FIX_PANEL_WIDTH  0.5
#define FIX_PANEL_HEIGHT 1.0
#define FIX_PANEL_MAX    10.0

class Window {
	public:
		Window(std::string name, int width, int height);
		Window(std::string name); // Fullscreen window
		~Window();

		// Control methods
		void start();
		void loop();

		// Main loop methods
		void render();
		void pollEvents();

		// Event methods
		void keyEvent(SDL_Event* e);
		void mouseEvent(SDL_Event* e);

		bool shouldClose();

		SDL_Window* _window; // Window to render to

		// An object that will render things for us
		Renderer*  _render;     // Renders stuff
		//Reactor    _reactor;    // Main power reactor
		FixPanel   _fixPanel;   // Center fix panel

		bool _close; // If the window should close or not

		int _width;  // Width of window
		int _height; // Height of window

	private:
		// We split the code up so it's easier to fix when stuff breaks
		void renderReactor();    // Sub-function to render reactor state
		void renderPowerCells(); // Rendering power cell states
		void renderFixPanel();   // Rending center fix panel
		void renderDividers();   // Drawing lines between the containers
};

#endif