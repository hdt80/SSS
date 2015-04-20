#ifndef POWER_COMPS_FIX_PANEL_H
#define POWER_COMPS_FIX_PANEL_H

#include <string>
#include <vector>

#include "util/Logger.h"

// The FixPanel is the center panel of the screen that has a list of
// instructions needs to fix certain power cells. 
// Inside the FixPanel class there's the Fix class, which contains
// the problem, steps to fix said problem, what message we're expecting from
// the server when a fix has been applied, and finally, what action we should do
// when we recieve the completed message. 

// The Engineer will select the set of Instructions he wants to follow by using
// the num pad, 8 to go up, and 2 for down. Hitting 5 will toggle if the current
// selected fix is open or not. When opened, the center screen will clear, and draw the steps
// in the middle. 

class FixPanel {
	private:
		class Fix {
			public:
				// Constructor and deconstructor
				Fix();
				Fix(std::string problem, std::string fixSteps,
					std::string fixDone, std::string doneAction);
				~Fix();

				// Vars
				std::string problem;    // What the problem is
				std::string fixSteps;   // Steps to fix problem
				std::string fixDone;    // Message recieved when fix applied
				std::string doneAction; // Action to do when done
		};

	public:
		// Constructor and deconstructor
		FixPanel();
		~FixPanel();


		// Methods
		int size(); // Return the amount of fixes in queue
		
		void changeCurrFix(int amount); // Increase or decrease the curr fix

		// Add a fix to the queue
		void addFix(std::string problem, std::string fixSteps,
					std::string fixDone, std::string doneAction);

		// Vars
		std::vector<Fix> fixes;   // Vector of undone fixes
		int              currFix; // Current fix we've selected, will be at top
};

#endif