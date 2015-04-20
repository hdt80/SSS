#include "power_comps/FixPanel.h"

// =================================
// Fix
// =================================

// Constuctor
FixPanel::Fix::Fix() {
	problem    = "";
	fixSteps   = "";
	fixDone    = "";
	doneAction = "";
}

FixPanel::Fix::Fix(std::string problem, std::string fixSteps, std::string fixDone, std::string doneAction) {
	this->problem    = problem;
	this->fixSteps   = fixSteps;
	this->fixDone    = fixDone;
	this->doneAction = doneAction;
}

// Deconstuctor
FixPanel::Fix::~Fix() {

}

// =================================
// Fix panel
// =================================

// Constructor
FixPanel::FixPanel() {
	currFix = 0;
	fixes.clear();
}

// Deconstuctor
FixPanel::~FixPanel() {
	fixes.clear();
}

// Returns the amount of fixes we have in our queue
int FixPanel::size() {
	return fixes.size();
}

// Change the current fix we've selected by a given amount
void FixPanel::changeCurrFix(int amount) {
	// If we're adding or removing from currFix changes the checks we run
	if (amount > 0) {
		// We always want atleast one fix draw, if any, so we'll clamp to size-1
		if (currFix < size() - 1) {
			currFix += amount;
		}
	} else {
		// Can't go below 0 or else we'll get a seg fault
		if (currFix > 0) {
			currFix += amount; // += cause we provide the -
		}
	}
}

// Add a fix to the queue of fixes
// problem - What broke
// fixSteps - Instructions to fix said problem, like a minigame
// fixDone - What message will be recieved when the steps are done
// doneAction - Message to send to the server once fixDone is recieved
//            - such as adding more power to a cell or changing the currMax
void FixPanel::addFix(std::string problem, std::string fixSteps,
					  std::string fixDone, std::string doneAction) {
	Fix fix(problem, fixSteps, fixDone, doneAction);
	fixes.push_back(fix);
}