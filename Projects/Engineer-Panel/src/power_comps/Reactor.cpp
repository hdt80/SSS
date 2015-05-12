#include "power_comps/Reactor.h"

// =================================
// Constructor and desconstructor
// =================================
Reactor::Reactor() {
	this->maxPower    = 16;
	this->currentCell = 0;
}

Reactor::Reactor(int maxPower) {
	this->maxPower    = maxPower;
	this->currentCell = 0;
}

Reactor::~Reactor() {

}

// =================================
// Methods
// =================================

// Change the max power in the reactor
// powerLevel - Level to change
void Reactor::setMaxPower(int level) {
	this->maxPower = level;
}

// Set the current power cell we're manipulating, upping or decreasing the power
// cell - Cell's power we're going to change
//      - If we try to change the cell below 0 or how many cells we've got then
//      - clamp the cell we're changing to a valid cell
void Reactor::setCurrCell(int cell) {
	if (cell < 0 || cell >= size()) {
		return;
	}
	currentCell = cell;
}

// Adding a new power cell under the reactor
// name - Display name of the new cell
// max  - Max power the new cell can hold
// Returns if the cell was added
//   true - No cell with matching name found
//   false - Cell with matching name found
bool Reactor::addCell(std::string name, int max) {
	if (contains(name)) {
		return false;
	}
	PowerCell toAdd(name, // Reactor name
					max,  // Current max power, hasn't changed, so max
					max,  // True max power
					0     // Current power of cell
	);
	cells.push_back(toAdd);
	return true;
}

// Removes a power cell from the reactor
// name - Display name of cell to remove
// Returns if the cell was removed
//   true - Cell was found and removed
//   false - Cell wasn't found and couldn't be removed
bool Reactor::removeCell(std::string name) {
	if (!contains(name)) {
		return false;
	}
	return false;
}

// Return if this reactor has a power cell with that display name
// name - Power cell to find
// Returns if the reactor contians that cell
//   true - Reactor contains cell
//   false - Reactor doesn't contain cell
bool Reactor::contains(std::string name) {
	return (get(name) != nullptr);
}

// Changing the power level of a the cell at the current index by the amount
// cellIndex - Index of cell to modify power level
// amount    - Amount of power to add/take from the cell
// Returns if the reactor can complete that power change
//   true - There is enough power and the cell can accept the new power change
//   false - There isn't enough power or cell cannot accept power change
bool Reactor::changePower(int cellIndex, int amount) {
	if (cellIndex < 0 || cellIndex > size()) { // Checking we're modifying a
		return false;                          // valid cell
	}
	PowerCell* cell = &cells[cellIndex];

	// If we're adding power then we'll need to run a different set
	// of checks then if we're removing power from a cell
	if (amount > 0) {
		if (cell->currPower >= cell->currMax || // Currently using max power
			left() == 0) {                      // No power left in reactor
			return false;
		}
	} else { // Removing power, diff checks
		if (cell->currPower <= 0) { // No power = can't remove power
			return false;
		}
	}

	cells[cellIndex].currPower += amount;

	// Creating the string to be sent to the master server
	std::string str = "";
	str.append("EVN#");
	str.append("4;"); // Event ID 4 is power change event
	str.append(cell->name);
	str.append(";");
	str.append(convert::toString(cell->currPower));
	Connection::_connection.write(str);

	return true;
}

// Change a cell's max power level to the new amount
// cell - Power cell to change the max power
// amount - New max power relative to the current max power
// Returns if the cell can have that much max power
bool Reactor::setMaxPower(std::string str, int amount) {
	PowerCell* cell = get(str);
	if (cell == nullptr) {
		warn("Cell %s doesn't exist", str.c_str());
		return false;
	}
	if (cell->currMax > 0 && cell->currMax <= cell->trueMax) {
		cell->currMax += amount;
	} else {
		warn("Cannot change %s's max power to %i (Currently %i)", str.c_str(), amount, cell->currMax);
	}
	return true;
}

// Returns a pointer to the cell with that name
// name - Power cell with that name to return
// returns - A pointer to the cell with that name, or nullptr if that cell doesn't exist
PowerCell* Reactor::get(std::string name) {
	for (unsigned int i = 0; i < cells.size(); ++i) {
		if (cells[i].name == name) {
			return &cells[i];
		}
	}
	return nullptr;
}

// Return how much power a power cell is currently using
// name - The display name of the cell to return the power of
// returns - How much power is in that cell, or -1 if that cell doesn't exist
int Reactor::getPower(std::string name) {
	if (!contains(name)) {
		return -1;
	}
	return get(name)->currPower;
}

// Return how much a cell can currently hold
int Reactor::getCurrentMax(std::string name) {
	if (!contains(name)) {
		return -1;
	}
	return get(name)->currMax;
}

// Return how much a cell can hold
int Reactor::getTrueMax(std::string name) {
	if (!contains(name)) {
		return -1;
	}
	return get(name)->trueMax;
}

// Return how much power is currently being drawn by all power cells
int Reactor::power() {
	int power = 0;
	for (int i = 0; i < size(); ++i) {
		power += cells[i].currPower;
	}
	return power;
}

// Return how much power isn't being used by power cell and can be
// routed to other power cells. Basically the leftover power
int Reactor::left() {
	return (maxPower - power());
}

// Return how many power cells are being used
int Reactor::size() {
	return cells.size();
}

// Create reference for static variable
Reactor Reactor::_reactor;