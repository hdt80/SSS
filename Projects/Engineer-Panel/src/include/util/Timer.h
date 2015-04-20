#ifndef UTIL_TIMER_H
#define UTIL_TIMER_H

#include "SDL.h"
#include <stdio.h>
// A timer
class Timer {
	public:
		// Constuctor
		Timer();

		void start();   // Start running the timer
		void stop();    // Stop the timer
		void pause();   // Pause the timer
		void unpause(); // Unpause the timer

		int getTicks(); // Get how many ticks its been running

		bool isRunning(); // If the timer has been started
		bool isPaused();  // If the timer is currently paused

	private:
		int _startTick; // How many ticks ran when the timer stared
		int _pauseTick; // What tick we paused on

		bool _paused;  // If currently paused
		bool _running; // If stared
};

#endif