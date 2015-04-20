#include "power_comps/PowerCell.h"

PowerCell::PowerCell() {
	name = "DISPLAY_NAME_HERE";
	currMax = 0;
	trueMax = 0;
	currPower = 0;
}

PowerCell::PowerCell(std::string name, int currMax, int trueMax, int currPower) {
	this->name = name;
	this->currMax = currMax;
	this->trueMax = trueMax;
	this->currPower = currPower;
}