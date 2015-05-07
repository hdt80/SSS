#ifndef POWER_COMPS_REACTOR_H
#define POWER_COMPS_REACTOR_H

#include <string>
#include <vector>

#include "network/Connection.h"
#include "power_comps/PowerCell.h"
#include "util/Logger.h"
#include "util/Convert.h"

// Reactor - A Reactor produces all power for PowerCells to use
// If at anytime you're using more power than you can use, the reactor
// will go offline, and no power cells will be recieving power
class Reactor {
	public:
		// Constructor and deconstructor
		Reactor();
		Reactor(int maxPower);
		~Reactor();

		// Methods
		void setMaxPower(int level); // Change the max power level
		void setCurrCell(int cell);

		bool addCell(std::string name, int max); // Adding a new cell
		bool removeCell(std::string name);       // Removing a cell
		bool contains(std::string name);         // Return if a power cell has that name

		bool changePower(int cellIndex, int amount); // Changing a cell's power lvl
		bool setMaxPower(std::string cell, int lvl); // Changing a cell's max power

		PowerCell* get(std::string name); // Return a pointer to the cell with that name

		int getPower(std::string name);      // Return how much power that cell holds
		int getCurrentMax(std::string name); // How much power can be put in
		int getTrueMax(std::string name);    // Max power can be put int
		
		int power(); // How much power is used in all cells
		int left();  // How much power isn't being used by a power cell and is usable
		int size();  // How many cells are in the reactor

		// Vars
		std::vector<PowerCell> cells; // Power cell stored locally
		int maxPower;                 // Max power stored in reactor
		int currentCell;              // Current power cell we're manipulating

		static Reactor _reactor;
};

#endif