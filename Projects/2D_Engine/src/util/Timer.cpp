#include "util/Timer.h"

Timer::Timer() {
	_startTick = 0;
	_pauseTick = 0;

	_paused  = false;
	_running = false;
}

// Start the timer, counting up from how many ticks have happened
void Timer::start() {
	_running = true;
	_paused  = false;

	_startTick = SDL_GetTicks();
	_pauseTick = 0;
}

// Stop running the timer and clear the amount of time we've ran
void Timer::stop() {
	_running = false;
	_paused  = false;

	_startTick = 0;
	_pauseTick = 0;
}

// Pause the timer and store the current tick we're on
void Timer::pause() {
	// If the timer isn't already paused
	if (!_paused) {
		_paused = true; // Pause timer

		// Store how many ticks we've ran for
		_pauseTick = SDL_GetTicks() - _startTick;
		_startTick = 0;
	}
}

void Timer::unpause() {
	// If the timer is currently paused
	if (_paused) {
		_paused = false;

		// Calc how many ticks passed to get what tick we're currently on
		_startTick = SDL_GetTicks() - _pauseTick;
		_pauseTick = 0;
	}
}

// Return how many ticks have been ticked on this timer
int Timer::getTicks() {
	// If the timer is currently running
	if (_running) {
		// If it's paused
		if (_paused) {
			// Return the number of ticks that happen
			// before the timer was paused 
			return _pauseTick;
		} else {
			// Return the current ticks minus the
			// start tick to calc how many ticks it's ran 
			return SDL_GetTicks() - _startTick;
		}
	}
	return 0; // If it isn't running then no time has passed
}

bool Timer::isRunning() {
	return _running;
}

bool Timer::isPaused() {
	return _paused;
}