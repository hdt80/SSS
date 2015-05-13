#include "render/Window.h"

Window::Window(std::string name, int width, int height) {
	_close = false;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		error("Failed to initalize SDL: %s\n", SDL_GetError());
	} else {
		_width = width;
		_height = height;
		_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
		if (_window == nullptr) {
			error("Failed to create window: %s\n", SDL_GetError());
		} else {
			if (TTF_Init() != 0) {
				error("Failed to initalize TTF: %s\n", TTF_GetError());
			}
			_render = new Renderer(_window, height, width);
		}
	}
}

// A fullscreen window
Window::Window(std::string name) {
	_close = false;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		error("Failed to initalize SDL: %s\n", SDL_GetError());
	} else {
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			warn("Linear texture filtering not enabled!");
		}

		// Create a full screen window
		SDL_DisplayMode mode;
		if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
			error("Failed to get desktop mode: %s", SDL_GetError());
		}

		_width  = mode.w;
		_height = mode.h;

		debug("W: %i | H: %i\n", _width, _height);

		_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, _width, _height,
			SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);

		if (_window == nullptr) {
			error("Failed to create window: %s", SDL_GetError());
		} else {
			if (TTF_Init() != 0) {
				error("Failed to initalize TTF: %s\n", TTF_GetError());
			}
			_render = new Renderer(_window, _height, _width);
		}
	}
}

Window::~Window() {
	SDL_DestroyWindow(_window);
	_window = nullptr;

	delete _render;

	SDL_Quit();
}

// Start rendering to the window and create the power cells
void Window::start() {
	Connection::_connection.makeConnect("127.0.0.1", 5003);
	Connection::_connection.write("ENG");

	Serial::_port.connect("COM4");

	// Creating the power cells
	if (!Reactor::_reactor.addCell("Shield", 4)) {
		warn("Failed to create sheild power cell\n");
	}
	if (!Reactor::_reactor.addCell("Radar", 5)) {
		warn("Failed to create radar power cell\n");
	}
	if (!Reactor::_reactor.addCell("Weapons", 3)) {
		warn("Failed to create weapons power cell\n");
	}
	if (!Reactor::_reactor.addCell("Engines", 12)) {
		warn("Failed to create engines power cell\n");
	}

	_fixPanel.addFix("Engine damaged", "1. Cry", "FIX-engine_1", "Engine power++");
	_fixPanel.addFix("ACK", "Curl up", "1", "ACK_1");
	_fixPanel.addFix("UGH", "Watch netflix", "1", "weee");
	_fixPanel.addFix("1", "1", "1", "1");
	_fixPanel.addFix("2", "2", "2", "2");
	_fixPanel.addFix("#3", "3", "4", "4");
	_fixPanel.addFix("$", "4", "4", "4");
	_fixPanel.addFix("5", "5", "5", "5");
	_fixPanel.addFix("6", "6", "6", "6");
	_fixPanel.addFix("7", "&", "7", "7");
	_fixPanel.addFix("8", "8", "*", "*");
	_fixPanel.addFix("Get rid of Bryce", "1. It's simple, we kill the Batman", "DED", "$1000");
	// _fixPanel.addFix();

	// Starting rendering loop
	loop();
}

void Window::loop() {
	while (!shouldClose()) {
		auto start = std::chrono::high_resolution_clock::now();

		Connection::_connection.printBuffer();
		Serial::_port.loop();
		pollEvents();
		render();

		auto finish = std::chrono::high_resolution_clock::now();
		//debug("Loop time: %lld", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count());
	}
}

// Main render method
// All boxes should be drawn first, as they represent the current state
// of various power storage units.
// After all boxes have been drawn dividing lines are drawn on top of the 
// boxes to seperate reactor and power cells, then power cells from another
// power cell. Then an outline is drawn around the whole screen so it looks
// encapsulate and there's no blank space

// ===================================
// | Reactor | Queued events | Power |
// |		 |				 | Cells |
// |		 |			 	 |		 |
// |		 |				 |		 |
// | 		 |				 |		 |
// |		 |				 |		 |
// |		 |				 |		 |
// |		 |				 |		 |
// |		 |				 |		 |
// ===================================
void Window::render() {
	//int tick = SDL_GetTicks();
	_render->clear(0x00, 0x00, 0x00, 0x00); // Screen to black

	renderReactor();
	renderFixPanel();
	renderPowerCells();
	renderDividers();

	// After we render all the power components we'll draw it to the front buffer
	_render->render();

	// VSync, ensuring that a frame is only rendered every 16 ms to make 60 fps
	// int endTick = SDL_GetTicks();
	// debug("Took %i ticks to draw frame. Delay for %i ticks\n", endTick - tick, 16 - (endTick-tick));
	// SDL_Delay(16 - (endTick - tick));
}

