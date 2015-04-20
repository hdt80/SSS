#ifndef POWER_COMPS_POWER_CELL_H
#define POWER_COMPS_POWER_CELL_H

#include <string>

// PowerCell - An object to hold the current state of various functions of 
// a ship. Things such as engines, weapons, radar, sheilds, navigation are
// all controlled by the power level they hold
class PowerCell {
	public:
		// Constructor and deconstructor
		PowerCell();
		PowerCell(std::string name, int currMax, int trueMax, int currPower);

		// Methods

		// Vars
		std::string name; // Display name 
		// Because cells can be damage, the amount of power that they can hold
		// will be increased and decreased depending on the actions taken place
		int currMax;
		int trueMax;      // The max max power the call can hold
		int currPower;    // Current power level provided to cell
};

#endif