// Render the reactor and how much power is currently in it
void Window::renderReactor() {
	_render->setColor(0xC0, 0xC0, 0xC0, 0x00); // Grey

	// Calc how big our box should be by multiplying the size of one cell
	// by the amount of power currently in our reactor to get
	_render->drawBox(REACTOR_X,
					 REACTOR_HEIGHT - ((double) Reactor::_reactor.left() *
					 	(REACTOR_HEIGHT / (double) Reactor::_reactor.maxPower)),
	                 REACTOR_WIDTH,
	                 REACTOR_HEIGHT);

	// Reactor seperators for the max power
	_render->setColor(0xFF, 0x00, 0x00, 0x00); // Red
	for (int y = REACTOR_Y; y < Reactor::_reactor.maxPower; ++y) {
		_render->drawLine(REACTOR_X,
						  (double) y * (REACTOR_HEIGHT / (double) Reactor::_reactor.maxPower), 
						  REACTOR_WIDTH,
						  (double) y * (REACTOR_HEIGHT / (double) Reactor::_reactor.maxPower));
	}
}

// Renders all the power cells and how much power each cell has
void Window::renderPowerCells() {
	// Drawing the amount of power in each cell
	for (int y = POWER_CELL_Y; y < Reactor::_reactor.size(); ++y) {
		PowerCell* cell = &Reactor::_reactor.cells[y];
		
		// Drawing the amount of power inside the cell
		_render->setColor(0xB0, 0xC4, 0xDE, 0x00); // A silvery grey, "light blue steel"
		_render->drawBox(POWER_CELL_X, // Power cell's power starts at 0.75
						 // The y origin of the rect to draw is a ratio of screen hgt to #cells
						 (double) y * (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()),
						 // Width is number of powered cells * max to get width 
						 ((double) cell->currPower * (POWER_CELL_WIDTH / (double) cell->trueMax)),
						 // Height is the ratio of one cell
						 POWER_CELL_HEIGHT / (double) Reactor::_reactor.size());

		// Draw the currMax amount of power
		_render->setColor(0xFF, 0x00, 0x00, 0x00);
		_render->drawBox((POWER_CELL_X + POWER_CELL_WIDTH) -
							((double) cell->trueMax - (double) cell->currMax) * 
							(POWER_CELL_WIDTH / (double) cell->trueMax),
						 (double) y * (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()),
						 POWER_CELL_X + POWER_CELL_WIDTH,
						 POWER_CELL_HEIGHT / (double) Reactor::_reactor.size());
	}

	// Drawing lines between power cell
	_render->setColor(0xFF, 0x00, 0x00, 0x00); // Red
	for (int y = POWER_CELL_Y; y < Reactor::_reactor.size(); ++y) {
		_render->drawLine(POWER_CELL_X,
						  (double) y * (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()), 
						  POWER_CELL_HEIGHT,
						  (double) y * (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()));

		// Drawing the lines for the max power a cell can have
		PowerCell* cell = &Reactor::_reactor.cells[y];
		for (int x = 0; x < cell->trueMax; ++x) {
			// No comments for you here. I struggled with this, and so will you :D
			_render->drawLine(POWER_CELL_X + ((double) x * (POWER_CELL_WIDTH / (double) cell->trueMax)),
							  (double) y * (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()),
							  POWER_CELL_X + ((double) x * (POWER_CELL_WIDTH / (double) cell->trueMax)),
							  (double) (y + 1) * (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()));
		}
	}
}

// Renders the fix panel in the center
void Window::renderFixPanel() {
	// This loop draws all the user info about the center panel, fixes
	for (int i = _fixPanel.currFix; i < _fixPanel.currFix + FIX_PANEL_MAX; ++i) {
		if (i >= _fixPanel.size()) { // If we've reached the end of out fixes
			break;                   // why continue drawing?
		}
		// The problem takes up the first third of a fix slot
		// FIX_PANEL_WIDTH / (100 * FIX_PANEL_WIDTH) is to create some space
		_render->drawText(FIX_PANEL_X + (FIX_PANEL_WIDTH / (100 * FIX_PANEL_WIDTH)),
						  (i - _fixPanel.currFix) * (FIX_PANEL_HEIGHT / FIX_PANEL_MAX),
						  _fixPanel.fixes[i].problem);
		// Steps to fix the problem take up the 2nd third of a fix slot
		_render->drawText(FIX_PANEL_X + (FIX_PANEL_WIDTH / (100 * FIX_PANEL_WIDTH)),
						  (i - _fixPanel.currFix) * (FIX_PANEL_HEIGHT / FIX_PANEL_MAX) + ((FIX_PANEL_HEIGHT / FIX_PANEL_MAX) / 3),
						  _fixPanel.fixes[i].fixSteps);
		_render->drawText(FIX_PANEL_X + (FIX_PANEL_WIDTH / (100 * FIX_PANEL_WIDTH)),
						  (i - _fixPanel.currFix) * (FIX_PANEL_HEIGHT / FIX_PANEL_MAX) + (2 * (FIX_PANEL_HEIGHT / FIX_PANEL_MAX) / 3),
						  "Reward = " + _fixPanel.fixes[i].doneAction);
	}

	// Drawing the seperators for each fix slot
	for (int i = 0; i < FIX_PANEL_MAX; ++i) {
		_render->drawLine(FIX_PANEL_X,
						  i * (FIX_PANEL_HEIGHT / FIX_PANEL_MAX),
						  FIX_PANEL_X + FIX_PANEL_WIDTH,
						  i * (FIX_PANEL_HEIGHT / FIX_PANEL_MAX));
	}
}

// Renders the dividing lines between reactor, power cells and fix panel
void Window::renderDividers() {
	_render->setColor(0xFF, 0x00, 0x00, 0x00); // Red

	// Line dividing the reactor and fix panel
	_render->drawLine(REACTOR_X + REACTOR_WIDTH,
					  REACTOR_Y,
					  REACTOR_WIDTH,
					  REACTOR_HEIGHT);

	// Line dividing the fix panel and power cell
	_render->drawLine(POWER_CELL_X,
					  POWER_CELL_Y,
					  POWER_CELL_X,
					  POWER_CELL_HEIGHT);

	// Screen outline
	_render->drawRect(0.0, 0.0, 1.0, 1.0);

	// Drawing a box around the currently selected cell
	_render->setColor(0x00, 0xFF, 0x00, 0x00); // Green
	_render->drawRect(POWER_CELL_X, // All cells start here
					  // Getting the start y of the cell
					  (double) Reactor::_reactor.currentCell * (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()),
					  // All cells are 0.25 across
					  POWER_CELL_WIDTH,
					  // Height of the rect is the height one power cell occupies
					  (POWER_CELL_HEIGHT / (double) Reactor::_reactor.size()));
}

// Poll all queued events and act on them
void Window::pollEvents() {
	SDL_Event e; // Event we'll send the polling to

	while (SDL_PollEvent(&e) != 0) {
		// Event handling in here
		if (e.type == SDL_QUIT) {
			_close = true;
		} else if (e.type == SDL_KEYDOWN) {
			keyEvent(&e);
		}
	}
}

// key event handler wrapper
// "But I'm not a rapper" - supa hot fiya
void Window::keyEvent(SDL_Event* e) {
	if (e->type != SDL_KEYDOWN) { // If it isn't a key event then why
		return;					  // are we handling it?
	}

	if (e->key.keysym.sym == SDLK_ESCAPE) {
		_close = true;
	} else if (e->key.keysym.sym == SDLK_UP) {
		Reactor::_reactor.setCurrCell(Reactor::_reactor.currentCell - 1);
	} else if (e->key.keysym.sym == SDLK_DOWN) {
		Reactor::_reactor.setCurrCell(Reactor::_reactor.currentCell + 1);
	} else if (e->key.keysym.sym == SDLK_LEFT) {
		Reactor::_reactor.changePower(Reactor::_reactor.currentCell, -1);
	} else if (e->key.keysym.sym == SDLK_RIGHT) {
		Reactor::_reactor.changePower(Reactor::_reactor.currentCell, 1);
	} else if (e->key.keysym.sym == SDLK_KP_8) {
		_fixPanel.changeCurrFix(-1);
	} else if (e->key.keysym.sym == SDLK_KP_2) {
		_fixPanel.changeCurrFix(1);
	}
}

void Window::mouseEvent(SDL_Event* e) {

}

bool Window::shouldClose() {
	return _close;
}